#pragma once
#include "sound/SoundSource.h"
#include <string>

enum Position {
	POSITION_A,
	POSITION_B,
	POSITION_C,
	POSITION_D,
	POSITION_E,
	POSITION_F,
	INITIALSTATE,//�������
	ENEMY_SAME_POSITION,//�G�l�~�[�Ɠ����ꏊ�B
};

class Player;
class GameCamera;
class BackGround;
class SoundSource;
class FishManager;
class PlayFishing;
class TimeLimitUI;
class Enemy;

class PositionSelection : public IGameObject
{
public:


	PositionSelection();
	~PositionSelection();
	void Update();
	void Render(RenderContext& rc);
	void SetDisplayiUI();
	void SetStealPositionBarUI();
	void SetFishUI();//����UI���Z�b�g�B
	void SetFishDisplayPosition();//�f�B�X�v���CUI�̏ꏊ��ݒ�B
	void SetisDisplayingTrue();
	void SetisDisplayingFalse();
	void ChangeSceneToPlayFishing();
	bool GetisDisplaying();
	void SetDeactivate();//��A�N�e�B�u�ɂ���B
	void SetActivate();
	void Timer();
	int GetTime();
	void SetFishUIPosition();
	void FishChange();//����ς���B
	void SelectPosition();
	void SetTotalValue(float score);
	void FindFishHighScore();//�X�R�A����������T���B
	void IsWith_any_Position();
	void SetFishDisplayOutside_to_Green(Position positon);
	void SetCameraPosition();


	float setFish = 0.0f;
	Vector3 m_fishDisplayPosition[6];//�f�B�X�v���CUI�̃|�W�V����
	float m_fishDisplayPositionXcriteria = -350;//����\������f�B�X�v���C�̏ꏊ�̊�iX���j
	float m_fishDisplayPositionXinterval = 350.0f;
	bool m_is_displaying;//�\�����邩�ǂ����B
	bool m_shouldPartiallyDeactivate = false;//�����I�ɔ�A�N�e�B�u�ɂ���ׂ����B
	//double m_double_time=0.0f;//����(double�^)
	float m_timelimit = 240;//���Ԑ���
	int m_int_time = m_timelimit;//����(Int�^)
	float m_totalScore = 0.0f;//�X�R�A�̍��v�B
	bool m_is_time_up;//�^�C���A�b�v���Ă��邩�ǂ����B
	float m_stealPositionPoint = 0.0f;//�G���炩��|�W�V������D�����߂̃|�C���g�B

	//int m_isSetFishDisplayOutside_to_Green=0;//�t���[����UI��ΐF�ɂ��邩�B
	Position m_currentFramePlayerPositionState;//���̃t���[���̃|�W�V����
	Position m_previousFramePlayerPositionState = INITIALSTATE;
	Position m_positionStateArray[6]{
	POSITION_A,
	POSITION_B,
	POSITION_C,
	POSITION_D,
	POSITION_E,
	POSITION_F,
	};
	int a = 0;
	std::string fishHighScorePosition;//�o�Ă��鋛�̒��ň�ԃX�R�A��������������|�W�V�����B
	std::string PositionName[6] = {
		"positionA",
		"positionB",
		"positionC",
		"positionD",
		"positionE",
		"positionF"
	}
	;
	std::string select_by_with_position;
	char* objectName[6];
	Position position_with_now;
	Position enemy_position = INITIALSTATE;//�������;
	Player* m_player;			//�v���C���[�B
	GameCamera* gameCamera;			//�Q�[���J�����B
	BackGround* backGround;
	//SoundSource* gameBGM;		//�Q�[������BGM�B
	FontRender m_fontRender;
	SpriteRender m_fishDisplayInside[6];
	SpriteRender m_fishDisplayOutside[6];
	FishManager* m_fishManager[6];
	PlayFishing* m_playFishing;
	SpriteRender* m_fishUI[6];
	SpriteRender m_stealPositionBarInsideUI;
	SpriteRender m_stealPositionBarOutsideUI;
	SpriteRender m_stealPositionGaugeUI;
	TimeLimitUI* m_timeLimitUI;
	//ModelRender m_rodFloatModel;

	Stopwatch m_stopwatch;
	Enemy* m_enemy;

};

