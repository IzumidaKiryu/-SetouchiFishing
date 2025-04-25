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
	//制限時間のUIを作る。
	//m_timeLimitUI = NewGO<TimeLimitUI>(0, "timelimitUI");　//エラーが出るのでいったんコメントアウト。！！！！！！！！！！！

	//プレイヤーのオブジェクトを作る。
	m_player = NewGO<Player>(0, "player");

	//エネミーのオブジェクトを作る。
	m_enemy = NewGO<Enemy>(0, "enemy");

	//ゲームカメラのオブジェクトを作る。
	gameCamera = NewGO<GameCamera>(0, "gamecamera");

	//背景のオブジェクトを作る。
	backGround = NewGO<BackGround>(0);
	//ゲーム中のBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/gamebgm.wav");



	//ゲーム中のBGMを再生する。
	//gameBGM = NewGO<SoundSource>(0);
	/*gameBGM->Init(1);
	gameBGM->Play(true);*/
	gameCamera->m_toCameraPos.Set(0.0f, 750.0f, -250.0f);

	//UIの場所を決める。
	SetFishDisplayPosition();

	//UIを設定する。
	SetDisplayiUI();
	SetStealPositionBarUI();

	for (int i = 0; i < 6; i++) {

		//フィッシュマネージャーにつけるオブジェクトネームの設定。
		std::char_traits<char>::copy(objectName[i], PositionName[i].c_str(), PositionName[i].size() + 1);

		//フィッシュマネージャーの生成。
		m_fishManager[i] = NewGO<FishManager>(0, objectName[i]);
	}

}

PositionSelection::~PositionSelection()
{
	//プレイヤーを削除する。
	DeleteGO(m_player);
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
	//m_timeLimitUI->DisplayTimeLimitUI(m_int_time);//タイムリミットを表示する。エラーが出るのでコメントアウト！！！！！！！
	IsWith_any_Position();//今どこのポジションにいるか判定する。

	
	if (m_shouldPartiallyDeactivate == false) {//アクティブかどうか判断する。
		SetFishUI();
		if (g_pad[0]->IsTrigger(enButtonA)) {
			ChangeSceneToPlayFishing();
			gameCamera->Activate();
		}
	}
	else {
		gameCamera->Deactivate();
	}
	for (int i = 0; i < 6; i++) {
		//フィッシュマネージャーの生成。
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
	//m_timeLimitUI->GetClockUI().Draw(rc);
	//m_timeLimitUI->GetOnesPlacUI().Draw(rc);
	//m_timeLimitUI->GetTensPlacUI().Draw(rc);
	//m_timeLimitUI->GetHundredsPlacUI().Draw(rc);

	if (m_shouldPartiallyDeactivate == false) {
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

		//魚を表示するディスプレイの内側

		m_fishDisplayInside[i].Init("Assets/modelData/fish_display_ui_inside.DDS", 130, 130);
		m_fishDisplayInside[i].SetPivot(Vector2(0.5f, 0.5f));
		m_fishDisplayInside[i].SetPosition(m_fishDisplayPosition[i]);
		m_fishDisplayInside[i].SetScale(Vector3{ 1.0f, 1.0f, 1.0f });

		//魚を表示するディスプレイの外側

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
			m_fishDisplayPosition[i] = { m_fishDisplayPositionXcriteria + m_fishDisplayPositionXinterval * (i), 180.0f, 0.0f };
		}
		if (2 < i) {
			m_fishDisplayPosition[i] = { m_fishDisplayPositionXcriteria + m_fishDisplayPositionXinterval * (i - 3), -250.0f, 0.0f };
		}
	}
}

void PositionSelection::SetisDisplayingTrue()
{
	m_is_displaying = true;
}

void PositionSelection::SetisDisplayingFalse()
{
	m_is_displaying = false;
}

/// <summary>
/// シーンをプレイフィッシングに変える。
/// </summary>
void PositionSelection::ChangeSceneToPlayFishing()
{
	SetisDisplayingFalse();

	// インスタンス生成→ポジション設定→初期設定(内部でポジション設定の情報を使っている)
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
	//プレイヤーを非アクティブにする。
	m_player->Deactivate();
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
	m_player->Activate();
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
	m_int_time = m_timelimit - m_stopwatch.GetElapsed();
	m_stopwatch.Stop();
	if (m_int_time <= 0)
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

	m_playFishing->SetFishManagerObjectName(PositionName[position_with_now]);
}

void PositionSelection::SetTotalValue(float individualValue)
{
	m_totalScore += individualValue;
}

void PositionSelection::FindFishHighScore()
{
	//一番スコアが高い魚がいる場所を探すアルゴリズム。
	Position compare;//比べる。
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
	if (m_player->m_position.z >= 12.0f)
	{

		if (m_player->m_position.x < float{ -254.0f })
		{
			position_with_now = POSITION_A;
		}

		if (m_player->m_position.x >= float{ -254.0f } && m_player->m_position.x <= float{ 254.0f })
		{
			position_with_now = POSITION_B;
		}

		if (m_player->m_position.x > float{ 254.0f })
		{
			position_with_now = POSITION_C;
		}
	}

	if (m_player->m_position.z < 12.0f)
	{
		if (m_player->m_position.x < float{ -254.0f })
		{
			position_with_now = POSITION_D;
		}
		if (m_player->m_position.x >= float{ -254.0f } && m_player->m_position.x <= float{ 254.0f })
		{
			position_with_now = POSITION_E;
		}
		if (m_player->m_position.x > float{ 254.0f })
		{
			position_with_now = POSITION_F;
		}
	}
	if (position_with_now == enemy_position) {
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
	//エラーが出る。

	//m_currentFramePlayerPositionState = position;
	//if (m_currentFramePlayerPositionState != ENEMY_SAME_POSITION) {//エネミーとポジションが違う時。
	//	if (m_currentFramePlayerPositionState != m_previousFramePlayerPositionState)
	//	{
	//		m_fishDisplayOutside[m_currentFramePlayerPositionState].Init("Assets/modelData/fish_display_ui_outside_selection.DDS", 130, 130);
	//	}
	//}
	//if (m_currentFramePlayerPositionState != m_previousFramePlayerPositionState && m_previousFramePlayerPositionState != INITIALSTATE) { //前のフレームと別のポジションのときかつ、一番最初の処理じゃなければ。緑から普通の色に戻す。
	//	if (ENEMY_SAME_POSITION != m_previousFramePlayerPositionState)//戻すポジションに敵がいなければ。
	//	{
	//		m_fishDisplayOutside[m_previousFramePlayerPositionState].Init("Assets/modelData/fish_display_ui_outside.DDS", 130, 130);
	//	}
	//}
	//m_previousFramePlayerPositionState = position;

}




//void PositionSelection::fishingPositionA_SetFish()
//{
//
//}
