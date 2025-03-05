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

void PositionSelection::SettingFishType(fishingPosition position)
{
	int randumRank;
	randumRank=rand()%100;

	if (0<=randumRank <= 62)//この三匹の魚の出現確率（100分の63）
	{
		int randumFish = rand() % 3;
		switch (randumFish)
		{
		case 0:
			position.fish =Sinju;
			break;
		case 1:
			position.fish = Hirame;
			break;
		case 2:
			position.fish = Jakotenn;
			break;
		default:
			break;
		}

	}
	if (63 <= randumRank <=90)//この２匹の出現確率（100分の26）
	{
		int randumFish = rand() % 2;
		switch (randumFish)
		{
		case 0:
			position.fish = Tatiuo;
			break;
		case 1:
			position.fish = Buri;
			break;
		default:
			break;
		}
	}
	if (91 <= randumRank <= 99)//出現確率（100分の9）
	{
		position.fish = Tai;
	}


}

void PositionSelection::SelectChangeFish(fishingPosition Position)
{
}
