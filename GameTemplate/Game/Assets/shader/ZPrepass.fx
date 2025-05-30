///////////////////////////////////////
// ZPrepass
///////////////////////////////////////


///////////////////////////////////////
// 構造体。
///////////////////////////////////////
struct SSkinVSIn
{
    int4 Indices : BLENDINDICES0;
    float4 Weights : BLENDWEIGHT0;
};

// 頂点シェーダーへの入力
struct SVSIn
{
    float4 pos : POSITION; //頂点座標。
    SSkinVSIn skinVert; //スキン用のデータ。
};

// ピクセルシェーダーへの入力
struct SPSIn
{
    float4 pos : SV_POSITION; //座標。
    float3 depth : TEXCOORD0; //深度値。xにはプロジェクション空間、yにはカメラ空間での正規化されたZ値、zにはカメラ空間でのZ値
};

//関数定義
SPSIn VSMain(SVSIn vsIn, uniform bool hasSkin);

//変数定義
StructuredBuffer<float4x4> g_boneMatrix : register(t3); //ボーン行列。


///////////////////////////////////////
// 定数バッファ。
///////////////////////////////////////
// モデル用の定数バッファー
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

//スキン行列を計算する。
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
    float4x4 skinning = 0;
    float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}



///////////////////////////////////////
// 関数
///////////////////////////////////////

// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
SPSIn VSMain(SVSIn vsIn)
{
    return VSMain(vsIn, false);
}
// スキンありメッシュの頂点シェーダーのエントリー関数。
SPSIn VSSkinMain(SVSIn vsIn)
{
    return VSMain(vsIn, true);
}

// モデル用の頂点シェーダーのエントリーポイント
SPSIn VSMain(SVSIn vsIn, uniform bool hasSkin)
{
    SPSIn psIn;
    
    float4x4 m;
    if (hasSkin)
    {
        m = CalcSkinMatrix(vsIn.skinVert);
    }
    else
    {
        m = mWorld;
    }

    psIn.pos = mul(m, vsIn.pos); // モデルの頂点をワールド座標系に変換
    psIn.pos = mul(mView, psIn.pos); // ワールド座標系からカメラ座標系に変換
    psIn.depth.z = psIn.pos.z;
    psIn.pos = mul(mProj, psIn.pos); // カメラ座標系からスクリーン座標系に変換
    psIn.depth.x = psIn.pos.z / psIn.pos.w;
    psIn.depth.y = saturate(psIn.pos.w / 1000.0f);
    
    return psIn;
}


// モデル用のピクセルシェーダーのエントリーポイント
float4 PSMain(SPSIn psIn) : SV_Target0
{
    return float4(psIn.depth.x, psIn.depth.y, psIn.depth.z, 1.0f);
}

