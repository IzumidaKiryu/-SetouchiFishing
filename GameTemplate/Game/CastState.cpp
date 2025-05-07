#include "stdafx.h"
#include "CastState.h"
#include "PlayFishingStateBase.h"
#include "RodFloatMove.h"
#include"Player.h"
#include"PlayFishing.h"

CastState::CastState()
{
	//ウキを作成。
	m_rodFloatMove = NewGO<RodFloatMove>(0, "rodFloatMove");
}

CastState::~CastState()
{
	m_rodFloatMove = NewGO<RodFloatMove>(0, "rodFloatMove");
	
}

void CastState::Update()
{
	Cast();
	m_player = FindGO<Player>("player_Playfishing");

	SetCamera(
		Vector3{ 500.0f,100.0f,20.0f },
		m_rodFloatMove->GetPosition()
	);


}

void CastState::Cast()
{
	t += 0.1;
	m_playFishing = FindGO<PlayFishing>("playFishing");
	m_rodFloatPosition = m_float_initPos + (first_velocity_vector * 100 * m_playFishing->m_castStrength * t) + g * t * t * 1 / 2;
	SumRodFloatPosition(m_rodFloatPosition);
	SetFloat();
	if (m_rodFloatPosition.y <= water_surface_position_y) {
		Success();
	}
}
