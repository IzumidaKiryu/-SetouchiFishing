#pragma once
class TensionGauge :public IGameObject
{
public:

	TensionGauge();
	~TensionGauge();

	SpriteRender m_tensionGaugeInside;
	SpriteRender m_tensionGaugeOutside;
	SpriteRender m_tensionGaugeArrow;
	void Render(RenderContext& rc);
	
};

