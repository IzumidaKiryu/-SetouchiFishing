#include "stdafx.h"
#include "PositionSelection.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "GameCamera.h"
#include "BackGround.h"

PositionSelection::PositionSelection()
{
	srand(time(NULL));

	//プレイヤーのオブジェクトを作る。
	player = NewGO<Player>(0, "player");

	//ゲームカメラのオブジェクトを作る。
	gameCamera = NewGO<GameCamera>(0, "gamecamera");

	//背景のオブジェクトを作る。
	backGround = NewGO<BackGround>(0);
	//ゲーム中のBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/gamebgm.wav");
	//ゲーム中のBGMを再生する。
	gameBGM = NewGO<SoundSource>(0);
	/*gameBGM->Init(1);
	gameBGM->Play(true);*/
	gameCamera->m_toCameraPos.Set(0.0f, 1250.0f, -250.0f);
}

PositionSelection::~PositionSelection()
{
	//プレイヤーを削除する。
	DeleteGO(player);
	//ゲームカメラを削除する。
	DeleteGO(gameCamera);
	//ゲーム中のBGMを削除する。
	DeleteGO(gameCamera);
	//背景を削除する。
	DeleteGO(backGround);
}

void PositionSelection::Update()
{
}

void PositionSelection::Render(RenderContext& rc)
{
}

//void PositionSelection::fishingPositionA_SetFish()
//{
//
//}
