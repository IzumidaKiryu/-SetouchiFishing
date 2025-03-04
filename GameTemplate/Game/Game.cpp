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

	m_modelRender.Init("Assets/modelData/unityChan.tkm",m_animationClips,enAnimationClip_Num);
	return true;
}

void Game::Update()
{
	m_modelRender.PlayAnimation(enAnimationClip_Idle);
	m_modelRender.Update();
}

void Game::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
