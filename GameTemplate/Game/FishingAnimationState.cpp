#include "stdafx.h"
#include "FishingAnimationState.h"
#include "FishModel.h"
#include"Player.h"

FishingAnimationState::FishingAnimationState()
{
}

FishingAnimationState::~FishingAnimationState()
{
	
}

bool FishingAnimationState::OnInit()
{
	return true;
}



bool FishingAnimationState::OnStart()
{
	/*m_player = FindGO<Player>("player_Playfishing");*/
	m_player->SetChastAnimation();
	m_initCameraPos = m_player->GetPos() + Vector3{ 0.0f,100.0f,100.0f };
	m_endCameraPos = m_player->GetPos() + Vector3{ 500.0f,500.0f,500.0f };

	m_initCameraTarget = m_fishModel->m_position;
	m_endCameraTarget = m_player->GetPos() + Vector3{ 0.0f,100.0f,0.0f };

	return true;
}

void FishingAnimationState::CameraManagement()
{
	m_player = FindGO<Player>("player_Playfishing");
	m_cameraPosTime += 0.06;
	m_cameraTargetTime += 0.06;

	if (m_cameraPosTime <= 1) {
		m_cameraPos.Lerp(m_cameraPosTime*m_cameraPosTime, m_initCameraPos, m_endCameraPos);
		m_cameraTarget.Lerp(m_cameraTargetTime, m_initCameraTarget, m_endCameraTarget);
	}
	SetCamera(m_cameraPos, m_cameraTarget);
}



void FishingAnimationState::Update()
{
	CameraManagement();
	SetCastAnimation();
	Count();
}

void FishingAnimationState::Count()
{
	m_animationTime++;
	if (m_animationTime > 140) {
		Success();
	};
}

bool FishingAnimationState::SetCastAnimation()
{
	bool is_playingAnimation= m_player->SetChastAnimation();
	return is_playingAnimation;
}
