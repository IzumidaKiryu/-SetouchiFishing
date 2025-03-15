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
	float m_arrowPosition = 0.0f;//���̃|�W�V�����i�����ݒ��-237�j
	float m_gaugeUpperLimit = 473.0f;//�Q�[�W�̏��
	float m_gaugeLowerLimit = -473.0f;//�Q�[�W�̉���
	SpriteRender m_tensionGaugeInside;
	SpriteRender m_tensionGaugeOutside;
	SpriteRender m_tensionGaugeArrow;
	GetRotation* m_getRotation;
	void Render(RenderContext& rc);
};