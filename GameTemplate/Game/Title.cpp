#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "GameStartCountdown.h"
#include "sound/SoundEngine.h"


Title::Title()
{
	spriteRender.Init("Assets/sprite/yattabe.DDS", 1920.0f, 1080.0f);



	//タイトルのBGMを読み込む。
	//g_soundEngine->ResistWaveFileBank(0, "Assets/sound/titlebgm.wav");
	////タイトルのBGMを再生する。
	//titleBGM = NewGO<SoundSource>(0);
	//titleBGM->Init(0);
	//titleBGM->Play(true);
}

Title::~Title()
{
	//DeleteGO(titleBGM);
}

void Title::OnUpdate()
{
}

bool Title::ShouldChangeState()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{

		SetNextState(std::make_unique<GameStartCountdown>());
		return true; // Aボタンが押されたら状態を変更する
	}
	return false; // タイトル状態では状態を変更しない
}

void Title::OnEnter()
{
}

void Title::OnExit()
{
}

void Title::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}