#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Star.h"
#include "sound/SoundEngine.h"
#include "GetRotation.h"
#include "PositionSelection.h"
#include "PlayFishing.h"
#include "ScoreDisplay.h"
#include "GameResult.h"
#include "SkyCube.h"
#include "FishSlot.h"
#include "GameStartCountdown.h"
#include "Enemy.h"
#include "Player.h"
#include"PositionSelection.h"
#include"GameStateBase.h"
#include"Title.h"
#include< memory >
#include <iostream>

Game::Game()
{

	currentState = move(std::make_unique<Title>());
	NewGOGameObjects();
	DeactivateGameObjects();
}

Game::~Game()
{
	DeleteGO(positionSelection);
	DeleteGO(m_backGround);
	DeleteGO(m_skyCube);
	//DeleteGO(player);
	DeleteGO(gameCamera);
	
	//DeleteGO(backGround);
}

bool Game::Start()
{
	return true;
}


void Game::Update()
{
	if (currentState->ShouldChangeState())
	{
		currentState->Exit();

		currentState = currentState->NextState();
		if (currentState)
		{
			currentState->Enter();
		}
	}
}
void Game::Render(RenderContext& rc)
{
}

void Game::NewGOGameObjects()
{
	m_skyCube = NewGO<SkyCube>(0, "skyCube");
	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetScale(600.0f);//4000倍にすると描画がなくなるかも。

	//背景のオブジェクトを作る。
	m_backGround = NewGO<BackGround>(0, "backGround");
	//カウントダウン
	m_gameStartCountdown = NewGO<GameStartCountdown>(0, "gameStartCountdown");
	//カメラ
	gameCamera = NewGO<GameCamera>(0, "gamecamera");
	//ポジション選択シーンのオブジェクトを作る。
	m_positionSelection = NewGO<PositionSelection>(0, "positionSelection");
	//プレイヤーのオブジェクトを作る。
	m_player = NewGO<Player>(0, "player");
	//エネミーのオブジェクトを作る。
	m_enemy = NewGO<Enemy>(0, "enemy");

}

void Game::DeactivateGameObjects()
{
	m_enemy->Deactivate();
	m_player->Deactivate();
	m_positionSelection->Deactivate();
	m_gameStartCountdown->Deactivate();
	m_backGround->Deactivate();
	m_skyCube->Deactivate();
}
