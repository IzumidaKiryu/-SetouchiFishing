#include "stdafx.h"
#include "Game.h"


Game::Game()
{

}

Game::~Game()
{

}

bool Game::Start()
{
	//アニメーションクリップをロードする。
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_light.Init();
	m_modelRender.Init("Assets/modelData/unityChan.tkm",m_animationClips,enAnimationClip_Num,enModelUpAxisY);
	m_spriteRender.Init("Assets/sprite/Nozomi.DDS", 1920, 1080);
	
	return true;
}

void Game::Update()
{
	//wchar_t ws[256];
	//swprintf_s(ws, 256, L"悲鳴");
	m_fontRender.SetText(L"s");
	m_modelRender.PlayAnimation(enAnimationClip_Idle);
	m_modelRender.Update();
	m_spriteRender.Update();
}

void Game::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	//m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}
