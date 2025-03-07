#pragma once
class CastGauge:public IGameObject
{
public:

	CastGauge();
	~CastGauge();
	void Update();
	void Render(RenderContext& rc);
	float m_gaugeUpperLimit = 237.0f;//�Q�[�W�̏��
	float m_gaugeLowerLimit = -237.0f;//�Q�[�W�̉���
	SpriteRender m_castGaugeOutside;
	SpriteRender m_castGaugeInside;
	SpriteRender m_castGaugeArrow;
};

