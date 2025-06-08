#include "stdafx.h"
#include "InGameState.h"
#include"GameStartCountdown.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "PositionSelection.h"
#include "PlayFishing.h"
#include "Enemy.h"
#include"PositionSelection.h"
#include"TimeLimitUI.h"
#include "FishManager.h"
#include "ScoreManager.h"
#include"FishSlot.h"




InGameState::InGameState()
{
}

bool InGameState::Start()
{
	//背景のオブジェクトを作る。
	m_backGround = NewGO<BackGround>(0, "backGround");
	m_backGround->Init();
	//カメラ
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	m_gameCamera->Init();


	//ポジション選択シーンのオブジェクトを作る。
	m_positionSelection = NewGO<PositionSelection>(0, "positionSelection");

	//プレイヤーのオブジェクトを作る。
	m_player = NewGO<Player>(0, "player");
	m_player->Init();

	//エネミーのオブジェクトを作る。
	m_enemy = NewGO<Enemy>(0, "enemy");
	m_enemy->Init();
	//
	m_timeLimitUI = NewGO<TimeLimitUI>(0, "timeLimitUI");
	m_timeLimitUI->Init();

	m_scoreManager = NewGO<ScoreManager>(0, "scoreManager");
	m_scoreManager->Init();
    return true;
}

bool InGameState::Init()
{
	

	return true;
}

void InGameState::OnUpdate()
{
	//一度でもポジションセレクトに入ったら。
	if (m_hasCountdownClassFinished)
	{
		//タイマーを動かす。
		Timer();

		//魚を生成
		ChangeFish();
	}
}

bool InGameState::ShouldChangeState()
{
	if (m_isCountdownFinished) {
		SetNextName("gameResult");
		return true;
	}
    return false;
}

void InGameState::OnEnter()
{
    m_gameStartCountdown = NewGO<GameStartCountdown>(0, "GameStartCountdown");
}

void InGameState::OnExit()
{

	//ここにリアル画面にスコアを渡す関数を書く。

	DeleteGameObjects();

}

void InGameState::Render(RenderContext& rc)
{
	if (m_hasCountdownClassFinished) {
		m_timeLimitUI->m_timeFont.Draw(rc);
	}

}

void InGameState::Timer()
{
	m_time = m_timelimit - m_stopwatch.GetElapsed();
	m_stopwatch.Stop();
	m_timeLimitUI->SetTime(m_time);
	if (m_time <= 0)
	{
		m_isCountdownFinished=true;
		m_stopwatch.Stop();
	}

}

float InGameState::GetTime()
{
	return m_time;
}

void InGameState::SetHasCountdownClassFinished(bool flag)
{
	m_hasCountdownClassFinished = flag;
}

void InGameState::SetHasCountdownClassJustFinished(bool flag)
{
	m_hasCountdownClassJustFinished = flag;
}

void InGameState::ChangeFish()
{
	for (int i = 0; i < 6; i++) {

		Area b = static_cast<Area>(i);

		//フィッシュマネージャーの生成。
		
		//敵かプレイヤーがそこで釣りをしていなかったら。
		if (m_enemy->GetIsFishingInArea(static_cast<Area>(i))==false
			&&m_player->GetIsFishingInArea(static_cast<Area>(i)) == false)
		{
			if (m_fishManager[i]->GetShouldFishChange() == true)
			{
			//フィッシュマネージャーの生成。
				/// ★ UIポインタを先に無効化する！！
				m_fishUI[i] = nullptr;


				DeleteGO(m_fishManager[i]);

				//フィッシュマネージャーの生成。
				m_fishManager[i] = NewGO<FishManager>(0, AreaName[i].c_str());

				m_fishManager[i]->Init();


				SetFishUI(i);
		}
		}

	}
}

void InGameState::ChangeFish(int Areaindex)
{

	DeleteGO(m_fishManager[Areaindex]);

	//フィッシュマネージャーの生成。
	m_fishManager[Areaindex] = NewGO<FishManager>(0, AreaName[Areaindex].c_str());

	m_fishManager[Areaindex]->Init();


	SetFishUI(Areaindex);
}

void InGameState::CreateInitialFish()
{
	for (int i = 0; i < 6; i++) 
	{

		//フィッシュマネージャーの生成。
		m_fishManager[i] = NewGO<FishManager>(0, AreaName[i].c_str());
		m_fishManager[i]->Init();

		SetFishUI(i);
	}
}

float InGameState::GerFishTimeRatio(int index)
{
	return m_fishManager[index]->GetTimeRatio();

}

void InGameState::SetFishUI(int index)
{
	m_fishUI[index] = m_fishManager[index]->GetUI();
}

SpriteRender& InGameState::GetFishUI(int index)
{
	return *m_fishUI[index];
}

float InGameState::GetFishScore(int index)
{
	return m_fishManager[index]->GetScore();
}

void InGameState::SetScore(float score)
{

}

void InGameState::DeleteGameObjects()
{
	DeleteGO(m_positionSelection);
	DeleteGO(m_backGround);
	DeleteGO(m_gameCamera);
	DeleteGO(m_player);
	DeleteGO(m_enemy);
	DeleteGO(m_timeLimitUI);
}

/// <summary>
/// カウントダウンが終わった瞬間カウントダウンクラスで呼ばれる。
/// </summary>
void InGameState::OnCountdownFinished()
{
	m_stopwatch.Start();

	CreateInitialFish();

	//敵が最初に釣る場所を決める
	m_enemy->SetTargetFishingArea(m_positionSelection->FindFishHighScore()/*スコアが一番高い魚を探す*/);

	m_hasCountdownClassJustFinished = false;

}

std::string InGameState::GetAreaName(int index)
{
	return AreaName[index];
}

FishData InGameState::GetFishData(int index)
{
	return m_fishManager[index]->GetFishData();
}
