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
	spriteRender.Init("Assets/sprite/title.DDS", 1920.0f, 1080.0f);
	m_pressA.Init("Assets/modelData/PromptUI/PressA.DDS", 600.0f, 600.0f);
	m_pressA.SetPivot(Vector2{ 0.0f,0.0f });
	m_pressA.SetPosition(Vector3{ 200.0f,-500.0f,0.0f });
	m_pressA.Update();
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
	m_pressA.Draw(rc);
}