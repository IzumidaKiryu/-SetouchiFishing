#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Star.h"
#include "sound/SoundEngine.h"
#include "GetRotation.h"
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
#include"GameResult.h"
#include"InGameState.h"
#include< memory >
#include <iostream>

Game::Game()
{
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

	NewGOStateObjects();
	DeactivateGameObjects();

	//現在のステートを初期化。
	currentState = FindGO<Title>("title");

	return true;
}

bool Game::Init()
{

	return true;
}


void Game::Update()
{
	if (currentState->ShouldChangeState())
	{

		currentState->Exit();

		currentState = currentState->ChangeState();

		if (currentState)
		{
			currentState->Enter();
		}
	}
}
void Game::Render(RenderContext& rc)
{
}

void Game::NewGOStateObjects()
{
	m_skyCube = NewGO<SkyCube>(0, "skyCube");
	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetScale(600.0f);//4000倍にすると描画がなくなるかも。


	m_title = NewGO<Title>(0, "title");
	m_title->Init();

	m_inGameState = NewGO<InGameState>(0, "inGameState");
	m_inGameState->Init();

	m_gameResult = NewGO<GameResult>(0,"gameResult");
	m_gameResult->Init();



}

void Game::DeactivateGameObjects()
{
	m_inGameState->Deactivate();
	m_gameResult->Deactivate();
}

void Game::ResetInGame()
{
	DeleteGO(m_inGameState);
	m_inGameState = NewGO<InGameState>(0, "inGameState");
	m_inGameState->Deactivate();

}
