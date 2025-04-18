#pragma once
class GaugeCastSuccessful;
class TensionGauge;
class FishingGauge;
class PositionSelection;
class PlayFishing;
class GameCamera;
class RodFloatMove;

class CastGauge :public IGameObject
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
	void Failure();//���s�B
	void Success();//�����B
	//void SetRodFloatPositon();//


	float m_arrowPosition = -237.0f;//���̃|�W�V�����i�����ݒ��-237�j
	bool upState = true;//�オ���Ă��邩�̃X�e�[�g
	void Render(RenderContext& rc);
	float m_gaugeUpperLimit = 237.0f;//�Q�[�W�̏��
	float m_gaugeLowerLimit = -237.0f;//�Q�[�W�̉���
	float m_gaugeSpead;

	float m_heightFirstGaugeCastSuccessful = 10.0f;//�����Q�[�W�̍ŏ��̉����B
	bool is_ended = false;

	SpriteRender m_castGaugeOutside;
	SpriteRender m_castGaugeInside;
	SpriteRender m_castGaugeArrow;
	GaugeCastSuccessful* m_gaugeCastSuccessful = nullptr;
	FishingGauge* m_fishingGauge;
	TensionGauge* tensionGauge = nullptr;
	PositionSelection* m_positionSelection;
	PlayFishing* m_playFishing;
	ModelRender m_rodFloatModel;

	Vector3 first_velocity_vector{ 1.0f,0.0f,0.0f };
	float t=0;
	Vector3 g{ 0.0f,-30.0f,0.0f };
	Vector3 m_rodFloatPosition{ 0.0f,500.0f,0.0f };
	Vector3 InitPos{0.0f,500.0f,0.0f};

	GameCamera* m_gameCamera;
	RodFloatMove* m_rodFloatMove;
};

