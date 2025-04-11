#pragma once
class TensionGauge;
class PlayFishing;
class FishingGauge : public IGameObject
{
public:
	FishingGauge();
	~FishingGauge();
	void Update();
	void SetBarPosition();//�㉺�ɓ����o�[
	void UpAndDownManagement();//�o�[�̏㉺����̊Ǘ��B
	void UpwardOperation();
	void DownwardOperation();
	void SetBarSpead();
	void HitTest();
	float m_barPosition = -237.0f;//�o�[�̃|�W�V�����i�����ݒ��???�j
	bool upState = true;//�オ���Ă��邩�̃X�e�[�g
	void Render(RenderContext& rc);
	float m_barUpperLimit = 237.0f;//�o�[�̏��
	float m_barLowerLimit = -237.0f;//�o�[�̉���
	float m_barSpead;//�o�[�̃X�s�[�h
	void Attack();
	float m_attack = 1;
	float m_hpMinimumDecreaseLimit = 1.0f;
	float m_hpMaxDecreseLimit =0.5f;

	SpriteRender m_fishingGauge;
	SpriteRender m_fishingGaugeFrame;
	SpriteRender m_fishingGaugeBar;
	TensionGauge* m_tensionGauge;
	PlayFishing* m_playFishing;

	
};



