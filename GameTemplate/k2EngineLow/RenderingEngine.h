#pragma once
#include "Bloom.h"
namespace nsK2EngineLow {

	class FontRender;
	class ModelRender;
	class SpriteRender;
	class Bloom;

	class RenderingEngine
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

	private:
		//このクラスでライトの初期化をできるように変更したあとModelRenderのコンストラクタ内のNewGOを消す。

		Bloom m_bloom;

		RenderTarget m_mainRenderingTarget;
		RenderTarget m_2DRenderTarget;
		Sprite m_mainSprite;
		Sprite m_2DSprite;
		SpriteInitData m_spriteInitData;
		Sprite m_copyToframeBufferSprite;


		std::vector<ModelRender*> ModelRenderObject;
		std::vector<SpriteRender*> SpriteRenderObject;
		std::vector<FontRender*> FontRenderObject;
		

	};
}

