#include "stdafx.h"
#include "PositionSelection.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "FishManager.h"
#include "PlayFishing.h"
#include "TimeLimitUI.h"
#include <Time.h>
#include <string>

PositionSelection::PositionSelection()
{
	srand(time(NULL));

	m_stopwatch.Start();

	for (int i = 0; i < 6; i++)
	{
		objectName[i] = new char[fishManagerObjectName[i].size() + 1];
	}
	//�������Ԃ�UI�����B
	m_timeLimitUI= NewGO<TimeLimitUI>(0, "timelimitUI");

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
	gameCamera->m_toCameraPos.Set(0.0f, 750.0f, -250.0f);

	//UI�̏ꏊ�����߂�B
	SetFishDisplayPosition();

	//UI��ݒ肷��B
	SetUI();

	for (int i = 0; i < 6; i++) {

		//�t�B�b�V���}�l�[�W���[�ɂ���I�u�W�F�N�g�l�[���̐ݒ�B
			std::char_traits<char>::copy(objectName[i], fishManagerObjectName[i].c_str(), fishManagerObjectName[i].size() + 1);
		
			//�t�B�b�V���}�l�[�W���[�̐����B
		m_fishManager[i] = NewGO<FishManager>(0, objectName[i]);
	}

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
	//���Ԃ��͂���B
	Timer();
	m_timeLimitUI->DisplayTimeLimitUI(m_int_time);//�^�C�����~�b�g��\������B

	if (m_shouldPartiallyDeactivate == false) {//�A�N�e�B�u���ǂ������f����B
		SetFishUI();
		if (g_pad[0]->IsTrigger(enButtonA)) {//A�{�^���������ꂽ��B
			ChangeSceneToPlayFishing();//�v���C�t�B�b�V���O�V�[���ɕς���B
		}
	}
	/*for (int i = 0; i < 6; i++) {
		m_timelimit=m_fishManager[i]->m_randum;
	}*/
}

void PositionSelection::Render(RenderContext& rc)
{
	m_timeLimitUI->GetClockUI().Draw(rc);
	m_timeLimitUI->GetOnesPlacUI().Draw(rc);
	m_timeLimitUI->GetTensPlacUI().Draw(rc);
	m_timeLimitUI->GetHundredsPlacUI().Draw(rc);
	if (m_shouldPartiallyDeactivate==false) {
		for (int i = 0; i < 6; i++) {
			m_fishDisplayInside[i].Draw(rc);
			m_fishDisplayOutside[i].Draw(rc);
			m_fishUI[i]->Draw(rc);
		}
	}
}


void PositionSelection::SetUI()
{
	for (int i = 0; i < 6; i++) {

		//����\������f�B�X�v���C�̓���

		m_fishDisplayInside[i].Init("Assets/modelData/fish_display_ui_inside.DDS", 150, 150);
		m_fishDisplayInside[i].SetPivot(Vector2(0.5f, 0.5f));
		m_fishDisplayInside[i].SetPosition(m_fishDisplayPosition[i]);
		m_fishDisplayInside[i].SetScale(Vector3{ 1.0f, 1.0f, 1.0f });

		//����\������f�B�X�v���C�̊O��

		m_fishDisplayOutside[i].Init("Assets/modelData/fish_display_ui_outside.DDS", 150, 150);
		m_fishDisplayOutside[i].SetPivot(Vector2(0.5f, 0.5f));
		m_fishDisplayOutside[i].SetPosition(m_fishDisplayPosition[i]);
		m_fishDisplayOutside[i].SetScale(Vector3{ 1.0f, 1.0f, 1.0f });

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

void PositionSelection::SetisDisplayingTrue()
{
	m_is_displaying=true;
}

void PositionSelection::SetisDisplayingFalse()
{
	m_is_displaying = false;
}

/// <summary>
/// �V�[�����v���C�t�B�b�V���O�ɕς���B
/// </summary>
void PositionSelection::ChangeSceneToPlayFishing()
{
	SetisDisplayingFalse();
	
	// �C���X�^���X�������|�W�V�����ݒ聨�����ݒ�(����Ń|�W�V�����ݒ�̏���g���Ă���)
	m_playFishing = NewGO<PlayFishing>(0, "playFishing");
	SelectPositionA();
	m_playFishing->Init();

	SetDeactivate();
}

bool PositionSelection::GetisDisplaying()
{
	return m_is_displaying;
}

void PositionSelection::SetDeactivate()
{
	//�v���C���[���A�N�e�B�u�ɂ���B
	player->Deactivate();
	//�Q�[���J�������A�N�e�B�u�ɂ���B
	gameCamera->Deactivate();
	//�w�i���A�N�e�B�u�ɂ���B
	backGround->Deactivate();
	//Ui��\�����Ȃ��B
	m_shouldPartiallyDeactivate = true;
}

void PositionSelection::SetActivate()
{
	//�v���C���[���A�N�e�B�u�ɂ���B
	player->Activate();
	//�Q�[���J�������A�N�e�B�u�ɂ���B
	gameCamera->Activate();
	//�w�i���A�N�e�B�u�ɂ���B
	backGround->Activate();
	//UI��\������B
	m_shouldPartiallyDeactivate = false;
}

/// <summary>
/// �������Ԃ��͂���B
/// </summary>
void PositionSelection::Timer()
{
	m_double_time= m_timelimit-m_stopwatch.GetElapsed();
	m_stopwatch.Stop();
	m_int_time = m_double_time;
	if (m_double_time<=0)
	{
		m_is_time_up = true;
		m_stopwatch.Stop();

	}
}

void PositionSelection::SetFishUI()
{
	for (int i = 0; i < 6; i++) {
		m_fishUI[i] = m_fishManager[i]->m_ui;
	}
	SetFishUIPosition();

}


void PositionSelection::SetFishUIPosition()
{
	for (int i = 0; i < 6; i++) {
		m_fishUI[i]->SetPivot(Vector2(0.5f, 0.5f));
		m_fishUI[i]->SetPosition(m_fishDisplayPosition[i]);
		m_fishUI[i]->SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
		m_fishUI[i]->Update();
		//�t�B�b�V���f�B�X�v���C��UI�̓t�B�b�V���f�B�X�v���C�̉��ɕ\���������̂ł����ŃA�b�v�f�[�g����B
		m_fishDisplayOutside[i].Update();
		m_fishDisplayInside[i].Update();
	}
}

void PositionSelection::FishChange()
{
	for (int i = 0; i < 6; i++) {
		if (m_fishManager[i]->GetShouldFishChange()) {
			DeleteGO(m_fishManager[i]);

			//�t�B�b�V���}�l�[�W���[�̐����B
			m_fishManager[i] = NewGO<FishManager>(0, objectName[i]);
		}

	}
}

void PositionSelection::SelectPosition()
{
	if (true)
	{

	}
}

void PositionSelection::SelectPositionA()
{
	m_playFishing->SetFishManagerObjectName("positionA");
}

void PositionSelection::SelectPositionB()
{
	m_playFishing->SetFishManagerObjectName("positionB");
}

void PositionSelection::SelectPositionC()
{
	m_playFishing->SetFishManagerObjectName("positionC");
}

void PositionSelection::SelectPositionD()
{
	m_playFishing->SetFishManagerObjectName("positionD");
}

void PositionSelection::SelectPositionE()
{
	m_playFishing->SetFishManagerObjectName("positionE");
}

void PositionSelection::SelectPositionF()
{
	m_playFishing->SetFishManagerObjectName("positionF");
}

void PositionSelection::SetTotalValue(float individualValue)
{
	m_totalValue += individualValue;
}



//void PositionSelection::fishingPositionA_SetFish()
//{
//
//}
