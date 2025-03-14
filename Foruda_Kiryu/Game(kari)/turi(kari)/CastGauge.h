#pragma once
class GaugeCastSuccessful;
class TensionGauge;
class CastGauge:public IGameObject
{
public:
	CastGauge();
	~CastGauge();
	void Update();
	void SetArrowPosition();
	void UpAndDownManagement();//�L���X�g�Q�[�W�̏㉺����̊Ǘ��B
	void UpwardOperation();
	void DownwardOperation();
	void SetGaugeSpead();
	void HitTest();
	float m_arrowPosition= -237.0f;//���̃|�W�V�����i�����ݒ��-237�j
	bool upState=true;//�オ���Ă��邩�̃X�e�[�g
	void Render(RenderContext& rc);
	float m_gaugeUpperLimit = 237.0f;//�Q�[�W�̏��
	float m_gaugeLowerLimit = -237.0f;//�Q�[�W�̉���
	float m_gaugeSpead;
	float m_heightFirstGaugeCastSuccessful=10.0f;//�����Q�[�W�̍ŏ��̉����B

	SpriteRender m_castGaugeOutside;
	SpriteRender m_castGaugeInside;
	SpriteRender m_castGaugeArrow;
	GaugeCastSuccessful* m_gaugeCastSuccessful;
	TensionGauge* tensionGauge;
};

