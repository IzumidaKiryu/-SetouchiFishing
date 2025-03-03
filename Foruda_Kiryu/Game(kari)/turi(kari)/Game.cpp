#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Star.h"
#include "sound/SoundEngine.h"
#include "GameCrear.h"
#include "GetRotation.h"
#include "PositionSelection.h"

Game::Game()
{
	positionSelection= NewGO<PositionSelection>(0, "positionSelection");
	//////HPバー（内側）
	//hpBarInSide.Init("Assets/modelData/HPbar.DDS", 1024, 128);
	//hpBarInSide.SetPivot(Vector2(0.0f, 0.5f));
	//hpBarInSide.SetPosition(Vector3(-850.0f, 450.0f, 0.0f));
	//hpBarInSide.SetScale(Vector3{ 0.35f, 0.5f, 1.0f });
	//
	//getRotation= NewGO<GetRotation>(0, "getRotation");
	////プレイヤーのオブジェクトを作る。
	//player = NewGO<Player>(0, "player");

	////ゲームカメラのオブジェクトを作る。
	//gameCamera = NewGO<GameCamera>(0, "gamecamera");

	////背景のオブジェクトを作る。
	//backGround = NewGO<BackGround>(0);

	////Starクラスのオブジェクトを作る。
	//Star* star1 = NewGO<Star>(0,"star");
	//star1->position = { 100.0f,150.0f,-200.0f };
	//star1->firstPosition = star1->position;

	//Star* star2 = NewGO<Star>(0, "star");
	//star2->position = { 1000.0f,150.0f,-200.0f };
	//star2->firstPosition = star2->position;

	//Star* star3 = NewGO<Star>(0, "star");
	//star3->position = { 100.0f,250.0f,400.0f };
	//star3->firstPosition = star3->position;

	//Star* star4 = NewGO<Star>(0, "star");
	//star4->position = { 2300.0f,50.0f,-200.0f };
	//star4->firstPosition = star4->position;

	//Star* star5 = NewGO<Star>(0, "star");
	//star5->position = { 2700.0f,450.0f,400.0f };
	//star5->firstPosition = star5->position;
	//
	////ゲーム中のBGMを読み込む。
	//g_soundEngine->ResistWaveFileBank(1, "Assets/sound/gamebgm.wav");
	////ゲーム中のBGMを再生する。
	//gameBGM = NewGO<SoundSource>(0);
	//gameBGM->Init(1);
	//gameBGM->Play(true);
}

Game::~Game()
{
	DeleteGO(positionSelection);
	//プレイヤーを削除する。
	DeleteGO(player);
	//ゲームカメラを削除する。
	DeleteGO(gameCamera);
	//ゲーム中のBGMを削除する。
	DeleteGO(gameCamera);
	//背景を削除する。
	DeleteGO(backGround);
}

//更新処理。
void Game::Update()
{
	//rotationQuantity = { getRotation->rotationQuantity*0.15f/*5.0f*/,2.0f,0.0f};


	hpBarInSide.SetScale(rotationQuantity);

	hpBarInSide.Update();


	////ゲームクリア
	//if (player->starCount == 5) {
	//	//ゲームクリアのオブジェクトを作成
	//	GameClear* gameclear = NewGO<GameClear>(0);
	//	DeleteGO(this);
	//}
}
void Game::Render(RenderContext& rc)
{
	////フォントを描画する。
	//m_fontRender.Draw(rc);
	hpBarInSide.Draw(rc);
}