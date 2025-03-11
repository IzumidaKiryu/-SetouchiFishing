#pragma once
class TensionGauge :public IGameObject
{
public:

	TensionGauge();
	~TensionGauge();

	SpriteRender m_tensionGaugeInside;
	SpriteRender m_tensionGaugeOutside;
	void Render(RenderContext& rc);
};

