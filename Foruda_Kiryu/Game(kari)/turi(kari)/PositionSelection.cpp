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
#include "stdafx.h"
#include "Enemy.h"


PositionSelection::PositionSelection()
{


	srand(time(NULL));

	m_stopwatch.Start();

	for (int i = 0; i < 6; i++)
	{
		objectName[i] = new char[PositionName[i].size() + 1];
	}
	//�������Ԃ�UI�����B
	m_timeLimitUI= NewGO<TimeLimitUI>(0, "timelimitUI");

	//�v���C���[�̃I�u�W�F�N�g�����B
	m_player = NewGO<Player>(0, "player");

	//�G�l�~�[�̃I�u�W�F�N�g�����B
	m_enemy = NewGO<Enemy>(0, "enemy");

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
	SetDisplayiUI();
	SetStealPositionBarUI();

	for (int i = 0; i < 6; i++) {

		//�t�B�b�V���}�l�[�W���[�ɂ���I�u�W�F�N�g�l�[���̐ݒ�B
			std::char_traits<char>::copy(objectName[i], PositionName[i].c_str(), PositionName[i].size() + 1);
		
			//�t�B�b�V���}�l�[�W���[�̐����B
		m_fishManager[i] = NewGO<FishManager>(0, objectName[i]);
	}

}

PositionSelection::~PositionSelection()
{
	//�v���C���[���폜����B
	DeleteGO(m_player);
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
	IsWith_any_Position();//���ǂ��̃|�W�V�����ɂ��邩���肷��B

	if (m_shouldPartiallyDeactivate == false) {//�A�N�e�B�u���ǂ������f����B
		SetFishUI();
		if (g_pad[0]->IsTrigger(enButtonA)) {
			ChangeSceneToPlayFishing();
		}
	}
	for (int i = 0; i < 6; i++) {
		//�t�B�b�V���}�l�[�W���[�̐����B
		m_fishManager[i] = FindGO<FishManager>(objectName[i]);
		if (m_fishManager[i]->GetShouldFishChange() == true) {
			DeleteGO(m_fishManager[i]);
			m_fishManager[i] = NewGO<FishManager>(0, objectName[i]);
		}

	}

FindFishHighScore();
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
		m_stealPositionBarOutsideUI.Draw(rc);
		m_stealPositionBarInsideUI.Draw(rc);
	}
}


void PositionSelection::SetDisplayiUI()
{
	for (int i = 0; i < 6; i++) {

		//����\������f�B�X�v���C�̓���

		m_fishDisplayInside[i].Init("Assets/modelData/fish_display_ui_inside.DDS", 130, 130);
		m_fishDisplayInside[i].SetPivot(Vector2(0.5f, 0.5f));
		m_fishDisplayInside[i].SetPosition(m_fishDisplayPosition[i]);
		m_fishDisplayInside[i].SetScale(Vector3{ 1.0f, 1.0f, 1.0f });

		//����\������f�B�X�v���C�̊O��

		m_fishDisplayOutside[i].Init("Assets/modelData/fish_display_ui_outside.DDS", 130, 130);
		m_fishDisplayOutside[i].SetPivot(Vector2(0.5f, 0.5f));
		m_fishDisplayOutside[i].SetPosition(m_fishDisplayPosition[i]);
		m_fishDisplayOutside[i].SetScale(Vector3{ 1.0f, 1.0f, 1.0f });

	}
}

void PositionSelection::SetStealPositionBarUI()
{
	m_stealPositionBarOutsideUI.Init("Assets/modelData/landscape_gauge_inside.DDS", 500, 100);
	m_stealPositionBarOutsideUI.SetPivot(Vector2(0.5f, 0.5f));
	m_stealPositionBarOutsideUI.SetPosition(Vector3{ 370.0f, 300.0f, 0.0f });
	m_stealPositionBarOutsideUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_stealPositionBarOutsideUI.Update();

	m_stealPositionBarInsideUI.Init("Assets/modelData/landscape_gauge_outer.DDS", 500, 100);
	m_stealPositionBarInsideUI.SetPivot(Vector2(0.5f, 0.5f));
	m_stealPositionBarInsideUI.SetPosition(Vector3{ 370.0f, 300.0f, 0.0f });
	m_stealPositionBarInsideUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_stealPositionBarInsideUI.Update();

}

void PositionSelection::SetFishDisplayPosition()
{
	for (int i = 0; i < 6; i++) {
		if (i < 3) {
			m_fishDisplayPosition[i] = { m_fishDisplayPositionXcriteria+m_fishDisplayPositionXinterval*(i), 180.0f, 0.0f };
		}
		if (2 < i) {
			m_fishDisplayPosition[i] = { m_fishDisplayPositionXcriteria + m_fishDisplayPositionXinterval * (i-3), -250.0f, 0.0f };
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
	
	// �C���X�^���X�������|�W�V�����ݒ聨�����ݒ�(�����Ń|�W�V�����ݒ�̏����g���Ă���)
	m_playFishing = NewGO<PlayFishing>(0, "playFishing");
	SelectPosition();
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
	m_player->Deactivate();
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
	m_player->Activate();
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
	m_int_time= m_timelimit-m_stopwatch.GetElapsed();
	m_stopwatch.Stop();
	if (m_int_time<=0)
	{
		m_is_time_up = true;
		m_stopwatch.Stop();

	}
	/*char text[256];
	sprintf_s(text, "m_int_time = %d, com = %d\n", m_int_time);
	OutputDebugStringA(text);*/
}

int PositionSelection::GetTime()
{
	return m_int_time;
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

	m_playFishing->SetFishManagerObjectName(PositionName[position_with_now]);
}

void PositionSelection::SetTotalValue(float individualValue)
{
	m_totalScore += individualValue;
}

void PositionSelection::FindFishHighScore()
{
	//��ԃX�R�A��������������ꏊ��T���A���S���Y���B
	Position compare;//��ׂ�B
	enemy_position = POSITION_A;
		for (int i = 0; i < 4; i++) {
			if (m_fishManager[i]->GetScore() >= m_fishManager[i + 1]->GetScore()) {
				compare = m_positionStateArray[i];
			}
			else {
				compare = m_positionStateArray[i + 1];
			}
			if (m_fishManager[enemy_position]->GetScore() <= m_fishManager[compare]->GetScore()) {
				enemy_position = compare;
			}

		}

}

void PositionSelection::IsWith_any_Position()
{
	if (m_player->position.z >= 12.0f)
	{

		if (m_player->position.x < float{ -254.0f })
		{
			position_with_now = POSITION_A;
		}

		if (m_player->position.x >= float{ -254.0f } && m_player->position.x <= float{ 254.0f })
		{
			position_with_now = POSITION_B;
		}

		if (m_player->position.x > float{ 254.0f })
		{
			position_with_now = POSITION_C;
		}
	}

	if (m_player->position.z < 12.0f)
	{
		if (m_player->position.x < float{ -254.0f })
		{
			position_with_now = POSITION_D;
		}
		if (m_player->position.x >= float{ -254.0f } && m_player->position.x <= float{ 254.0f })
		{
			position_with_now = POSITION_E;
		}
		if (m_player->position.x > float{ 254.0f })
		{
			position_with_now = POSITION_F;
		}
	}
	if (position_with_now==enemy_position) {
		position_with_now = ENEMY_SAME_POSITION;
	}

	/*if (m_player->position.x <= float{ 254.0f })
	{
		if (m_player->position.z > 12.0f)
		{
			position_with_now = POSITION_B;
		}

		if (m_player->position.z < 12.0f)
		{
			position_with_now = POSITION_E;
		}
	}

	if (m_player->position.x >= float{ 254.0f })
	{
		if (m_player->position.z > 12.0f)
		{
			position_with_now= POSITION_C;
		}
		if (m_player->position.z< 12.0f)
		{
			position_with_now = POSITION_F;
		}
	}*/
	SetFishDisplayOutside_to_Green(position_with_now);
}

void PositionSelection::SetFishDisplayOutside_to_Green(Position position)
{
	m_currentFramePlayerPositionState = position;
	if (m_currentFramePlayerPositionState != ENEMY_SAME_POSITION) {//�G�l�~�[�ƃ|�W�V�������Ⴄ���B
		if (m_currentFramePlayerPositionState != m_previousFramePlayerPositionState)
		{
			m_fishDisplayOutside[m_currentFramePlayerPositionState].Init("Assets/modelData/fish_display_ui_outside_selection.DDS", 130, 130);
		}
	}
		if (m_currentFramePlayerPositionState != m_previousFramePlayerPositionState && m_previousFramePlayerPositionState != INITIALSTATE) { //�O�̃t���[���ƕʂ̃|�W�V�����̂Ƃ����A��ԍŏ��̏�������Ȃ���΁B�΂��畁�ʂ̐F�ɖ߂��B
			if (ENEMY_SAME_POSITION != m_previousFramePlayerPositionState)//�߂��|�W�V�����ɓG�����Ȃ���΁B
			{
				m_fishDisplayOutside[m_previousFramePlayerPositionState].Init("Assets/modelData/fish_display_ui_outside.DDS", 130, 130);
			}
		}
	m_previousFramePlayerPositionState= position;

}




//void PositionSelection::fishingPositionA_SetFish()
//{
//
//}
