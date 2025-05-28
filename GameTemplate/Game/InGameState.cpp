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

}

bool InGameState::Start()
{

    return true;
}

void InGameState::OnUpdate()
{

}

bool InGameState::ShouldChangeState()
{

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
}

