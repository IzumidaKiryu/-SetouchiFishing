#include "stdafx.h"
#include "PositionSelection.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Buri.h"
#include "Fish.h"

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

	//UI�̏ꏊ�����߂�B
	SetFishDisplayPosition();

	//UI��ݒ肷��B
	SetUI();

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
	for (int i = 0; i < 6; i++) {
		m_fishDisplayInside[i].Draw(rc);
		m_fishDisplayOutside[i].Draw(rc);
	}
}

void PositionSelection::SettingFishType(fishingPosition Position)
{
}

void PositionSelection::SelectChangeFish(fishingPosition Position)
{
}


void PositionSelection::SetUI()
{
	for (int i = 0; i < 6; i++) {

		//����\������f�B�X�v���C�̓���

		m_fishDisplayInside[i].Init("Assets/modelData/fish_display_ui_inside.DDS", 150, 150);
		m_fishDisplayInside[i].SetPivot(Vector2(0.5f, 0.5f));
		m_fishDisplayInside[i].SetPosition(m_fishDisplayPosition[i]);
		m_fishDisplayInside[i].SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
		m_fishDisplayInside[i].Update();

		//����\������f�B�X�v���C�̊O��

		m_fishDisplayOutside[i].Init("Assets/modelData/fish_display_ui_outside.DDS", 150, 150);
		m_fishDisplayOutside[i].SetPivot(Vector2(0.5f, 0.5f));
		m_fishDisplayOutside[i].SetPosition(m_fishDisplayPosition[i]);
		m_fishDisplayOutside[i].SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
		m_fishDisplayOutside[i].Update();

	}
}

void PositionSelection::SetFishDisplayPosition()
{
	for (int i = 0; i < 6; i++) {
		if (i < 3) {
			m_fishDisplayPosition[i] = { m_fishDisplayPositionXcriteria+m_fishDisplayPositionXinterval*(i), 200.0f, 0.0f };
		}
		if (2 < i) {
			m_fishDisplayPosition[i] = { m_fishDisplayPositionXcriteria + m_fishDisplayPositionXinterval * (i-3), -200.0f, 0.0f };
		}
	}
}

//void PositionSelection::fishingPositionA_SetFish()
//{
//
//}
