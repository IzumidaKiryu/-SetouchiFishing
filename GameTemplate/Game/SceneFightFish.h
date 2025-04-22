#pragma once
enum FIshState
{
	setWhen_State_Announce_Should,//���A�i�E���X���邩��ݒ肷��B
	normal,//���ʁB
	setWhen_State_Angry_or_exhausted_Should,//���X�e�[�g��Angry��exhausted�ɕς��邩�B
	announce,//��Ԃ̕ω����A�i�E���X����B
	change_Angry_or_exhausted,
	angry,//�{���Ă���B
	exhausted,//�敾���Ă���B
};

class GetRotation;
class PlayFishing;
class FishingRodHP;
class RodFloatMove;
class TensionGauge;
class GameCamera;
class PositionSelection;
class SceneFightFish:public IGameObject
{
public:
	SceneFightFish();
	~SceneFightFish();

	void Update();
	void RightAndLeftManagement();
	void SetSigns_of_Fish_Position();
	void SetFishEscapePower();
	void SetFishDirection();//���������Ă��������ς��邩�ǂ����B
	void FishDirectionChange();//���������Ă��������ς���B
	void failure();//���s�B
	void success();//�����B
	float GetRotationPower();

	void SetWhen_State_Announce_Should_State();
	void NormalState();//�������ʂ̏�Ԃ̎��̏����B
	void When_State_Angry_or_exhausted_Shoul();
	void AnnounceState();
	void Change_Angry_or_Exhausted_State();
	void AngerState();//�����{���Ă���Ƃ��̏����B
	void ExhaustedState();//�����敾���Ă���Ƃ��̏����B
	void FishStateAdminister();
	void SetRodFloatModel();
	void SetCamera();
	void FrameCount();
	void Set3DFishPosition();
	void SetRangeRate();

	float m_forcePullFish;//������������́B
	bool m_previous_is_fish_suited_for_upper_side = true;//�O�̃t���[���ŋ�����������Ă������ǂ����B
	bool is_fish_suited_for_upper_side = true;//�����㑤�������Ă��邩�ǂ����B
	float m_initRangeRate;
	float m_range_rate = 0.0f;//�ő勗���ƍ����鋗���̊����B
	float m_barTop = 473.0f;//�Q�[�W�̏�[�B
	float m_barBottom = -473.0f;//�Q�[�W�̉��[�B
	float m_fishEscapePower = 0.0f;//���������悤�Ƃ���́B�i�������E�Ɉ�������́j�B
	int m_fishChange_in_DirectionTimes = 0;//���������]���������B
	int m_when_state_announce_should = 0;//���X�e�[�g���A�i�E���X�ɕς��邩�B�i���̐���23�Ȃ�����]���񐔂�23��ڂ̎��ɃX�e�[�g���A�i�E���X�ɂ���B�j
	int m_when_State_Angry_or_exhausted_Should;//���X�e�[�g��Angry��exhausted�ɕς��邩�B
	int state_changed_when_directiontimes;//��ԐV�����X�e�[�g���ς�������ɋ������܂ŕ����]���������B
	int m_angerState_frame_count = 0;//�A���K�[�X�e�[�g�̎��Ƀt���[�����J�E���g����B
	bool m_reduce_Hp_when_angry = true;
	bool m_should_change_fish_to_anger_ui = true;
	int m_frameCount = 0;
	float m_this_frame_by_fish_advanced_distance;//���̃t���[���ŋ����i�񂾋����i�����ŕ\���j
	float m_total_by_fish_advanced_distance;//�g�[�^���ŋ����i�񂾋����B

	Vector3 fish3DPos;

	FIshState m_fishState;
	SpriteRender m_tensionGaugeInside;
	SpriteRender m_tensionGaugeOutside;
	SpriteRender m_signs_of_Fish;//���e
	GetRotation* m_getRotation;
	PlayFishing* m_playFishing;
	FishingRodHP* m_fishingRodHP;
	RodFloatMove* m_rodFloatMove;
	TensionGauge* m_tensionGauge;
	GameCamera* m_gameCamera;
	PositionSelection* m_positionSelection;
};

