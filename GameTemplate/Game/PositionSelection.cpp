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
#include"InGameState.h"
#include< memory >




PositionSelection::PositionSelection()
{
	

	srand(time(NULL));
	

}

PositionSelection::~PositionSelection()
{
	//横取りゲージを削除する。
	DeleteGO(m_stealPositionBar);
	//プレイヤーを削除する。
	DeleteGO(m_player);

	DeleteGO(m_playFishing);
	DeleteGO(m_fishSlot);
}

bool PositionSelection::Start()
{
	FindGameObjects();


	//m_enemy->SetCountdownFinished(true);//カウントダウンが終わったことを伝える。
	return true;
}
void PositionSelection::Update()
{
	if (m_isCountdownFinished==true)
	{

		//プレイヤーの現在エリアを更新。
		UpdatePlayerArea();

		//アクティブ？。
		if (m_shouldPartiallyDeactivate == false) {

			if (g_pad[0]->IsTrigger(enButtonA)) {
				ChangeSceneToPlayFishing();
				m_gameCamera->Activate();
			}
		}
		else {
			m_gameCamera->Deactivate();
		}

		FindFishHighScore();

	}
}



void PositionSelection::Init()
{
	//横取りゲージを作る。
	m_stealPositionBar = NewGO<StealPositionBar>(0, "stealPositionBar");

	//ゲーム中のBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/gamebgm.wav");



	//UIの場所を決める。
	SetFishDisplayPosition();


	//フィッシュスロットのオブジェクトを作る。
	m_fishSlot = NewGO<FishSlot>(0, "fishSlot");
	m_fishSlot->ThiscClassInit();

	SetCountdownFinished(true);

	m_enemy->SetCountdownFinished(true);//カウントダウンが終わったことを伝える。

}

void PositionSelection::FindGameObjects()
{
	m_player = FindGO<Player>("player");
	m_enemy = FindGO<Enemy>("enemy");
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_backGround = FindGO<BackGround>("backGround");
	m_inGameState = FindGO<InGameState>("inGameState");
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

	if (m_isCountdownFinished == true) {
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
		//プレイフィッシングクラスにいまの
		// エリアの魚の情報知らせる。

		NotifyCurrentArea();
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

float PositionSelection::GetTime()
{
	return m_float_time;
}



/// <summary>
/// 今のエリアを、プレイフィッシングに知らせる。
/// </summary>
void PositionSelection::NotifyCurrentArea()
{
	m_playFishing->SetCurrentFishManagerObjectName(m_inGameState->GetAreaName(static_cast<int>(m_currentArea)));
}

void PositionSelection::SetTotalValue(float individualValue)
{
	m_totalScore += individualValue;
}

/// <summary>
/// 一番スコアが高い魚を探す。
/// </summary>
void PositionSelection::FindFishHighScore()
{
	//一番スコアが高い魚がいる場所を探すアルゴリズム。
	Area bestArea=Area::A;

	float maxScore = -1.0f;


	for (int i = 0; i < 6; ++i) {
		float score = m_inGameState->GetFishScore(i);
		if (score > maxScore) {
			maxScore = score;
			bestArea = m_positionStateArray[i];
		}
	}

	m_enemyArea = bestArea;

}

/// <summary>
/// プレイヤーが現在どのエリアにいるかを判定し、更新する。
/// </summary>
void PositionSelection::UpdatePlayerArea()
{
	const Vector3& playerPos = m_player->m_position;


	// 仮想的に画面を 2 行 × 3 列のグリッドに分けている
	bool isFrontRow = playerPos.z >= FRONT_BACK_Z_BORDER;


	if (isFrontRow)
	{

		if (playerPos.x < COLUMN_LEFT_BORDER)
		{
			m_currentArea = Area::A;
		}

		else if (playerPos.x <= COLUMN_RIGHT_BORDER)
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
		else if (playerPos.x <= COLUMN_RIGHT_BORDER) {
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
	//m_gameCamera->SetPosition(m_backGround->m_shipPosition + Vector3{ 0.0f,1500.0f,0.0f }/*Vector3{ 0.0f,0.0f,1000.0f }*/);
	//m_gameCamera->SetTarget(m_backGround->m_shipPosition + Vector3{ 0.0f,0.0f,100.0f });
}


void PositionSelection::SetCountdownFinished(bool countdownFinished)
{
	m_isCountdownFinished = countdownFinished;
}




//void PositionSelection::fishingPositionA_SetFish()
//{
//
//}
