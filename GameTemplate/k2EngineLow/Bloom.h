#pragma once
namespace nsK2EngineLow {
	class Bloom:public IGameObject
	{
	public:
		Bloom();
		~Bloom();
		//初期化
		void Init(RenderTarget& renderTarget);
		void Update();
		//描画。
		void Render(RenderContext& rc, RenderTarget&renderTarget);




		//RenderTarget* mainRenderTarget;
		RenderTarget luminanceRenderTarget;
		
		SpriteInitData luminanceSpriteInitData;
		SpriteInitData finalSpriteInitData;
		Sprite m_luminanceSprite;
		Sprite m_finalSprite;
		GaussianBlur gaussianBulur[4];
	
	};
}
