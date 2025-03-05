#include "stdafx.h"
#include "PositionSelection.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "GameCamera.h"
#include "BackGround.h"

PositionSelection::PositionSelection()
{
	srand(time(NULL));

	//�v���C���[�̃I�u�W�F�N�g�����B
	player = NewGO<Player>(0, "player");

	//�Q�[���J�����̃I�u�W�F�N�g�����B
	gameCamera = NewGO<GameCamera>(0, "gamecamera");

	//�w�i�̃I�u�W�F�N�g�����B
	backGround = NewGO<BackGround>(0);
	//�Q�[������BGM��ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/gamebgm.wav");
	//�Q�[������BGM���Đ�����B
	gameBGM = NewGO<SoundSource>(0);
	/*gameBGM->Init(1);
	gameBGM->Play(true);*/
	gameCamera->m_toCameraPos.Set(0.0f, 1250.0f, -250.0f);
}

PositionSelection::~PositionSelection()
{
	//�v���C���[���폜����B
	DeleteGO(player);
	//�Q�[���J�������폜����B
	DeleteGO(gameCamera);
	//�Q�[������BGM���폜����B
	DeleteGO(gameCamera);
	//�w�i���폜����B
	DeleteGO(backGround);
}

void PositionSelection::Update()
{

}

void PositionSelection::Render(RenderContext& rc)
{

}

void PositionSelection::SettingFishType(fishingPosition position)
{
	int randumRank;
	randumRank=rand()%100;

	if (0<=randumRank <= 62)//���̎O�C�̋��̏o���m���i100����63�j
	{
		int randumFish = rand() % 3;
		switch (randumFish)
		{
		case 0:
			position.fish =Sinju;
			break;
		case 1:
			position.fish = Hirame;
			break;
		case 2:
			position.fish = Jakotenn;
			break;
		default:
			break;
		}

	}
	if (63 <= randumRank <=90)//���̂Q�C�̏o���m���i100����26�j
	{
		int randumFish = rand() % 2;
		switch (randumFish)
		{
		case 0:
			position.fish = Tatiuo;
			break;
		case 1:
			position.fish = Buri;
			break;
		default:
			break;
		}
	}
	if (91 <= randumRank <= 99)//�o���m���i100����9�j
	{
		position.fish = Tai;
	}


}

void PositionSelection::SelectChangeFish(fishingPosition Position)
{
}
