cbuffer cb : register(b0)
{
    float4x4 mvp; //MVP行列。
    float4 mulColor; //乗算カラー。
};

struct VSInput
{
    float4 pos : POSITION;
    float2 uv : TEXCOORD0;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

//頂点シェーダー
PSInput VSMain(VSInput In)
{
    PSInput psIn;
    psIn.pos = mul(mvp, In.pos);
    psIn.uv = In.uv;
    return psIn;
}

Texture2D<float4> mainRenderTargetTexture : register(t0); // メインレンダリングターゲットのテクスチャ。
sampler Sampler : register(s0);

//輝度抽出用ピクセルシェーダ。
float4 PSSamplingLuminance(PSInput In):SV_Target0
{
    // メインレンダリングターゲットからカラーをサンプリング
    float4 color = mainRenderTargetTexture.Sample(Sampler, In.uv);

    // サンプリングしたカラーの明るさを計算
    float t = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f));
    //float t = dot(color.xyz, float3(0.299f, 0.587f, 0.114f));

    // clip()関数は引数の値がマイナスになると、以降の処理をスキップする
    // なので、マイナスになるとピクセルカラーは出力されない
    // 今回の実装はカラーの明るさが1以下ならピクセルキルする
    //clip(t - 0.85f);//調整した値。
    clip(t - 1.0f);//ブルーム確認用。

    return color;
}

//ボケ画像にアクセスするための変数を追加。
Texture2D<float4> g_bokeTexture_0 : register(t0);
Texture2D<float4> g_bokeTexture_1 : register(t1);
Texture2D<float4> g_bokeTexture_2 : register(t2);
Texture2D<float4> g_bokeTexture_3 : register(t3);


float4 PSBloomFinal(PSInput In) : SV_Target0
{
    //ボケ画像をサンプリングして、平均をとって出力する。
    float4 combineColor = g_bokeTexture_0.Sample(Sampler, In.uv);
    combineColor += g_bokeTexture_1.Sample(Sampler, In.uv);
    combineColor += g_bokeTexture_2.Sample(Sampler, In.uv);
    combineColor += g_bokeTexture_3.Sample(Sampler, In.uv);
    combineColor /= 4.0f;
    //ブルームの強さを0.5倍に調整
    combineColor.rgb *= 0.5f;
    combineColor.a = 1.0f;
    return combineColor;
}