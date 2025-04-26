#include "stdafx.h"
#include "Title.h"
#include "Game.h"
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

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0, "game");
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}