#include "stdafx.h"
#include "SuccessUIState.h"

SuccessUIState::SuccessUIState()
{

}

void SuccessUIState::Update()
{
	SuccessUIMoveStateManager();
	SetPosition();
	SetFloat();

}

bool SuccessUIState::OnInit()
{
	m_successUI.Init("Assets/modelData/newSuccessUI.DDS", 500, 200);
	m_successUI.SetPivot(Vector2(0.5f, 0.5f));
	m_successUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_successUI.Update();

	m_successUI_Bar.Init("Assets/modelData/newSuccessUIBack.DDS", 1500, 300);
	m_successUI_Bar.SetPivot(Vector2(0.5f, 0.5f));
	m_successUI_Bar.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_successUI_Bar.Update();

	return true;
}

bool SuccessUIState::OnStart()
{
	m_initCameraPos = { m_cameraPos };
	m_initCameraTarget = { m_cameraTarget };
	m_endCameraTarget = { m_initFishModelPos };
	m_endCameraPos = { GetPlayerPos() + Vector3 {0.0f,100.0f,100.0f} };

	return true;
}

void SuccessUIState::SuccessUIMoveStateManager()
{
	switch (m_successUIMoveState)
	{
	case SuccessUIState::in:
		In();
		break;
	case SuccessUIState::wait:
		Wait();
		break;
	case SuccessUIState::out:
		Out();
		CameraManagement();
		break;
	default:
		break;
	}

}

void SuccessUIState::SetPosition()
{
	m_successUI.SetPosition(m_successUIPos);
	m_successUI.Update();
	m_successUI_Bar.SetPosition(m_successUIBarPos);
	m_successUI_Bar.Update();
}

void SuccessUIState::In()
{
	m_t += 0.05;


	m_successUIPos.Lerp(m_t * m_t, m_initSuccessUIPos_in, m_endSuccessUIPos_in);
	m_successUIBarPos.Lerp(m_t * m_t, m_initSuccessUIBarPos_in, m_endSuccessUIBarPos_in);

	if (m_t * m_t > 1) {
		m_successUIMoveState = wait;
		m_t = 0;
	}
}

void SuccessUIState::Wait()
{
	m_t += 0.05;
	if (m_t > 1) {
		m_successUIMoveState = out;
		m_t = 0;
	}
}

void SuccessUIState::Out()
{
	m_t += 0.05;

	if ((m_t * m_t) <= 1) {
		m_successUIPos.Lerp(m_t * m_t, m_initSuccessUIPos_out, m_endSuccessUIPos_out);
		m_successUIBarPos.Lerp(m_t * m_t, m_initSuccessUIBarPos_out, m_endSuccessUIBarPos_out);
	}

	if (m_t > 1) {
		Success();
	}
}

//void SuccessUIState::CameraManagement()
//{
//
//	m_cameraPos.Lerp(m_t, m_initCameraPos, m_endCameraPos);
//	m_cameraTarget.Lerp(m_t, m_initCameraTarget, m_endCameraTarget);
//	SetCamera(m_cameraPos, m_cameraTarget);
//}

void SuccessUIState::Render(RenderContext& rc)
{
	m_successUI_Bar.Draw(rc);
	m_successUI.Draw(rc);
}