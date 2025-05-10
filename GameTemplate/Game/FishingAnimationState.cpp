#include "stdafx.h"
#include "FishingAnimationState.h"
#include"Player.h"

FishingAnimationState::FishingAnimationState()
{
	m_player = FindGO<Player>("player");
	SetCastAnimation();
}

FishingAnimationState::~FishingAnimationState()
{
}

bool FishingAnimationState::Start()
{

	return true;
}

void FishingAnimationState::Update()
{

}

void FishingAnimationState::Count()
{

}

void FishingAnimationState::SetCastAnimation()
{
	/*m_player->SetChastAnimation();*/
}
