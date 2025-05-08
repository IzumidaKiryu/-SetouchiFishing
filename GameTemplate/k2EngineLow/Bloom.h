#pragma once
namespace nsK2EngineLow {
	class Bloom:public IGameObject
	{
	public:
		Bloom();
		~Bloom();
		void Init(RenderTarget& renderTarget);
		void Update();
		void Render(RenderContext& rc, RenderTarget&renderTarget);

		RenderTarget* mainRenderTarget;
		RenderTarget luminanceRenderTarget;
		
		SpriteInitData luminanceSpriteInitData;
		SpriteInitData finalSpriteInitData;
		Sprite m_luminuceSprite;
		Sprite m_finalSprite;
		GaussianBlur gaussianBulur[4];
	
	};
}
