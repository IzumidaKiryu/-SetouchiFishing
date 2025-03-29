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

//ライトデータにアクセスするための定数バッファを用意する。
cbuffer DirectionLightCb : register(b1)
{
	//ディレクションライト用変数
    float3 ligDirection;
    float3 ligColor;
	
	
	//ポイントライト用変数
    float3 ptPosition; // ポイントライトの位置。
    float3 ptColor; // ポイントライトのカラー。
    float ptRange; // ポイントライトの影響範囲。
	
	//スポットライト用変数。
    float3 spPosition; // スポットライトの位置。
    float3 spColor; // スポットライトのカラー。
    float spRange; // スポットライトの射出範囲。
    float3 spDirection; // スポットライトの射出方向。
    float spAngle; // スポットライトの射出角度。

	
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
    //カメラ空間の法線の追加。
    float3 normalInView : TEXCOORD2;//カメラ空間の法線。
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
float3 CalcLigFromPointLight(SPSIn psIn);//ポイントライトの計算。
float3 CalcLigFromDirectionLight(SPSIn psIn);
float3 CalcLigFromSpotLight(SPSIn psIn);//スポットライトによるライティングの計算。


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
    psIn.normal = mul(m, vsIn.normal);
	
	psIn.uv = vsIn.uv;
    
    //カメラ空間の法線を求める。
    psIn.normalInView = mul(mView, psIn.normal);//カメラ空間の法線の計算。

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
	 // ディレクションライトによるライティングを計算する
    float3 directionLig = CalcLigFromDirectionLight(psIn);

    // ポイントライトによるライティングを計算する
    float3 pointLig = CalcLigFromPointLight(psIn);
    
    //スポットライトによるライティングの計算。
    float3 spotLig = CalcLigFromSpotLight(psIn);
   
   // //リムライトの強さを求める。
   // //サーフェースの法線と光の入射方向に依存するリムの強さを求める。
    float power1 = 1.0f - max(0.0f, dot(ligDirection, psIn.normal));
    
   // //サーフェースの法線と視線の方向に依存するリムの強さを求める。
    float power2 = 1.0f - max(0.0f, psIn.normalInView.z * -1.0f);
    
   // //最終的なリムの強さを求める。
    float limPower = power1 * power2;
    
   // //pow()を使用して強さの変化を指数関数的にする。
    limPower = pow(limPower, 1.3f);
    
   // ////最終的な反射光を求める（リム確認用）。
   //float limOnlyFinalLig = directionLig + ambientLight;
    
   // //最終的な反射光を求める（全ライト）。
    float allLightFinalLig = directionLig + pointLig + spotLig + ambientLight;
    
   // //最終的な反射光にリムライトの反射光を合成する。
   // //リムライトのカラーを計算する。
    float3 limColor = limPower * ligColor;
    
   // //最終的な反射光にリムの反射光を合算する。
    //(リムのみ)
   //limOnlyFinalLig += limColor;
    //（すべてのライト）
    allLightFinalLig += limColor;
    
	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);
	
	//最終的な出力カラーに光を乗算する。
	//albedoColor.xyz *= limOnlyFinalLig;
    albedoColor.xyz *= allLightFinalLig;
 
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

//ポイントライトによる反射光の計算。
float3 CalcLigFromPointLight(SPSIn psIn)
{
    // このサーフェイスに入射しているポイントライトの光の向きを計算する
    float3 ligDir = psIn.worldPos - ptPosition;

    // 正規化して大きさ1のベクトルにする
    ligDir = normalize(ligDir);

    // 減衰なしのLambert拡散反射光を計算する
    float3 diffPoint = CalcLambertDiffuse(
        ligDir, // ライトの方向
        ptColor, // ライトのカラー
        psIn.normal // サーフェイスの法線
    );

    // 減衰なしのPhong鏡面反射光を計算する
    float3 specPoint = CalcPhongSpecular(
        ligDir, // ライトの方向
        ptColor, // ライトのカラー
        psIn.worldPos, // サーフェイズのワールド座標
        psIn.normal     // サーフェイズの法線
    );

    // 距離による影響率を計算する
    // ポイントライトとの距離を計算する
    float3 distance = length(psIn.worldPos - ptPosition);

    // 影響率は距離に比例して小さくなっていく
    float affect = 1.0f - 1.0f / ptRange * distance;

    // 影響力がマイナスにならないように補正をかける
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }

    // 影響の仕方を指数関数的にする。今回のサンプルでは3乗している
    affect = pow(affect, 3.0f);

    // 拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める
    diffPoint *= affect;
    specPoint *= affect;

    return diffPoint + specPoint;
}

/// <summary>
/// ディレクションライトによる反射光を計算
/// </summary
/// <param name="psIn">ピクセルシェーダーからの入力。</param>
float3 CalcLigFromDirectionLight(SPSIn psIn)
{
    // ディレクションライトによるLambert拡散反射光を計算する
    float3 diffDirection = CalcLambertDiffuse(ligDirection, ligColor, psIn.normal);

    // ディレクションライトによるPhong鏡面反射光を計算する
    float3 specDirection = CalcPhongSpecular(ligDirection, ligColor, psIn.worldPos, psIn.normal);
    return diffDirection + specDirection;
}


float3 CalcLigFromSpotLight(SPSIn psIn)
{
     //スポットライトによるライティングを計算する。
    //サーフェースに入射するスポットライトの幹を計算。
    float3 ligDir = psIn.worldPos - spPosition;
	
	//正規化して大きさ１のベクトルにする。
    ligDir = normalize(ligDir);
	
	//減衰なしのLambert拡散反射光を計算。
    float3 diffSpotLight = CalcLambertDiffuse(
		ligDir, //ライトの方向。
		spColor, //ライトのカラー。
		psIn.normal	//サーフェースの法線。
	);
	
	//減衰なしのPhong鏡面反射光を計算。
    float3 specSpotLight = CalcPhongSpecular(
		ligDir, //ライトの方向。
		spColor, //ライトのカラー。
		psIn.worldPos, //サーフェースのワールド座標
		psIn.normal		 //サーフェースの法線。
	);
	
	
	//距離による影響率を計算する。
	//ポイントライトの距離を計算する。
    float distance = length(psIn.worldPos - spPosition);
	
	//影響率はひょりに比例して小さくなる。
    float affect = 1.0f - 1.0f / spRange * distance;
	
	//影響力がマイナスにならないように補正をかける。
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }
	
	//影響力を指数関数にする。3乗にしてる。
    affect = pow(affect, 3.0f);
	
	//拡散反射光と鏡面反射光に影響力を乗算して影響を弱める。
    diffSpotLight *= affect;
    specSpotLight *= affect;
	//入射光と射出方向の角度を求める
    // dot()を利用して内積を求める
    float angle = dot(ligDir, spDirection);

    // dot()で求めた値をacos()に渡して角度を求める
    angle = abs(acos(angle));

    //角度による影響率を求める
    // 角度に比例して小さくなっていく影響率を計算する
    affect = 1.0f - 1.0f / spAngle * angle;

    // 影響率がマイナスにならないように補正をかける
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }

    //影響の仕方を指数関数的にする。今回のサンプルでは0.5乗している
    affect = pow(affect, 3.0f);

    //角度による影響率を反射光に乗算して、影響を弱める
    diffSpotLight *= affect;
    specSpotLight *= affect;
    return diffSpotLight + specSpotLight;
	
}
