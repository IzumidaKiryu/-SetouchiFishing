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
	void SetFishEscapePower();
	void m_isfishEscapePowerDirectionChange();//魚が逃げようとする力の方向を変えるかどうか。
	void m_fishEscapePowerDirectionChange();//魚が逃げようとする力の方向を変える。
	int m_fishEscapePowerDirection = 1;//魚が逃げようとする力の方向。（1なら右、-1なら左に引っ張る）。
	float m_arrowPosition = 0.0f;//���̃|�W�V�����i�����ݒ��-237�j
	float m_gaugeUpperLimit = 473.0f;//�Q�[�W�̏��
	float m_gaugeLowerLimit = -473.0f;//�Q�[�W�̉���
	float m_fishEscapePower = 0.0f;//魚が逃げようとする力。（矢印を左右に引っ張る力）。
	SpriteRender m_tensionGaugeInside;
	SpriteRender m_tensionGaugeOutside;
	SpriteRender m_tensionGaugeArrow;
	GetRotation* m_getRotation;
	void Render(RenderContext& rc);
};