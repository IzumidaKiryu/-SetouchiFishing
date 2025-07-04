#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "GameStartCountdown.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include"InGameState.h"
#include"GameGuide.h"

namespace
{
	static const float TITLE_SPRITE_SIZE_WIDE = 1650.0f;// タイトル画面のスプライトの幅
	static const float TITLE_SPRITE_SIZE_HIGH = 900.0f;// タイトル画面のスプライトの高さ
	static const float PRESS_SPRITE_SIZE_WIDE = 600.0f;// セレクトボタンのスプライトの幅
	static const float PRESS_SPRITE_SIZE_HIGH = 150.0f;// セレクトボタンのスプライトの高さ
	static const Vector2 PRESSA_SPRITE_PIVOT = { 0.0f,0.0f };// セレクトボタンのスプライトのピボット位置
	static const Vector2 PRESSX_SPRITE_PIVOT = { 0.0f,0.0f };// セレクトボタンのスプライトのピボット位置
	static const Vector3 PRESSA_SPRITE_POSITION = { 100.0f,-150.0f,0.0f };// セレクトボタンのスプライトの位置
	static const Vector3 PRESSX_SPRITE_POSITION = { 100.0f,-350.0f,0.0f };// セレクトボタンのスプライトの位置
}
Title::Title() = default;
Title::~Title() = default;

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
  spriteRender.Init("Assets/sprite/title.DDS", TITLE_SPRITE_SIZE_WIDE, TITLE_SPRITE_SIZE_HIGH);

	m_pressA.Init("Assets/sprite/setumei/stateUI.DDS", PRESS_SPRITE_SIZE_WIDE, PRESS_SPRITE_SIZE_HIGH);
	m_pressA.SetPivot(PRESSA_SPRITE_PIVOT);
	m_pressA.SetPosition(PRESSA_SPRITE_POSITION);
	m_pressA.Update();

	m_pressX.Init("Assets/sprite/setumei/playUI.DDS", PRESS_SPRITE_SIZE_WIDE, PRESS_SPRITE_SIZE_HIGH);
	m_pressX.SetPivot(PRESSX_SPRITE_PIVOT);
	m_pressX.SetPosition(PRESSX_SPRITE_POSITION);
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