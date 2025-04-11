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
		objectName[i] = new char[PositionName[i].size() + 1];
	}
	//制限時間のUIを作る。
	m_timeLimitUI= NewGO<TimeLimitUI>(0, "timelimitUI");

	//プレイヤーのオブジェクトを作る。
	player = NewGO<Player>(0, "player");

	//ゲームカメラのオブジェクトを作る。
	gameCamera = NewGO<GameCamera>(0, "gamecamera");

	//背景のオブジェクトを作る。
	backGround = NewGO<BackGround>(0);
	//ゲーム中のBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/gamebgm.wav");
	//ゲーム中のBGMを再生する。
	gameBGM = NewGO<SoundSource>(0);
	/*gameBGM->Init(1);
	gameBGM->Play(true);*/
	gameCamera->m_toCameraPos.Set(0.0f, 750.0f, -250.0f);

	//UIの場所を決める。
	SetFishDisplayPosition();

	//UIを設定する。
	SetUI();

	for (int i = 0; i < 6; i++) {


		//�t�B�b�V���}�l�[�W���[�ɂ���I�u�W�F�N�g�l�[���̐ݒ�B
			std::char_traits<char>::copy(objectName[i], PositionName[i].c_str(), PositionName[i].size() + 1);

		
			//フィッシュマネージャーの生成。
		m_fishManager[i] = NewGO<FishManager>(0, objectName[i]);
	}

}

PositionSelection::~PositionSelection()
{
	//プレイヤーを削除する。
	DeleteGO(player);
	//ゲームカメラを削除する。
	DeleteGO(gameCamera);
	//ゲーム中のBGMを削除する。
	DeleteGO(gameCamera);
	//背景を削除する。
	DeleteGO(backGround);
}

void PositionSelection::Update()
{

	//時間をはかる。
	Timer();
	m_timeLimitUI->DisplayTimeLimitUI(m_int_time);//タイムリミットを表示する。

	if (m_shouldPartiallyDeactivate == false) {//アクティブかどうか判断する。
		SetFishUI();
		if (g_pad[0]->IsTrigger(enButtonA)) {//Aボタンが押されたら。
			ChangeSceneToPlayFishing();//プレイフィッシングシーンに変える。
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

		//魚を表示するディスプレイの内側

		m_fishDisplayInside[i].Init("Assets/modelData/fish_display_ui_inside.DDS", 150, 150);
		m_fishDisplayInside[i].SetPivot(Vector2(0.5f, 0.5f));
		m_fishDisplayInside[i].SetPosition(m_fishDisplayPosition[i]);
		m_fishDisplayInside[i].SetScale(Vector3{ 1.0f, 1.0f, 1.0f });

		//魚を表示するディスプレイの外側

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

void PositionSelection::ChangeSceneToPlayFishing()
{
	SetisDisplayingFalse();

	
	// �C���X�^���X�������|�W�V�����ݒ聨�����ݒ�(�����Ń|�W�V�����ݒ�̏����g���Ă���)
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
	//プレイヤーを非アクティブにする。
	player->Deactivate();
	//ゲームカメラを非アクティブにする。
	gameCamera->Deactivate();
	//背景を非アクティブにする。
	backGround->Deactivate();
	//Uiを表示しない。
	m_shouldPartiallyDeactivate = true;
}

void PositionSelection::SetActivate()
{
	//プレイヤーをアクティブにする。
	player->Activate();
	//ゲームカメラをアクティブにする。
	gameCamera->Activate();
	//背景をアクティブにする。
	backGround->Activate();
	//UIを表示する。
	m_shouldPartiallyDeactivate = false;
}

/// <summary>
/// 制限時間をはかる。
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
		//フィッシュディスプレイのUIはフィッシュディスプレイの下に表示したいのでここでアップデートする。
		m_fishDisplayOutside[i].Update();
		m_fishDisplayInside[i].Update();
	}
}

void PositionSelection::FishChange()
{
	for (int i = 0; i < 6; i++) {
		if (m_fishManager[i]->GetShouldFishChange()) {
			DeleteGO(m_fishManager[i]);

			//フィッシュマネージャーの生成。
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

void PositionSelection::FindFishHighScore()
{
	//��ԃX�R�A��������������ꏊ��T���A���S���Y���B
	for (int i = 0; i < 5; i++) {
		if (m_fishManager[i]->GetScore() >= m_fishManager[i + 1]->GetScore()) {
			fishHighScorePosition=PositionName[i];
		}
		else {
			fishHighScorePosition = PositionName[i+1];
		}
	}

}




//void PositionSelection::fishingPositionA_SetFish()
//{
//
//}
