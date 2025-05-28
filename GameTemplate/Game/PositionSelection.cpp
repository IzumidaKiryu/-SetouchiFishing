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
#include "StealPositionBar.h"
#include "FishSlot.h"
#include "GameStartCountdown.h"
#include< memory >




PositionSelection::PositionSelection()
{
	

	srand(time(NULL));



}

PositionSelection::~PositionSelection()
{
	//m_gameCamera = FindGO<GameCamera>("gamecamera");
	//横取りゲージを削除する。
	DeleteGO(m_stealPositionBar);
	//プレイヤーを削除する。
	DeleteGO(m_player);
	////ゲームカメラを削除する。
	//DeleteGO(m_gameCamera);
	////背景を削除する。
	//DeleteGO(m_backGround);
	
}

void PositionSelection::Update()
{
	if (m_isCountdownFinished==true)
	{

		//時間をはかる。
		Timer();
		//m_timeLimitUI->DisplayTimeLimitUI(m_int_time);//タイムリミットを表示する。エラーが出るのでコメントアウト！！！！！！！
		UpdatePlayerArea();//今どこのポジションにいるか判定する。

		if (m_shouldPartiallyDeactivate == false) {//アクティブかどうか判断する。

			if (g_pad[0]->IsTrigger(enButtonA)) {
				ChangeSceneToPlayFishing();
				m_gameCamera->Activate();
			}
			SetCameraPosition();
		}
		else {
			m_gameCamera->Deactivate();
		}
		for (int i = 0; i < 6; i++) {
			//フィッシュマネージャーの生成。
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
}

bool PositionSelection::Start()
{
	FindGameObjects();
	//m_enemy->SetCountdownFinished(true);//カウントダウンが終わったことを伝える。
	return true;
}

void PositionSelection::Init()
{
	m_stopwatch.Start();

	//制限時間のUIを作る。
	m_timeLimitUI = NewGO<TimeLimitUI>(0, "timelimitUI");

	//横取りゲージを作る。
	m_stealPositionBar = NewGO<StealPositionBar>(0, "stealPositionBar");

	//ゲーム中のBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/gamebgm.wav");



	//ゲーム中のBGMを再生する。
	//gameBGM = NewGO<SoundSource>(0);
	/*gameBGM->Init(1);
	gameBGM->Play(true);*/
	//gameCamera->m_toCameraPos.Set(0.0f, 750.0f, -250.0f);

	//UIの場所を決める。
	SetFishDisplayPosition();


	for (int i = 0; i < 6; i++) {

		objectName[i] = new char[AreaName[i].size() + 1];


		//フィッシュマネージャーにつけるオブジェクトネームの設定。
		std::char_traits<char>::copy(objectName[i], AreaName[i].c_str(), AreaName[i].size() + 1);

		//フィッシュマネージャーの生成。
		m_fishManager[i] = NewGO<FishManager>(0, objectName[i]);
	}


	//フィッシュスロットのオブジェクトを作る。
	m_fishSlot = NewGO<FishSlot>(0, "fishSlot");


	SetCountdownFinished(true);

	m_enemy->SetCountdownFinished(true);//カウントダウンが終わったことを伝える。

}

void PositionSelection::FindGameObjects()
{
	m_player = FindGO<Player>("player");
	m_enemy = FindGO<Enemy>("enemy");
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_backGround = FindGO<BackGround>("backGround");

	//m_fishSlot = FindGO<FishSlot>("fishSlot");
	//m_fishSlot->ThiscClassInit();
}


bool PositionSelection::ShouldChangeState()
{
	return false;
}

void PositionSelection::OnUpdate()
{
}

void PositionSelection::Render(RenderContext& rc)
{
	//m_timeLimitUI->GetClockUI().Draw(rc);
	//m_timeLimitUI->GetOnesPlacUI().Draw(rc);
	//m_timeLimitUI->GetTensPlacUI().Draw(rc);
	//m_timeLimitUI->GetHundredsPlacUI().Draw(rc);
	if (m_isCountdownFinished == true) {
		m_timeLimitUI->m_timeFont.Draw(rc);
		m_stealPositionBar->DisplayUI(rc);
		if (m_shouldPartiallyDeactivate == false) {

			m_fishSlot->ShowUI(rc);
		}
	}
}


void PositionSelection::SetFishDisplayPosition()
{
	for (int i = 0; i < 6; i++) {
		if (i < 3) {
			m_fishDisplayPosition[i] = { m_fishDisplayPositionXcriteria + m_fishDisplayPositionXinterval * (i), 230.0f, 0.0f };
		}
		if (2 < i) {
			m_fishDisplayPosition[i] = { m_fishDisplayPositionXcriteria + m_fishDisplayPositionXinterval * (i - 3), -300.0f, 0.0f };
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
	if (m_currentArea != Area::ENEMY_SAME_POSITION) {//敵とポジションがかぶっていないとき。
		SetisDisplayingFalse();

		// インスタンス生成→ポジション設定→初期設定(内部でポジション設定の情報を使っている)
		m_playFishing = NewGO<PlayFishing>(0, "playFishing");
		SelectArea();
		m_playFishing->Init();

		SetDeactivate();
	}
}

bool PositionSelection::GetisDisplaying()
{
	return m_is_displaying;
}

void PositionSelection::SetDeactivate()
{
	//プレイヤーを非アクティブにする。
	m_player->Deactivate();
	//エネミーを非アクティブ。
	m_enemy->Deactivate();
	//ゲームカメラを非アクティブにする。
	m_gameCamera->Deactivate();
	//背景を非アクティブにする。
	/*backGround->Deactivate();*/
	/*backGround->BackGroundDeactive();*/
	//Uiを表示しない。
	m_shouldPartiallyDeactivate = true;
}

void PositionSelection::SetActivate()
{
	//プレイヤーをアクティブにする。
	m_player->Activate();
	//エネミーをアクティブ。
	m_enemy->Activate();
	//ゲームカメラをアクティブにする。
	m_gameCamera->Activate();
	//背景をアクティブにする。
	/*backGround->Activate();*/
	/*backGround->BackGroundActive();*/
	//UIを表示する。
	m_shouldPartiallyDeactivate = false;
}

/// <summary>
/// 制限時間をはかる。
/// </summary>
void PositionSelection::Timer()
{
	m_float_time = m_timelimit - m_stopwatch.GetElapsed();
	m_stopwatch.Stop();
	m_timeLimitUI->SetTime(m_float_time);
	if (m_float_time <= 0)
	{
		m_is_time_up = true;
		if (m_is_time_up == false) {
			m_stopwatch.Stop();
		}

	}
	/*char text[256];
	sprintf_s(text, "m_int_time = %d, com = %d\n", m_int_time);
	OutputDebugStringA(text);*/
}

float PositionSelection::GetTime()
{
	return m_float_time;
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

void PositionSelection::SelectArea()
{
	m_playFishing->SetFishManagerObjectName(AreaName[static_cast<int>(m_currentArea)]);
}

void PositionSelection::SetTotalValue(float individualValue)
{
	m_totalScore += individualValue;
}

void PositionSelection::FindFishHighScore()
{
	//一番スコアが高い魚がいる場所を探すアルゴリズム。
	Area compare;//比べる。
	m_enemyArea = Area::A;
	for (int i = 0; i < 4; i++) {
		if (m_fishManager[i]->GetScore() >= m_fishManager[i + 1]->GetScore()) {
			compare = m_positionStateArray[i];
		}
		else {
			compare = m_positionStateArray[i + 1];
		}
		if (m_fishManager[static_cast<int>(m_enemyArea)]->GetScore() <= m_fishManager[static_cast<int>(compare)]->GetScore()) {
			m_enemyArea = compare;
		}

	}

}

/// <summary>
/// プレイヤーが現在どのエリアにいるかを判定し、更新する。
/// </summary>
void PositionSelection::UpdatePlayerArea()
{
	const Vector3& playerPos = m_player->m_position;


	// 仮想的に画面を 2 行 × 3 列のグリッドに分けている
	bool isFrontRow = playerPos.z >= -175.0f;


	if (isFrontRow)
	{

		if (playerPos.x < COLUMN_LEFT_BORDER)
		{
			m_currentArea = Area::A;
		}

		else if (playerPos.x <= 353.0f)
		{
			m_currentArea = Area::B;
		}

		else
		{
			m_currentArea = Area::C;
		}
	}

	else
	{
		if (playerPos.x < COLUMN_LEFT_BORDER)
		{
			m_currentArea = Area::D;
		}
		else if (playerPos.x <= 353.0f) {
			m_currentArea = Area::E;
		}
		else
		{
			m_currentArea = Area::F;
		}
	}

	// 敵と同じエリアにいる場合の特別処理
	if (m_currentArea == m_enemyArea) {
		m_currentArea = Area::ENEMY_SAME_POSITION;
	}
	UpdateSlotFrameVisibility(m_currentArea);
}

/// <summary>
/// 魚を表示するフレームの色をそこにいるキャラクターによって変える。
/// </summary>
/// <param name="position"></param>
void PositionSelection::UpdateSlotFrameVisibility(Area position)
{
	
	m_fishSlot->UpdateSlotFrameVisibility(static_cast<int>(position), static_cast<int>(m_enemyArea));

}

/// <summary>
/// カメラのポジションをセットする。
/// </summary>
void PositionSelection::SetCameraPosition()
{
	m_gameCamera->SetPosition(m_backGround->m_shipPosition + Vector3{ 0.0f,1500.0f,0.0f }/*Vector3{ 0.0f,0.0f,1000.0f }*/);
	m_gameCamera->SetTarget(m_backGround->m_shipPosition + Vector3{ 0.0f,0.0f,100.0f });
}

SpriteRender& PositionSelection::GetFishUI(int num)
{
	m_fishUI[num] = m_fishManager[num]->m_ui;
		return *m_fishUI[num];
}

float PositionSelection::GerFishTimeRatio(int index)
{
	return m_fishManager[index]->GetTimeRatio();
}

void PositionSelection::SetCountdownFinished(bool countdownFinished)
{
	m_isCountdownFinished = countdownFinished;
}




//void PositionSelection::fishingPositionA_SetFish()
//{
//
//}
