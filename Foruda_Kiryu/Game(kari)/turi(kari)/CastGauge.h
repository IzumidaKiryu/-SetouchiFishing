#pragma once
class CastGauge:public IGameObject
{
public:

	CastGauge();
	~CastGauge();
	void Update();
	void Render(RenderContext& rc);
	float m_gaugeUpperLimit = 237.0f;//ゲージの上限
	float m_gaugeLowerLimit = -237.0f;//ゲージの下限
	SpriteRender m_castGaugeOutside;
	SpriteRender m_castGaugeInside;
	SpriteRender m_castGaugeArrow;
};

