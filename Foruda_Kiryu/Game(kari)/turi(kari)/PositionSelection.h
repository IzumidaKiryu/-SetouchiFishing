#pragma once
#include "sound/SoundSource.h"

class Player;
class GameCamera;
class BackGround;
class SoundSource;

enum FishType {
	null,
	Tai,
	Buri,
	Tatiuo,
	Hirame,
	Jakotenn,
	Sinju,
};
struct fishingPosition {
	FishType fish;
	bool fishChangeFlag;//����ς��邩�ǂ����̃t���O�B
};

class PositionSelection : public IGameObject
{
public:
	

	PositionSelection();
	~PositionSelection();
	void Update();
	void Render(RenderContext& rc);
	void SettingFishType(fishingPosition Position);//���̃^�C�v��ݒ�B
	void SelectChangeFish(fishingPosition Position);//����ς��邩�ǂ����I�ԁB
	void SetUI();
	void SetFishDisplayPosition();

	float setFish=0.0f;
	Vector3 m_fishDisplayPosition[6];
	float m_fishDisplayPositionXcriteria = -350;//����\������f�B�X�v���C�̏ꏊ�̊�iX���j
	float m_fishDisplayPositionXinterval = 350.0f;


	Player* player;			//�v���C���[�B
	GameCamera* gameCamera;			//�Q�[���J�����B
	BackGround* backGround;
	SoundSource* gameBGM;		//�Q�[������BGM�B
	FontRender m_fontRender;
	fishingPosition PositionA;
	fishingPosition PositionB;
	fishingPosition PositionC;
	fishingPosition PositionD;
	fishingPosition PositionE;
	fishingPosition PositionF;

};

