/*!
 * @brief	繧ｷ繝ｳ繝励Ν縺ｪ繝｢繝・Ν繧ｷ繧ｧ繝ｼ繝繝ｼ縲・
 */


////////////////////////////////////////////////
// 螳壽焚繝舌ャ繝輔ぃ縲・
////////////////////////////////////////////////
//繝｢繝・Ν逕ｨ縺ｮ螳壽焚繝舌ャ繝輔ぃ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

//繝ｩ繧､繝医ョ繝ｼ繧ｿ縺ｫ繧｢繧ｯ繧ｻ繧ｹ縺吶ｋ縺溘ａ縺ｮ螳壽焚繝舌ャ繝輔ぃ繧堤畑諢上☆繧九・
cbuffer DirectionLightCb : register(b1)
{
	//繝・ぅ繝ｬ繧ｯ繧ｷ繝ｧ繝ｳ繝ｩ繧､繝育畑螟画焚
    float3 ligDirection;
    float3 ligColor;
	
	//繝昴う繝ｳ繝医Λ繧､繝育畑螟画焚
    float3 ptPosition; // 繝昴う繝ｳ繝医Λ繧､繝医・菴咲ｽｮ縲・
    float3 ptColor; // 繝昴う繝ｳ繝医Λ繧､繝医・繧ｫ繝ｩ繝ｼ縲・
    float ptRange; // 繝昴う繝ｳ繝医Λ繧､繝医・蠖ｱ髻ｿ遽・峇縲・
	
	//繧ｹ繝昴ャ繝医Λ繧､繝育畑螟画焚縲・
    float3 spPosition; // 繧ｹ繝昴ャ繝医Λ繧､繝医・菴咲ｽｮ縲・
    float3 spColor; // 繧ｹ繝昴ャ繝医Λ繧､繝医・繧ｫ繝ｩ繝ｼ縲・
    float spRange; // 繧ｹ繝昴ャ繝医Λ繧､繝医・蟆・・遽・峇縲・
    float3 spDirection; // 繧ｹ繝昴ャ繝医Λ繧､繝医・蟆・・譁ｹ蜷代・
    float spAngle; // 繧ｹ繝昴ャ繝医Λ繧､繝医・蟆・・隗貞ｺｦ縲・

	
	//隕也せ縺ｮ繝・・繧ｿ縺ｫ繧｢繧ｯ繧ｻ繧ｹ縺吶ｋ縺溘ａ縺ｮ螟画焚繧貞ｮ壽焚繝舌ャ繝輔ぃ縺ｫ逋ｻ骭ｲ
    float3 eyePos;
    float3 ambientLight; //迺ｰ蠅・・

     //蜊顔帥繝ｩ繧､繝医・繝・・繧ｿ縺ｫ繧｢繧ｯ繧ｻ繧ｹ縺吶ｋ縺溘ａ縺ｮ螟画焚繧定ｿｽ蜉
    float3 groundColor; // 辣ｧ繧願ｿ斐＠縺ｮ繝ｩ繧､繝・
    float3 skyColor; // 螟ｩ逅・Λ繧､繝・
    float3 groundNormal; // 蝨ｰ髱｢縺ｮ豕慕ｷ・
}
////////////////////////////////////////////////
// 讒矩菴・
////////////////////////////////////////////////
//繧ｹ繧ｭ繝九Φ繧ｰ逕ｨ縺ｮ鬆らせ繝・・繧ｿ繧偵・縺ｨ縺ｾ縺ｨ繧√・
struct SSkinVSIn{
	int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};
//鬆らせ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｸ縺ｮ蜈･蜉帙・
struct SVSIn{
	float4 pos 		: POSITION;		//繝｢繝・Ν縺ｮ鬆らせ蠎ｧ讓吶・
	float2 uv 		: TEXCOORD0;	//UV蠎ｧ讓吶・
	SSkinVSIn skinVert;				//繧ｹ繧ｭ繝ｳ逕ｨ縺ｮ繝・・繧ｿ縲・
    float3 normal : NORMAL;
    //鬆らせ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｮ蜈･蜉帙↓謗･繝吶け繝医Ν縺ｨ蠕薙・繧ｯ繝医Ν繧定ｿｽ蜉
    float3 tangent : TANGENT;
    float3 biNormal : BINORMAL;
};
//繝斐け繧ｻ繝ｫ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｸ縺ｮ蜈･蜉帙・
struct SPSIn{
	float4 pos 			: SV_POSITION;	//繧ｹ繧ｯ繝ｪ繝ｼ繝ｳ遨ｺ髢薙〒縺ｮ繝斐け繧ｻ繝ｫ縺ｮ蠎ｧ讓吶・
	float2 uv 			: TEXCOORD0;	//uv蠎ｧ讓吶・
    float3 worldPos     : TEXCOORD1;
    float3 normal       : NORMAL;
    float3 tangent      : TANGENT; // 謗･繝吶け繝医Ν
    float3 biNormal     : BINORMAL; // 蠕薙・繧ｯ繝医Ν
    float3 normalInView : TEXCOORD2;//繧ｫ繝｡繝ｩ遨ｺ髢薙・豕慕ｷ壹・
   
};

////////////////////////////////////////////////
// 繧ｰ繝ｭ繝ｼ繝舌Ν螟画焚縲・
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0); //繧｢繝ｫ繝吶ラ繝槭ャ繝励・
Texture2D<float4> g_normalMap : register(t1);//豕慕ｷ壹・繝・・縺ｫ繧｢繧ｯ繧ｻ繧ｹ縺吶ｋ縺溘ａ縺ｮ螟画焚縲・
Texture2D<float4> g_specularMap : register(t2);//繧ｹ繝壹く繝･繝ｩ繝槭ャ繝励↓繧｢繧ｯ繧ｻ繧ｹ縺吶ｋ縺溘ａ縺ｮ螟画焚縲・
Texture2D<float4> g_aoMap:register(t10);//AO繝槭ャ繝怜盾辣ｧ逕ｨ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//繝懊・繝ｳ陦悟・縲・

sampler g_sampler : register(s0);	//繧ｵ繝ｳ繝励Λ繧ｹ繝・・繝医・

////////////////////////////////////////////////
// 髢｢謨ｰ螳夂ｾｩ縲・
////////////////////////////////////////////////
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);
float3 CalcLigFromDirectionLight(SPSIn psIn);//繝・ぅ繝ｬ繧ｯ繧ｷ繝ｧ繝ｳ繝ｩ繧､繝医・
float3 CalcLigFromPointLight(SPSIn psIn); //繝昴う繝ｳ繝医Λ繧､繝茨ｼ井ｻ翫・1蛟九・縺ｿ縺縺瑚ｿｽ蜉縺吶ｋ縺ｪ繧牙ｼ墓焚縺ｮ霑ｽ蜉繧抵ｼ峨・
float3 CalcLigFromSpotLight(SPSIn psIn);//繧ｹ繝昴ャ繝医Λ繧､繝医↓繧医ｋ繝ｩ繧､繝・ぅ繝ｳ繧ｰ縺ｮ險育ｮ励・
float3 CalcLimPower(SPSIn psIn);//繝ｪ繝繝ｩ繧､繝医・
float3 CalcLigFromHemiSphereLight(SPSIn psIn);//蜊顔帥繝ｩ繧､繝医・
float3 CalcNormal(float3 normal, float3 tangent, float3 biNormal, float2 uv);//豕慕ｷ壹・險育ｮ励・
float3 CalcNormalMap(SPSIn psIn);//豕慕ｷ壹・繝・・縺ｮ險育ｮ励・
float3 CalcSpeculerMap(SPSIn psIn);//繧ｹ繝壹く繝･繝ｩ繝槭ャ繝励・險育ｮ励・
float3 CalcAnbientPower(SPSIn psIn);//AO繝槭ャ繝励°繧臥腸蠅・・縺ｮ蠑ｷ縺輔ｒ險育ｮ励・

/// <summary>
//繧ｹ繧ｭ繝ｳ陦悟・繧定ｨ育ｮ励☆繧九・
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
/// 鬆らせ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｮ繧ｳ繧｢髢｢謨ｰ縲・
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
	psIn.pos = mul(m, vsIn.pos);//繝｢繝・Ν縺ｮ鬆らせ繧偵Ρ繝ｼ繝ｫ繝牙ｺｧ讓咏ｳｻ縺ｫ螟画鋤縲・
    psIn.worldPos = psIn.pos;
	psIn.pos = mul(mView, psIn.pos);//繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓咏ｳｻ縺九ｉ繧ｫ繝｡繝ｩ蠎ｧ讓咏ｳｻ縺ｫ螟画鋤縲・
	psIn.pos = mul(mProj, psIn.pos);//繧ｫ繝｡繝ｩ蠎ｧ讓咏ｳｻ縺九ｉ繧ｹ繧ｯ繝ｪ繝ｼ繝ｳ蠎ｧ讓咏ｳｻ縺ｫ螟画鋤縲・

	//鬆らせ豕慕ｷ壹ｒ繝斐け繧ｻ繝ｫ繧ｷ繧ｧ繝ｼ繝縺ｫ貂｡縺吶・
    psIn.normal = normalize(mul(m, vsIn.normal));
    
	//謗･繝吶け繝医Ν縺ｨ蠕薙・繧ｯ繝医Ν繧偵Ρ繝ｼ繝ｫ繝臥ｩｺ髢薙↓螟画鋤縺吶ｋ
    psIn.tangent = normalize(mul(m, vsIn.tangent));
    psIn.biNormal = normalize(mul(m, vsIn.biNormal));
	psIn.uv = vsIn.uv;
    
    psIn.normalInView = mul(mView, psIn.normal); //繧ｫ繝｡繝ｩ遨ｺ髢薙・豕慕ｷ壹ｒ豎ゅａ繧九・

    
	return psIn;
}

/// <summary>
/// 繧ｹ繧ｭ繝ｳ縺ｪ縺励Γ繝・す繝･逕ｨ縺ｮ鬆らせ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｮ繧ｨ繝ｳ繝医Μ繝ｼ髢｢謨ｰ縲・
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, false);
}
/// <summary>
/// 繧ｹ繧ｭ繝ｳ縺ゅｊ繝｡繝・す繝･縺ｮ鬆らせ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｮ繧ｨ繝ｳ繝医Μ繝ｼ髢｢謨ｰ縲・
/// </summary>
SPSIn VSSkinMain( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, true);
}
/// <summary>
/// 繝斐け繧ｻ繝ｫ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｮ繧ｨ繝ｳ繝医Μ繝ｼ髢｢謨ｰ縲・
/// </summary>
float4 PSMain( SPSIn psIn ) : SV_Target0
{
	 // 繝・ぅ繝ｬ繧ｯ繧ｷ繝ｧ繝ｳ繝ｩ繧､繝医↓繧医ｋ繝ｩ繧､繝・ぅ繝ｳ繧ｰ繧定ｨ育ｮ励☆繧・
    float3 directionLig = CalcLigFromDirectionLight(psIn);

    // 繝昴う繝ｳ繝医Λ繧､繝医↓繧医ｋ繝ｩ繧､繝・ぅ繝ｳ繧ｰ繧定ｨ育ｮ励☆繧・
    float3 pointLig = CalcLigFromPointLight(psIn);
    
    //繧ｹ繝昴ャ繝医Λ繧､繝医↓繧医ｋ繝ｩ繧､繝・ぅ繝ｳ繧ｰ縺ｮ險育ｮ励・
    float3 spotLig = CalcLigFromSpotLight(psIn);
   
   //繝ｪ繝繝ｩ繧､繝医・蠑ｷ縺輔ｒ豎ゅａ繧九・
    float3 limColor = CalcLimPower(psIn);
    
    //蜊顔帥繝ｩ繧､繝医・險育ｮ励・
    float3 hemiLight = CalcLigFromHemiSphereLight(psIn);
   
    //豕慕ｷ壹・繝・・縺ｮ險育ｮ励・
    float3 normalMap = CalcNormalMap(psIn);
  
    //繧ｹ繝壹く繝･繝ｩ繝槭ャ繝励・險育ｮ励・
    float3 speculerMap = CalcSpeculerMap(psIn);
    
    //AO繝槭ャ繝励↓繧医ｋ迺ｰ蠅・・縺ｮ蠑ｷ縺輔ｒ險育ｮ励・
    float3 aoMap = CalcAnbientPower(psIn);
    
    //繝・ぅ繝ｬ繧ｯ繧ｷ繝ｧ繝ｳ縲√・繧､繝ｳ繝医√せ繝昴ャ繝医∫腸蠅・・縲∝濠逅・∵ｳ慕ｷ壹・繝・・縲√せ繝壹く繝･繝ｩ繝槭ャ繝・
    //繧貞粋邂励＠縺ｦ譛邨ら噪縺ｪ蜿榊ｰ・・繧呈ｱゅａ繧九・
    float3 allLightFinalLig = directionLig + pointLig + spotLig + ambientLight + hemiLight+normalMap+speculerMap;
  
   //譛邨ら噪縺ｪ蜿榊ｰ・・縺ｫ繝ｪ繝縺ｮ蜿榊ｰ・・繧貞粋邂励☆繧九・
    //・医☆縺ｹ縺ｦ縺ｮ繝ｩ繧､繝茨ｼ・
    allLightFinalLig += limColor;
   
    //繝・け繧ｹ繝√Ε縺九ｉ繧ｫ繝ｩ繝ｼ繧呈戟縺｣縺ｦ縺上ｋ
	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);
	
	//譛邨ら噪縺ｪ蜃ｺ蜉帙き繝ｩ繝ｼ縺ｫ蜈峨ｒ荵礼ｮ励☆繧九・
   albedoColor.xyz *= allLightFinalLig;
 
	return albedoColor;
}
/// <summary>
/// Lambert諡｡謨｣蜿榊ｰ・・險育ｮ励・
/// <summary>
float3 CalcLambertDiffuse(float3 lightDire, float3 lightColor, float3 normal)
{
	// 繝斐け繧ｻ繝ｫ縺ｮ豕慕ｷ壹→繝ｩ繧､繝医・譁ｹ蜷代・蜀・ｩ阪ｒ險育ｮ励☆繧・
    float t = dot(normal, lightDire) * -1.0f;

    // 蜀・ｩ阪・蛟､繧・莉･荳翫・蛟､縺ｫ縺吶ｋ
    t = max(0.0f, t);

    // 諡｡謨｣蜿榊ｰ・・繧定ｨ育ｮ励☆繧・
    return lightColor * t;
}

/// <summary>
/// Phong髀｡髱｢蜿榊ｰ・・繧定ｨ育ｮ励☆繧・
/// </summary>
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
    // 蜿榊ｰ・・繧ｯ繝医Ν繧呈ｱゅａ繧・
    float3 refVec = reflect(lightDirection, normal);

    // 蜈峨′蠖薙◆縺｣縺溘し繝ｼ繝輔ぉ繧､繧ｹ縺九ｉ隕也せ縺ｫ莨ｸ縺ｳ繧九・繧ｯ繝医Ν繧呈ｱゅａ繧・
    float3 toEye = eyePos - worldPos;
    toEye = normalize(toEye);

    // 髀｡髱｢蜿榊ｰ・・蠑ｷ縺輔ｒ豎ゅａ繧・
    float t = dot(refVec, toEye);

    // 髀｡髱｢蜿榊ｰ・・蠑ｷ縺輔ｒ0莉･荳翫・謨ｰ蛟､縺ｫ縺吶ｋ
    t = max(0.0f, t);

    // 髀｡髱｢蜿榊ｰ・・蠑ｷ縺輔ｒ邨槭ｋ
    t = pow(t, 5.0f);

    // 髀｡髱｢蜿榊ｰ・・繧呈ｱゅａ繧・
    return lightColor * t;
}

/// 繝・ぅ繝ｬ繧ｯ繧ｷ繝ｧ繝ｳ繝ｩ繧､繝医↓繧医ｋ蜿榊ｰ・・繧定ｨ育ｮ・
float3 CalcLigFromDirectionLight(SPSIn psIn)
{
    // 繝・ぅ繝ｬ繧ｯ繧ｷ繝ｧ繝ｳ繝ｩ繧､繝医↓繧医ｋLambert諡｡謨｣蜿榊ｰ・・繧定ｨ育ｮ励☆繧・
    float3 diffDirection = CalcLambertDiffuse(ligDirection, ligColor, psIn.normal);

    // 繝・ぅ繝ｬ繧ｯ繧ｷ繝ｧ繝ｳ繝ｩ繧､繝医↓繧医ｋPhong髀｡髱｢蜿榊ｰ・・繧定ｨ育ｮ励☆繧・
    float3 specDirection = CalcPhongSpecular(ligDirection, ligColor, psIn.worldPos, psIn.normal);
    
    return diffDirection + specDirection;
}
//繝昴う繝ｳ繝医Λ繧､繝医↓繧医ｋ蜿榊ｰ・・繧定ｨ育ｮ励☆繧九・
float3 CalcLigFromPointLight(SPSIn psIn)
{
    // 縺薙・繧ｵ繝ｼ繝輔ぉ繧､繧ｹ縺ｫ蜈･蟆・＠縺ｦ縺・ｋ繝昴う繝ｳ繝医Λ繧､繝医・蜈峨・蜷代″繧定ｨ育ｮ励☆繧・
    float3 ligDir = psIn.worldPos - ptPosition;

    // 豁｣隕丞喧縺励※螟ｧ縺阪＆1縺ｮ繝吶け繝医Ν縺ｫ縺吶ｋ
    ligDir = normalize(ligDir);

    // 貂幄｡ｰ縺ｪ縺励・Lambert諡｡謨｣蜿榊ｰ・・繧定ｨ育ｮ励☆繧・
    float3 diffPoint = CalcLambertDiffuse(
        ligDir, // 繝ｩ繧､繝医・譁ｹ蜷・
        ptColor, // 繝ｩ繧､繝医・繧ｫ繝ｩ繝ｼ
        psIn.normal // 繧ｵ繝ｼ繝輔ぉ繧､繧ｹ縺ｮ豕慕ｷ・
    );

    // 貂幄｡ｰ縺ｪ縺励・Phong髀｡髱｢蜿榊ｰ・・繧定ｨ育ｮ励☆繧・
    float3 specPoint = CalcPhongSpecular(
        ligDir, // 繝ｩ繧､繝医・譁ｹ蜷・
        ptColor, // 繝ｩ繧､繝医・繧ｫ繝ｩ繝ｼ
        psIn.worldPos, // 繧ｵ繝ｼ繝輔ぉ繧､繧ｺ縺ｮ繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・
        psIn.normal     // 繧ｵ繝ｼ繝輔ぉ繧､繧ｺ縺ｮ豕慕ｷ・
    );

    // 霍晞屬縺ｫ繧医ｋ蠖ｱ髻ｿ邇・ｒ險育ｮ励☆繧・
    // 繝昴う繝ｳ繝医Λ繧､繝医→縺ｮ霍晞屬繧定ｨ育ｮ励☆繧・
    float3 distance = length(psIn.worldPos - ptPosition);

    // 蠖ｱ髻ｿ邇・・霍晞屬縺ｫ豈比ｾ九＠縺ｦ蟆上＆縺上↑縺｣縺ｦ縺・￥
    float affect = 1.0f - 1.0f / ptRange * distance;

    // 蠖ｱ髻ｿ蜉帙′繝槭う繝翫せ縺ｫ縺ｪ繧峨↑縺・ｈ縺・↓陬懈ｭ｣繧偵°縺代ｋ
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }

    // 蠖ｱ髻ｿ縺ｮ莉墓婿繧呈欠謨ｰ髢｢謨ｰ逧・↓縺吶ｋ縲ゆｻ雁屓縺ｮ繧ｵ繝ｳ繝励Ν縺ｧ縺ｯ3荵励＠縺ｦ縺・ｋ
    affect = pow(affect, 3.0f);

    // 諡｡謨｣蜿榊ｰ・・縺ｨ髀｡髱｢蜿榊ｰ・・縺ｫ貂幄｡ｰ邇・ｒ荵礼ｮ励＠縺ｦ蠖ｱ髻ｿ繧貞ｼｱ繧√ｋ
    diffPoint *= affect;
    specPoint *= affect;

    return diffPoint + specPoint;
}

 //繧ｹ繝昴ャ繝医Λ繧､繝医↓繧医ｋ繝ｩ繧､繝・ぅ繝ｳ繧ｰ繧定ｨ育ｮ励☆繧九・
float3 CalcLigFromSpotLight(SPSIn psIn)
{
    //繧ｵ繝ｼ繝輔ぉ繝ｼ繧ｹ縺ｫ蜈･蟆・☆繧九せ繝昴ャ繝医Λ繧､繝医・蟷ｹ繧定ｨ育ｮ励・
    float3 ligDir = psIn.worldPos - spPosition;
	
	//豁｣隕丞喧縺励※螟ｧ縺阪＆・代・繝吶け繝医Ν縺ｫ縺吶ｋ縲・
    ligDir = normalize(ligDir);
	
	//貂幄｡ｰ縺ｪ縺励・Lambert諡｡謨｣蜿榊ｰ・・繧定ｨ育ｮ励・
    float3 diffSpotLight = CalcLambertDiffuse(
		ligDir, //繝ｩ繧､繝医・譁ｹ蜷代・
		spColor, //繝ｩ繧､繝医・繧ｫ繝ｩ繝ｼ縲・
		psIn.normal	//繧ｵ繝ｼ繝輔ぉ繝ｼ繧ｹ縺ｮ豕慕ｷ壹・
	);
	
	//貂幄｡ｰ縺ｪ縺励・Phong髀｡髱｢蜿榊ｰ・・繧定ｨ育ｮ励・
    float3 specSpotLight = CalcPhongSpecular(
		ligDir, //繝ｩ繧､繝医・譁ｹ蜷代・
		spColor, //繝ｩ繧､繝医・繧ｫ繝ｩ繝ｼ縲・
		psIn.worldPos, //繧ｵ繝ｼ繝輔ぉ繝ｼ繧ｹ縺ｮ繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・
		psIn.normal		 //繧ｵ繝ｼ繝輔ぉ繝ｼ繧ｹ縺ｮ豕慕ｷ壹・
	);
	
	
	//霍晞屬縺ｫ繧医ｋ蠖ｱ髻ｿ邇・ｒ險育ｮ励☆繧九・
	//繧ｹ繝昴ャ繝医Λ繧､繝医・霍晞屬繧定ｨ育ｮ励☆繧九・
    float distance = length(psIn.worldPos - spPosition);
	
	//蠖ｱ髻ｿ邇・・霍晞屬縺ｫ豈比ｾ九＠縺ｦ蟆上＆縺上↑繧九・
    float affect = 1.0f - 1.0f / spRange * distance;
	
	//蠖ｱ髻ｿ蜉帙′繝槭う繝翫せ縺ｫ縺ｪ繧峨↑縺・ｈ縺・↓陬懈ｭ｣繧偵°縺代ｋ縲・
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }
	
	//蠖ｱ髻ｿ蜉帙ｒ謖・焚髢｢謨ｰ縺ｫ縺吶ｋ縲・荵励↓縺励※繧九・
    affect = pow(affect, 3.0f);
	
	//諡｡謨｣蜿榊ｰ・・縺ｨ髀｡髱｢蜿榊ｰ・・縺ｫ蠖ｱ髻ｿ蜉帙ｒ荵礼ｮ励＠縺ｦ蠖ｱ髻ｿ繧貞ｼｱ繧√ｋ縲・
    diffSpotLight *= affect;
    specSpotLight *= affect;
    
	//蜈･蟆・・縺ｨ蟆・・譁ｹ蜷代・隗貞ｺｦ繧呈ｱゅａ繧・
    // dot()繧貞茜逕ｨ縺励※蜀・ｩ阪ｒ豎ゅａ繧・
    float angle = dot(ligDir, spDirection);

    // dot()縺ｧ豎ゅａ縺溷､繧誕cos()縺ｫ貂｡縺励※隗貞ｺｦ繧呈ｱゅａ繧・
    angle = abs(acos(angle));

    //隗貞ｺｦ縺ｫ繧医ｋ蠖ｱ髻ｿ邇・ｒ豎ゅａ繧・
    // 隗貞ｺｦ縺ｫ豈比ｾ九＠縺ｦ蟆上＆縺上↑縺｣縺ｦ縺・￥蠖ｱ髻ｿ邇・ｒ險育ｮ励☆繧・
    affect = 1.0f - 1.0f / spAngle * angle;

    // 蠖ｱ髻ｿ邇・′繝槭う繝翫せ縺ｫ縺ｪ繧峨↑縺・ｈ縺・↓陬懈ｭ｣繧偵°縺代ｋ
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }

    //蠖ｱ髻ｿ縺ｮ莉墓婿繧呈欠謨ｰ髢｢謨ｰ逧・↓縺吶ｋ縲・
    affect = pow(affect, 0.5f);

    //隗貞ｺｦ縺ｫ繧医ｋ蠖ｱ髻ｿ邇・ｒ蜿榊ｰ・・縺ｫ荵礼ｮ励＠縺ｦ縲∝ｽｱ髻ｿ繧貞ｼｱ繧√ｋ
    diffSpotLight *= affect;
    specSpotLight *= affect;
    return diffSpotLight + specSpotLight;
	
}

//繝ｪ繝繝ｩ繧､繝医・蠑ｷ縺輔ｒ險育ｮ励☆繧九・
float3 CalcLimPower(SPSIn psIn)
{
    /// //繧ｵ繝ｼ繝輔ぉ繝ｼ繧ｹ縺ｮ豕慕ｷ壹→蜈峨・蜈･蟆・婿蜷代↓萓晏ｭ倥☆繧九Μ繝縺ｮ蠑ｷ縺輔ｒ豎ゅａ繧九・
    float power1 = 1.0f - max(0.0f, dot(ligDirection, psIn.normal));
    
   // //繧ｵ繝ｼ繝輔ぉ繝ｼ繧ｹ縺ｮ豕慕ｷ壹→隕也ｷ壹・譁ｹ蜷代↓萓晏ｭ倥☆繧九Μ繝縺ｮ蠑ｷ縺輔ｒ豎ゅａ繧九・
    float power2 = 1.0f - max(0.0f, psIn.normalInView.z * -1.0f);
    
   // //譛邨ら噪縺ｪ繝ｪ繝縺ｮ蠑ｷ縺輔ｒ豎ゅａ繧九・
    float limPower = power1 * power2;
    
   // //pow()繧剃ｽｿ逕ｨ縺励※蠑ｷ縺輔・螟牙喧繧呈欠謨ｰ髢｢謨ｰ逧・↓縺吶ｋ縲・
    limPower = pow(limPower, 1.3f);
    
    //繝ｪ繝繝ｩ繧､繝医・繧ｫ繝ｩ繝ｼ繧定ｨ育ｮ励☆繧九・
    float3 limColor = limPower * ligColor;
    
    return limColor;
}

//蜊顔帥繝ｩ繧､繝医・蠑ｷ縺輔ｒ險育ｮ励☆繧九・
float3 CalcLigFromHemiSphereLight(SPSIn psIn)
{
    //蜊顔帥繝ｩ繧､繝医・險育ｮ励・
    //繧ｵ繝ｼ繝輔ぉ繝ｼ繧ｹ縺ｮ豕慕ｷ壹→蝨ｰ髱｢縺ｮ豕慕ｷ壹→縺ｮ蜀・ｩ阪ｒ險育ｮ励☆繧九・
    float t = dot(psIn.normal, groundNormal);
    
    //蜀・ｩ阪・邨先棡繧・・・縺ｮ遽・峇縺ｫ螟画鋤縺吶ｋ縲・
    t = (t + 1.0f) / 2.0f;
    
    //蝨ｰ髱｢濶ｲ縺ｨ螟ｩ逅・牡繧定｣懷ｮ檎紫・斐〒邱壼ｽ｢陬懷ｮ後☆繧九・
    float3 hemiLight = lerp(groundColor, skyColor, t);

    return hemiLight;
}

//豕慕ｷ壹・險育ｮ励・
float3 CalcNormal(float3 normal, float3 tangent, float3 biNormal, float2 uv)
{
    float3 spaceNormal = g_normalMap.SampleLevel(g_sampler, uv, 0.0f).xyz;
    spaceNormal = (spaceNormal * 2.0f) - 1.0f;
    
    float3 newNormal = tangent * spaceNormal.x + biNormal * spaceNormal.y + normal * spaceNormal.z;

    return newNormal;
}

//豕慕ｷ壹・繝・・縺ｮ險育ｮ励・
float3 CalcNormalMap(SPSIn psIn)
{
    // 繝・ぅ繝輔Η繝ｼ繧ｺ繝槭ャ繝励ｒ繧ｵ繝ｳ繝励Μ繝ｳ繧ｰ
    float4 diffuseMap = g_albedo.Sample(g_sampler, psIn.uv);
    float3 normal = psIn.normal;

    //豕慕ｷ壹・繝・・縺九ｉ繧ｿ繝ｳ繧ｸ繧ｧ繝ｳ繝医せ繝壹・繧ｹ縺ｮ豕慕ｷ壹ｒ繧ｵ繝ｳ繝励Μ繝ｳ繧ｰ縺吶ｋ
    float3 localNormal = g_normalMap.Sample(g_sampler, psIn.uv).xyz;

    // 繧ｿ繝ｳ繧ｸ繧ｧ繝ｳ繝医せ繝壹・繧ｹ縺ｮ豕慕ｷ壹ｒ0・・縺ｮ遽・峇縺九ｉ-1・・縺ｮ遽・峇縺ｫ蠕ｩ蜈・☆繧・
    localNormal = (localNormal - 0.5f) * 2.0f;

    //繧ｿ繝ｳ繧ｸ繧ｧ繝ｳ繝医せ繝壹・繧ｹ縺ｮ豕慕ｷ壹ｒ繝ｯ繝ｼ繝ｫ繝峨せ繝壹・繧ｹ縺ｫ螟画鋤縺吶ｋ
    normal = psIn.tangent * localNormal.x + psIn.biNormal * localNormal.y + normal * localNormal.z;
    
    // 諡｡謨｣蜿榊ｰ・・繧定ｨ育ｮ励☆繧・
    return max(0.0f, dot(normal, -ligDirection)) * ligColor;
}

//繧ｹ繝壹く繝･繝ｩ繝槭ャ繝励・險育ｮ励・
float3 CalcSpeculerMap(SPSIn psIn)
{
    //繝・ぅ繝輔Η繝ｼ繧ｺ繝槭ャ繝励ｒ繧ｵ繝ｳ繝励Μ繝ｳ繧ｰ縲・
    float4 diffuseMap = g_albedo.Sample(g_sampler, psIn.uv);
    //繝弱・繝槭Ν繝槭ャ繝励ｒ繧ゅ→縺ｫ豕慕ｷ壹ｒ險育ｮ励・
    float3 normal = CalcNormal(psIn.normal, psIn.tangent, psIn.biNormal, psIn.uv);
    //諡｡謨｣蜿榊ｰ・・繧定ｨ育ｮ・髢｢謨ｰ縺､縺九∴繧九°縺ｪ)縲・
    float3 diffuseLig = max(0.0f, dot(normal, -ligDirection)) * ligColor;
    
    //髀｡髱｢蜿榊ｰ・・繧定ｨ育ｮ励・
    //蜿榊ｰ・・繧ｯ繝医Ν縺ｮ險育ｮ励・
    float3 refVec = reflect(ligDirection, normal);
    //蜈峨′蠖薙◆縺｣縺溘し繝ｼ繝輔ぉ繝ｼ繧ｹ縺九▲繧芽ｦ也せ縺ｫ莨ｸ縺ｳ繧九・繧ｯ繝医Ν繧呈ｱゅａ繧九・
    float3 toEye = eyePos - psIn.worldPos;
    toEye = normalize(toEye);
    //髀｡髱｢蜿榊ｰ・・蠑ｷ縺輔ｒ豎ゅａ繧九・
    float t = saturate(dot(refVec, toEye));
    //髀｡髱｢蜿榊ｰ・・蠑ｷ縺輔ｒ邨槭ｋ縲・
    t = pow(t, 5.0f);
    //髀｡髱｢蜿榊ｰ・ｒ豎ゅａ繧九・
    float3 specLig = ligDirection * t;
    
    //繧ｹ繝壹く繝･繝ｩ繝槭ャ繝励せ繝壹く繝･繝ｩ蜿榊ｰ・・蠑ｷ縺輔ｒ繧ｵ繝ｳ繝励Μ繝ｳ繧ｰ縲・
    float specPower = g_specularMap.Sample(g_sampler, psIn.uv).r;
    //髀｡髱｢蜿榊ｰ・・蠑ｷ縺輔ｒ髀｡髱｢蜿榊ｰ・・縺ｫ荵礼ｮ励☆繧九・
    specLig * specPower * 50.0f; //蛟咲紫螟峨∴繧九→蜈峨ｊ譁ｹ縺悟､峨ｏ繧九・
   
    return specLig;
}

float3 CalcAnbientPower(SPSIn psIn)
{
    float3 ambient = ambientLight;
    float ambientPower = g_aoMap.Sample(g_sampler, psIn.uv);
    ambient *= ambientPower;
    
    return ambient;
}