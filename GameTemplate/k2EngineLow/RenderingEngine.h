#pragma once
#include "Bloom.h"
#include "Light.h"

namespace nsK2EngineLow {

	class FontRender;
	class ModelRender;
	class SpriteRender;
	class Bloom;

	class RenderingEngine :public Noncopyable
	{
	public:
		RenderingEngine();
		bool Start();
		void InitFinalSprite();
		void Init2DSprite();
		void Execute(RenderContext&rc);
		void ModelDraw(RenderContext& rc);
		void SpriteFontDraw(RenderContext& rc);
		void CopyMainRenderTargetToFrameBuffer(RenderContext& rc);

		void InitShadowMap();//シャドウマップ描画用のレンダリングターゲットの作成。
		void InitZPrepassRenderTarget();
		void ZPrepass(RenderContext& rc);
		void ShadowDraw(RenderContext& rc);

		void AddModelRenderObject(ModelRender* modelRender)
		{
			ModelRenderObject.push_back(modelRender);
		}

		void AddSpriteRenderObject(SpriteRender* spriteRender)
		{
			SpriteRenderObject.push_back(spriteRender);
		}

		void AddFontRenderObject(FontRender* fontRender)
		{
			FontRenderObject.push_back(fontRender);
		}


		//ZPrepassの描画パスにモデルを追加
		void Add3DModelToZPrepass(Model& model)
		{
			m_zprepassModelsObject.push_back(&model);
		}

		Camera& GetLightCamera()
		{
			return lightCamera;
		}

		Light* GetLightingCB()
		{
			return m_light;
		}

		SceneLight& GetLightCB()
		{
			return m_light->GetLight();
		}
		
		//ZPrepassで作成された深度テクスチャを取得
		Texture& GetZPrepassDepthTexture()
		{
			return m_zprepassRenderTarget.GetRenderTargetTexture();
		}

		RenderTarget& GetShadowTarget()
		{
			return shadowMapTarget;
		}

		
		//ライトビュースクリーンの設定
		void SetLVP(Matrix mat)
		{
			// 正射影の設定
			lightCamera.SetWidth(50.0f);   // 表示領域の幅
			lightCamera.SetHeight(50.0f);  // 表示領域の高さ
			lightCamera.SetNear(1.0f);
			lightCamera.SetFar(100.0f);
			lightCamera.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);

			// Update でビュー・プロジェクション行列を作成
			lightCamera.Update();

		}
	private:
		//このクラスでライトの初期化をできるように変更したあとModelRenderのコンストラクタ内のNewGOを消す。

		Bloom m_bloom;
		Light *m_light;

		RenderTarget m_mainRenderingTarget;
		RenderTarget m_2DRenderTarget;
		Sprite m_mainSprite;
		Sprite m_2DSprite;
		SpriteInitData m_spriteInitData;
		Sprite m_copyToframeBufferSprite;
		RenderTarget m_zprepassRenderTarget;

		//シャドウ用
		RenderTarget shadowMapTarget;
		Camera lightCamera;
		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };	//カラーバッファーは真っ白

		std::vector<ModelRender*> ModelRenderObject;
		std::vector<SpriteRender*> SpriteRenderObject;
		std::vector<FontRender*> FontRenderObject;
		std::vector<Model* >		m_zprepassModelsObject;	// ZPrepassの描画パスで描画されるモデルのリスト


	};
}

