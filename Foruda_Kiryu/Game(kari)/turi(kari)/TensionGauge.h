#pragma once
class GetRotation;
class TensionGauge :public IGameObject
{
public:

	TensionGauge();
	~TensionGauge();
	void Update();
	void RightAndLeftManagement();
	void SetArrowPosition();
	bool m_isRight;
	float m_arrowPosition =0.0f;//矢印のポジション（初期設定は-237）
	float m_gaugeUpperLimit = 473.0f;//ゲージの上限
	float m_gaugeLowerLimit = -473.0f;//ゲージの下限
	SpriteRender m_tensionGaugeInside;
	SpriteRender m_tensionGaugeOutside;
	SpriteRender m_tensionGaugeArrow;
	GetRotation* m_getRotation;
	void Render(RenderContext& rc);
};

