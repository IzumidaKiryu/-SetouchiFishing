/*!
 * @brief	シンプルなモデルシェーダー。
 */


////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

cbuffer DirectionLightCb : register(b1)
{
	//ディレクションライト用変数
    float3 ligDirection;
    float3 ligColor;
	
	
	//ポイントライト用変数
    float3 ptPosition; // ポイントライトの位置
    float3 ptColor; // ポイントライトのカラー
    float ptRange; // ポイントライトの影響範囲
	
	
	//視点のデータにアクセスするための変数を定数バッファに登録
    float3 eyePos;
    float3 ambientLight; //環境光
}
////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn{
	int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float2 uv 		: TEXCOORD0;	//UV座標。
	SSkinVSIn skinVert;				//スキン用のデータ。
    float3 normal : NORMAL;
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float2 uv 			: TEXCOORD0;	//uv座標。
    float3 normal : NORMAL;
    float3 worldPos : TEXCOORD1;
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);




/// <summary>
//スキン行列を計算する。
/// </summary>
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

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
	SPSIn psIn;
	float4x4 m;
	if( hasSkin ){
		m = CalcSkinMatrix(vsIn.skinVert);
	}else{
		m = mWorld;
	}
	psIn.pos = mul(m, vsIn.pos);
    psIn.worldPos = psIn.pos;
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);

	//頂点法線をピクセルシェーダに渡す。
    psIn.normal = mul(mWorld, vsIn.normal);
	
	psIn.uv = vsIn.uv;

	return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, true);
}
/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain( SPSIn psIn ) : SV_Target0
{
	//ディレクションライトによるランバートは拡散の計算。
    float3 diffDirection = CalcLambertDiffuse(ligDirection, ligColor, psIn.normal);
	//ディレクションライトによるPhong鏡面反射の計算。
    float3 specDirection = CalcPhongSpecular(ligDirection, ligColor, psIn.worldPos,psIn.normal);
	
	
	//ポイントライトによるランバート拡散反射光とPhong鏡面反射光の計算。
	//サーフェースに入射するポイントライトの幹を計算。
    float3 ligDir = psIn.worldPos - ptPosition;
	
	//正規化して大きさ１のベクトルにする。
    ligDir = normalize(ligDir);
	
	//減衰なしのLambert拡散反射光を計算。
    float3 diffPoint = CalcLambertDiffuse(
		ligDir,		//ライトの方向。
		ptColor,	//ライトのカラー。
		psIn.normal	//サーフェースの法線。
	);
	
	//減衰なしのPhong鏡面反射光を計算。
    float3 specPoint = CalcPhongSpecular(
		ligDir,			 //ライトの方向。
		ptColor,		 //ライトのカラー。
		psIn.worldPos,	 //サーフェースのワールド座標
		psIn.normal		 //サーフェースの法線。
	);
	
	
	//距離による影響率を計算する。
	//ポイントライトの距離を計算する。
    float distance = length(psIn.worldPos - ptPosition);
	
	//影響率はひょりに比例して小さくなる。
    float affect = 1.0f - 1.0f / ptRange * distance;
	
	//影響力がマイナスにならないように補正をかける。
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }
	
	//影響力を指数関数にする。3乗にしてる。
    affect = pow(affect, 3.0f);
	
	//拡散反射光と鏡面反射光に影響力を乗算して影響を弱める。
    diffPoint *= affect;
    specPoint *= affect;
	
	//2つの反射光を合算して最終的な反射光を求める。
    float3 diffceLig = diffPoint + diffDirection;
    float3 speclarLig = specPoint + specDirection;
	
	//拡散反射光と鏡面反射光を足し算して最終的な光を求める。
    float3 lig = diffceLig + speclarLig + ambientLight;
	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);
	
	//最終的な出力カラーに光を乗算する。
	albedoColor.xyz *= lig;
	

	return albedoColor;
}
/// <summary>
/// Lambert拡散反射の計算。
/// <summary>
float3 CalcLambertDiffuse(float3 lightDire, float3 lightColor, float3 normal)
{
	// ピクセルの法線とライトの方向の内積を計算する
    float t = dot(normal, lightDire) * -1.0f;

    // 内積の値を0以上の値にする
    t = max(0.0f, t);

    // 拡散反射光を計算する
    return lightColor * t;
}

/// <summary>
/// Phong鏡面反射光を計算する
/// </summary>
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
    // 反射ベクトルを求める
    float3 refVec = reflect(lightDirection, normal);

    // 光が当たったサーフェイスから視点に伸びるベクトルを求める
    float3 toEye = eyePos - worldPos;
    toEye = normalize(toEye);

    // 鏡面反射の強さを求める
    float t = dot(refVec, toEye);

    // 鏡面反射の強さを0以上の数値にする
    t = max(0.0f, t);

    // 鏡面反射の強さを絞る
    t = pow(t, 5.0f);

    // 鏡面反射光を求める
    return lightColor * t;
}