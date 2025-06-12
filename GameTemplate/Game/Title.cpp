#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "GameStartCountdown.h"
#include "sound/SoundEngine.h"
#include"InGameState.h"


Title::Title()
{
}

Title::~Title()
{
}

bool Title::Start()
{
	return true;
}

bool Title::Init()
{
	spriteRender.Init("Assets/sprite/title.DDS", 1650.0f, 900.0f);
	return true;
}

void Title::OnUpdate()
{
}

bool Title::ShouldChangeState()
{

	if (g_pad[0]->IsTrigger(enButtonA))
	{

		SetNextName("inGameState");
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
	//なぜかm_isStartがfalseになっているから描画されない。
	spriteRender.Draw(rc);
}