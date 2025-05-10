#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

nsK2EngineLow::RenderingEngine::RenderingEngine()
{
	//mainTargetセット。
	m_mainRenderingTarget.Create(
		g_graphicsEngine->GetFrameBufferWidth(),
		g_graphicsEngine->GetFrameBufferHeight(),
		1,
		1,
		DXGI_FORMAT_R32G32B32A32_FLOAT,				// カラーバッファのフォーマット
		DXGI_FORMAT_D32_FLOAT
	);

	//2D(フォントとスプライト)の初期化。
	Init2DSprite();

	//ブルームの初期化。
	m_bloom.Init(m_mainRenderingTarget);

	//最終的なテクスチャを貼り付けるためのスプライトを初期化。
	InitFinalSprite();
}

bool nsK2EngineLow::RenderingEngine::Start()
{
	return true;
}

void nsK2EngineLow::RenderingEngine::Init2DSprite()
{
	float clearColor[4] = { 0.0f,0.0f,0.0f,1.0f };

	//2D用のターゲットの初期化。
	m_2DRenderTarget.Create(
		m_mainRenderingTarget.GetWidth(),
		m_mainRenderingTarget.GetHeight(),
		1,
		1,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_FORMAT_UNKNOWN,
		clearColor
	);

	//最終合成用のスプライトを初期化する。
	SpriteInitData spriteInitData;
	//テクスチャは2Dレンダーターゲット。
	spriteInitData.m_textures[0] = &m_2DRenderTarget.GetRenderTargetTexture();
	// 解像度はmainRenderTargetの幅と高さ
	spriteInitData.m_width = m_mainRenderingTarget.GetWidth();
	spriteInitData.m_height = m_mainRenderingTarget.GetHeight();
	// 2D用のシェーダーを使用する
	spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
	spriteInitData.m_vsEntryPointFunc = "VSMain";
	spriteInitData.m_psEntryPoinFunc = "PSMain";
	//上書き。
	spriteInitData.m_alphaBlendMode = AlphaBlendMode_None;
	//レンダリングターゲットのフォーマット。
	spriteInitData.m_colorBufferFormat[0] = m_mainRenderingTarget.GetColorBufferFormat();

	m_2DSprite.Init(spriteInitData);

	//テクスチャはメインレンダ―ターゲット。
	spriteInitData.m_textures[0] = &m_mainRenderingTarget.GetRenderTargetTexture();

	//解像度は2Dレンダ―ターゲットの幅と高さ
	spriteInitData.m_width = m_2DRenderTarget.GetWidth();
	spriteInitData.m_height = m_2DRenderTarget.GetHeight();
	//レンダリングターゲットのフォーマット。
	spriteInitData.m_colorBufferFormat[0] = m_2DRenderTarget.GetColorBufferFormat();

	m_mainSprite.Init(spriteInitData);
}

void nsK2EngineLow::RenderingEngine::InitFinalSprite()
{
	m_spriteInitData.m_textures[0] = &m_mainRenderingTarget.GetRenderTargetTexture();
	m_spriteInitData.m_width = m_mainRenderingTarget.GetWidth();
	m_spriteInitData.m_height = m_mainRenderingTarget.GetHeight();
	m_spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
	m_copyToframeBufferSprite.Init(m_spriteInitData);
}

void nsK2EngineLow::RenderingEngine::Execute(RenderContext& rc)
{

	//rc.SetRenderTarget(m_mainRenderingTarget);
	//モデルの描画。
	ModelDraw(rc);

	//エフェクトの描画。
	EffectEngine::GetInstance()->Draw();

	//画像と文字の描画。
	SpriteFontDraw(rc);

	//ブルームの適用。
	m_bloom.Render(rc, m_mainRenderingTarget);

	//メインレンダリングターゲットの絵をフレームバッファにコピー。
	CopyMainRenderTargetToFrameBuffer(rc);

	//m_mainSprite.Draw(rc);

	//クリア。
	ModelRenderObject.clear();
	SpriteRenderObject.clear();
	FontRenderObject.clear();

}

void nsK2EngineLow::RenderingEngine::ModelDraw(RenderContext& rc)
{
	// メインのターゲットが使えるようになるまで待つ
	rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderingTarget);
	// ターゲットセット
	rc.SetRenderTargetAndViewport(m_mainRenderingTarget);
	// ターゲットのクリア
	rc.ClearRenderTargetView(m_mainRenderingTarget);

	// まとめてモデルレンダーを描画
	for (auto MobjData : ModelRenderObject) {
		MobjData->OnDraw(rc);
	}

	// 描画されるまで待つ
	rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderingTarget);
}

void nsK2EngineLow::RenderingEngine::SpriteFontDraw(RenderContext& rc)
{
	//2D用のターゲットが使えるようになるまで待つ。
	rc.WaitUntilToPossibleSetRenderTarget(m_2DRenderTarget);
	//ターゲットのセット。
	rc.SetRenderTargetAndViewport(m_2DRenderTarget);
	//ターゲットのクリア。
	rc.ClearRenderTargetView(m_2DRenderTarget);

	m_mainSprite.Draw(rc);

	//スプライトと文字の描画。
	for (auto SobjData : SpriteRenderObject) {
		SobjData->OnDraw(rc);
	}
	for (auto FobjData : FontRenderObject) {
		FobjData->OnDraw(rc);
	}

	// 描画されるまで待つ
	rc.WaitUntilFinishDrawingToRenderTarget(m_2DRenderTarget);
	//ターゲットをメインに戻す
	rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderingTarget);
	rc.SetRenderTargetAndViewport(m_mainRenderingTarget);
	m_2DSprite.Draw(rc);
	rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderingTarget);
}

void nsK2EngineLow::RenderingEngine::CopyMainRenderTargetToFrameBuffer(RenderContext& rc)
{
	//フレームバッファにセット。
	rc.SetRenderTarget(
		g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
		g_graphicsEngine->GetCurrentFrameBuffuerDSV()
	);
	
	m_copyToframeBufferSprite.Draw(rc);
}
