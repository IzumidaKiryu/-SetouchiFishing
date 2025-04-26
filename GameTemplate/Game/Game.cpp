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

Game::Game()
{
	m_skyCube = NewGO<SkyCube>(0, "skyCube");
	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetScale(400.0f);//4000倍にすると描画がなくなるかも。

	//m_rul = NewGO<GameResult>(0, "rusut");
	positionSelection = NewGO<PositionSelection>(0, "positionSelection");
	//m_scoreDisplay = NewGO<ScoreDisplay>(0, "scoreDisplay");
	//m_playFishing = NewGO<PlayFishing>(0, "playFishing");
	//////HP�o�[�i����j
	//hpBarInSide.Init("Assets/modelData/HPbar.DDS", 1024, 128);
	//hpBarInSide.SetPivot(Vector2(0.0f, 0.5f));
	//hpBarInSide.SetPosition(Vector3(-850.0f, 450.0f, 0.0f));
	//hpBarInSide.SetScale(Vector3{ 0.35f, 0.5f, 1.0f });
	//
	//getRotation= NewGO<GetRotation>(0, "getRotation");
	////�v���C���[�̃I�u�W�F�N�g����B
	//player = NewGO<Player>(0, "player");

	////�Q�[���J�����̃I�u�W�F�N�g����B
	//gameCamera = NewGO<GameCamera>(0, "gamecamera");

	////�w�i�̃I�u�W�F�N�g����B
	//backGround = NewGO<BackGround>(0);
	
}

Game::~Game()
{
	DeleteGO(positionSelection);
	DeleteGO(player);
	DeleteGO(gameCamera);
	
	DeleteGO(backGround);
}


void Game::Update()
{
	//rotationQuantity = { getRotation->rotationQuantity*0.15f/*5.0f*/,2.0f,0.0f};


	/*hpBarInSide.SetScale(m_rotationQuantity);

	hpBarInSide.Update();*/
}
void Game::Render(RenderContext& rc)
{
	////m_fontRender.Draw(rc);
	//hpBarInSide.Draw(rc);
}