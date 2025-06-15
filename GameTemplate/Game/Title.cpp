#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "GameStartCountdown.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include"InGameState.h"


Title::Title()
{
}

Title::~Title()
{
}

bool Title::Start()
{
	g_soundEngine->ResistWaveFileBank(0,"Assets/sound/gameTiileBGM.wav");

	m_sound = NewGO<SoundSource>(0);

	m_sound->Init(0);

	m_sound->Play(false);
	return true;
}

bool Title::Init()
{
  spriteRender.Init("Assets/sprite/title.DDS", 1650.0f, 900.0f);
	m_pressA.Init("Assets/sprite/setumei/State.DDS", 600.0f, 150.0f);
	m_pressA.SetPivot(Vector2{ 0.0f,0.0f });
	m_pressA.SetPosition(Vector3{ 100.0f,-100.0f,0.0f });
	m_pressA.Update();

	m_pressB.Init("Assets/sprite/setumei/Play.DDS", 600.0f, 150.0f);
	m_pressB.SetPivot(Vector2{ 0.0f,0.0f });
	m_pressB.SetPosition(Vector3{ 100.0f,-300.0f,0.0f });
	m_pressB.Update();

	m_bInfo.Init("Assets/sprite/setumei/setumei.DDS",1650.0f, 900.0f);
    m_bInfo.SetPivot(Vector2{ 0.0f,0.0f });
    m_bInfo.SetPosition(Vector3{ 100.0f, -100.0f, 0.0f });
    m_bInfo.Update();

	/*m_bInfo.Init("Assets/sprite/setumei/setumei_2.DDS", 1650.0f, 900.0f);
	m_bInfo.SetPivot(Vector2{ 0.0f,0.0f });
	m_bInfo.SetPosition(Vector3{ 100.0f, -100.0f, 0.0f });
	m_bInfo.Update();

	m_bInfo.Init("Assets/sprite/setumei/setumei_3.DDS", 1650.0f, 900.0f);
	m_bInfo.SetPivot(Vector2{ 0.0f,0.0f });
	m_bInfo.SetPosition(Vector3{ 100.0f, -100.0f, 0.0f });
	m_bInfo.Update();

	m_bInfo.Init("Assets/sprite/setumei/setumei_4.DDS", 1650.0f, 900.0f);
	m_bInfo.SetPivot(Vector2{ 0.0f,0.0f });
	m_bInfo.SetPosition(Vector3{ 100.0f, -100.0f, 0.0f });
	m_bInfo.Update();

	m_bInfo.Init("Assets/sprite/setumei/setumei_5.DDS", 1650.0f, 900.0f);
	m_bInfo.SetPivot(Vector2{ 0.0f,0.0f });
	m_bInfo.SetPosition(Vector3{ 100.0f, -100.0f, 0.0f });
	m_bInfo.Update();

	m_bInfo.Init("Assets/sprite/setumei/setumei_6.DDS", 1650.0f, 900.0f);
	m_bInfo.SetPivot(Vector2{ 0.0f,0.0f });
	m_bInfo.SetPosition(Vector3{ 100.0f, -100.0f, 0.0f });
	m_bInfo.Update();

	m_bInfo.Init("Assets/sprite/setumei/setumei_7.DDS", 1650.0f, 900.0f);
	m_bInfo.SetPivot(Vector2{ 0.0f,0.0f });
	m_bInfo.SetPosition(Vector3{ 100.0f, -100.0f, 0.0f });
	m_bInfo.Update();

	m_bInfo.Init("Assets/sprite/setumei/setumei_8.DDS", 1650.0f, 900.0f);
	m_bInfo.SetPivot(Vector2{ 0.0f,0.0f });
	m_bInfo.SetPosition(Vector3{ 100.0f, -100.0f, 0.0f });
	m_bInfo.Update();

	m_bInfo.Init("Assets/sprite/setumei/setumei_9.DDS", 1650.0f, 900.0f);
	m_bInfo.SetPivot(Vector2{ 0.0f,0.0f });
	m_bInfo.SetPosition(Vector3{ 100.0f, -100.0f, 0.0f });
	m_bInfo.Update();*/


	return true;
}

void Title::OnUpdate()
{
    // Bボタンで表示切り替え
    if (g_pad[0]->IsTrigger(enButtonB)) {
        m_isShowBInfo = !m_isShowBInfo;
    }
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
	m_pressB.Draw(rc);
	if (m_isShowBInfo) {
        m_bInfo.Draw(rc);
    }
}