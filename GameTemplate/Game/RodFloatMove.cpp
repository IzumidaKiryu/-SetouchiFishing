#include "stdafx.h"
#include "RodFloatMove.h"
#include "GameCamera.h"


RodFloatMove::RodFloatMove()
{
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	m_rodFloatModel.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_rodFloatModel.SetScale(Vector3{ 1.0f,1.0f,1.0f });
	m_rodFloatModel.Init("Assets/modelData/uki.tkm");
	m_rodFloatModel.Update();
}

RodFloatMove::~RodFloatMove()
{
}

void RodFloatMove::Update()
{
	RodFloatStateManagement();
	ModelUpdate();
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_gameCamera->SetTarget(m_rodFloatPosition);
}

void RodFloatMove::ModelUpdate()
{
	m_rodFloatModel.SetPosition(m_rodFloatPosition);
	m_rodFloatModel.Update();
}

void RodFloatMove::Buoyancy()
{
	switch (m_buoyancyState)
	{
	case Down:
		t -= 0.01;
		m_buoyancy.y = m_buoyancy.y+t;
		m_rodFloatPosition = m_rodFloatPosition+m_buoyancy;
		if (m_rodFloatPosition.y <= water_surface_position_y-30.0f) {
			m_buoyancyState = Up;
			t = 0;
		}
		break;
	case Up:
		t+=0.01;
		m_buoyancy.y = m_buoyancy.y + t;
		m_rodFloatPosition = m_rodFloatPosition + m_buoyancy;
		if (m_rodFloatPosition.y >= water_surface_position_y+5) {
			m_rodFloatPosition .y= water_surface_position_y;
			m_floatState = floating;
			t = 0;
		}
		break;
	default:
		break;
	}
}

void RodFloatMove::Cast()
{
	t += 0.1;
		m_rodFloatPosition = (InitPos + first_velocity_vector * 20 * t) + g * t * t * 1 / 2;
		if (m_rodFloatPosition.y <= water_surface_position_y) {
			m_floatState = buoyancy;
			t = 0;
		}
}

void RodFloatMove::Float()
{
	t += 0.05;
	m_buoyancy.y = (cos(t))*0.5;//ã‰º‚É“®‚©‚·
	m_buoyancy.z = (cos(t * 0.7/*ŽüŠú‚ð‚¸‚ç‚·*/) * 0.5);//¶‰E‚É“®‚©‚·
	m_rodFloatPosition = m_rodFloatPosition + m_buoyancy;
}

void RodFloatMove::RodFloatStateManagement()
{

	switch (m_floatState)
	{
	case cast:
		Cast();
		break;
	case buoyancy:
		/*Buoyancy();
		break;*/
	case floating:
		Float();
		break;
	default:
		break;
	}
}

//void RodFloatMove::Buoyancy_Move_B()
//{
//	Buoyancy_t += 0.1;
//	//if (m_cos <= 0) {
//	//	m_cos = sin(Buoyancy_t)-1;
//	//}
//
//	m_buoyancy.y = (cos(Buoyancy_t)) * (1 + (1 / Buoyancy_t * 0.01)) * 0.8;
//	m_buoyancy.z = water_surface_position_y + (cos(Buoyancy_t * 0.7) * 0.7/**1/t*/);
//	m_rodFloatPosition = m_rodFloatPosition + m_buoyancy;
//}

void RodFloatMove::Render(RenderContext& rc)
{
	m_rodFloatModel.Draw(rc);
}

void RodFloatMove::SetRodFloatPositon()
{
	
	//if (m_rodFloatPosition.y <= water_surface_position_y) {
	//	landing_position = m_rodFloatPosition;

	//	Buoyancy();
	//}
}
