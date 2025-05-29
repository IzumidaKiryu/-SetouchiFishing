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




InGameState::InGameState()
{
	//背景のオブジェクトを作る。
	m_backGround = NewGO<BackGround>(0, "backGround");
	//カメラ
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	//ポジション選択シーンのオブジェクトを作る。
	m_positionSelection = NewGO<PositionSelection>(0, "positionSelection");
	//プレイヤーのオブジェクトを作る。
	m_player = NewGO<Player>(0, "player");
	//エネミーのオブジェクトを作る。
	m_enemy = NewGO<Enemy>(0, "enemy");
	m_timeLimitUI = NewGO<TimeLimitUI>(0,"timeLimitUI");
}

bool InGameState::Start()
{

    return true;
}

void InGameState::OnUpdate()
{

	//ポジションセレクトに入った瞬間にタイマーをスタート。
	if (m_hasCountdownClassJustFinished) {
		m_stopwatch.Start();
		m_hasCountdownClassJustFinished = false;
	}

	//一度でもポジションセレクトに入ったら。
	//タイマーを動かす。
	if (m_hasCountdownClassFinished)
	{
		Timer();

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

void InGameState::SetInitFishManagers()
{
	for (int i = 0; i < 6; i++) {

		objectName[i] = new char[AreaName[i].size() + 1];


		//フィッシュマネージャーにつけるオブジェクトネームの設定。
		std::char_traits<char>::copy(objectName[i], AreaName[i].c_str(), AreaName[i].size() + 1);

		//フィッシュマネージャーの生成。
		m_fishManager[i] = NewGO<FishManager>(0, objectName[i]);

		SetFishUI(i);
	}


}

void InGameState::ChangeFish()
{
	for (int i = 0; i < 6; i++) {
		//フィッシュマネージャーの生成。
		if (m_fishManager[i]->GetShouldFishChange() == true) {

			DeleteGO(m_fishManager[i]);

			//フィッシュマネージャーの生成。
			m_fishManager[i] = NewGO<FishManager>(0, objectName[i]);

			SetFishUI(i);
		}

	}
}

float InGameState::GerFishTimeRatio(int index)
{
	return m_fishManager[index]->GetTimeRatio();

}

void InGameState::SetFishUI(int index)
{
	m_fishUI[index] = m_fishManager[index]->m_ui;
}

SpriteRender& InGameState::GetFishUI(int index)
{
	return *m_fishUI[index];
}

float InGameState::GetFishScore(int index)
{
	return m_fishManager[index]->GetScore();
}
