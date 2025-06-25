#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "GameStartCountdown.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include"InGameState.h"
#include"GameGuide.h"


Title::Title()
{

}

Title::~Title()
{
}

bool Title::Start()
{
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/gameTiileBGM.wav");

	m_sound = NewGO<SoundSource>(0);

	m_sound->Init(0);

	m_sound->Play(false);

	return true;
}

bool Title::Init()
{
  spriteRender.Init("Assets/sprite/title.DDS", 1650.0f, 900.0f);

	m_pressA.Init("Assets/sprite/setumei/stateUI.DDS", 600.0f, 150.0f);
	m_pressA.SetPivot(Vector2{ 0.0f,0.0f });
	m_pressA.SetPosition(Vector3{ 100.0f,-150.0f,0.0f });
	m_pressA.Update();

	m_pressX.Init("Assets/sprite/setumei/playUI.DDS", 600.0f, 150.0f);
	m_pressX.SetPivot(Vector2{ 0.0f,0.0f });
	m_pressX.SetPosition(Vector3{ 100.0f,-350.0f,0.0f });
	m_pressX.Update();
	

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

		DeleteGO(m_sound);

		g_soundEngine->ResistWaveFileBank(7, "Assets/sound/pushButton2.wav");
		m_sound = NewGO<SoundSource>(7);
		m_sound->Init(7);
		m_sound->Play(false);
		return true; // Aボタンが押されたら状態を変更する
	}

	if (g_pad[0]->IsTrigger(enButtonX))
	{
		SetNextName("gameGuide");
		return true; // Aボタンが押されたら状態を変更する

	}
	return false; // タイトル状態では状態を変更しない
}

void Title::OnEnter()
{
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/gameTiileBGM.wav");

	m_sound = NewGO<SoundSource>(0);

	m_sound->Init(0);

	m_sound->Play(false);
}

void Title::OnExit()
{
}

void Title::Render(RenderContext& rc)
{
	//なぜかm_isStartがfalseになっているから描画されない。
	spriteRender.Draw(rc);
	m_pressA.Draw(rc);
	m_pressX.Draw(rc);
}