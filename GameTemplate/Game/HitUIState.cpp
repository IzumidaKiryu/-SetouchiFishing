#include "stdafx.h"
#include "HitUIState.h"

HitUIState::HitUIState()
{

}

void HitUIState::Update()
{
	UIMoveStateManager();
	SetPosition();
	SetCamera(m_cameraPos, m_cameraTarget);
	SetFish();
	SetFloat();
	
}

bool HitUIState::OnInit()
{

	m_hitUI.Init("Assets/modelData/Hit!_UI.DDS", 500, 200);
	m_hitUI.SetPivot(Vector2(0.5f, 0.5f));
	m_hitUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_hitUI.Update();

	m_hitUI_Bar.Init("Assets/modelData/Hit!_UI_Bar.DDS", 1500, 300);
	m_hitUI_Bar.SetPivot(Vector2(0.5f, 0.5f));
	m_hitUI_Bar.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_hitUI_Bar.Update();

	return true;
}

bool HitUIState::OnStart()
{
	m_initCameraPos = { m_cameraPos };
	m_initCameraTarget = { m_cameraTarget };
	m_endCameraTarget = { m_init_fishModelPos };
	m_endCameraPos = { GetPlayerPos() + Vector3 {0.0f,100.0f,100.0f} };

	return true;
}

void HitUIState::UIMoveStateManager()
{
	switch (m_uiMoveState)
	{
	case HitUIState::in:
		In();
		break;
	case HitUIState::wait:
		Wait();
		break;
	case HitUIState::out:
		Out();
		CameraManagement();
		break;
	default:
		break;
	}
	
}

void HitUIState::SetPosition()
{
	m_hitUI.SetPosition(m_hitUIPos);
	m_hitUI.Update();
	m_hitUI_Bar.SetPosition(m_hitUIBarPos);
	m_hitUI_Bar.Update();
}

void HitUIState::In()
{
	m_t += 0.05;

	
	m_hitUIPos.Lerp(m_t*m_t, m_initHitUIPos_in, m_endHitUIPos_in);
	m_hitUIBarPos.Lerp(m_t*m_t, m_initHitUIBarPos_in, m_endHitUIBarPos_in);

	if (m_t*m_t > 1) {
		m_uiMoveState = wait;
		m_t = 0;
	}
}

void HitUIState::Wait()
{
	m_t += 0.05;
	if (m_t > 1) {
		m_uiMoveState = out;
		m_t = 0;
	}
}

void HitUIState::Out()
{
	m_t += 0.05;

	if ((m_t * m_t)<=1) {
		m_hitUIPos.Lerp(m_t * m_t, m_initHitUIPos_out, m_endHitUIPos_out);
		m_hitUIBarPos.Lerp(m_t * m_t, m_initHitUIBarPos_out, m_endHitUIBarPos_out);
	}

	if (m_t > 1) {
		Success();
	}
}

void HitUIState::CameraManagement()
{
	
	m_cameraPos.Lerp(m_t,m_initCameraPos,m_endCameraPos);
	m_cameraTarget.Lerp(m_t,m_initCameraTarget,m_endCameraTarget);
	SetCamera(m_cameraPos, m_cameraTarget);
}

void HitUIState::Render(RenderContext& rc)
{
	m_hitUI_Bar.Draw(rc);
	m_hitUI.Draw(rc);
}
