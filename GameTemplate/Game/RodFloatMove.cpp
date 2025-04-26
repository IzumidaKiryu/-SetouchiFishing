#include "stdafx.h"
#include "RodFloatMove.h"
#include "GameCamera.h"
#include"SceneFightFish.h";
#include"PlayFishing.h"
#include <cmath>  // sqrt�֐����g�����߂ɕK�v
#include <complex>   // ���f�����C�u����

RodFloatMove::RodFloatMove()
{
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
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
	//RodFloatStateManagement();
	SetPosition();
	ModelUpdate();
}

void RodFloatMove::ModelUpdate()
{
	m_rodFloatModel.SetPosition(m_rodFloatPosition);
	m_rodFloatModel.Update();
}

//void RodFloatMove::Buoyancy()
//{
//	switch (m_buoyancyState)
//	{
//	case Down:
//		t -= 0.01;
//		m_floating.y = m_floating.y+t;
//		m_rodFloatPosition = m_rodFloatPosition+m_floating;
//		if (m_rodFloatPosition.y <= water_surface_position_y-30.0f) {
//			m_buoyancyState = Up;
//			t = 0;
//		}
//		break;
//	case Up:
//		t+=0.01;
//		m_floating.y = m_floating.y + t;
//		m_rodFloatPosition = m_rodFloatPosition + m_floating;
//		if (m_rodFloatPosition.y >= water_surface_position_y+5) {
//			m_rodFloatPosition .y= water_surface_position_y;
//			m_floatState = floating;
//			t = 0;
//		}
//		break;
//	default:
//		break;
//	}
//}

//void RodFloatMove::Cast()
//{
//	t += 0.1;
//	/*m_z_axis_value_drop_float = 100.0f;*/
//
//	/*scalar_multiply_in_first_velocity_vector =(sqrt(-g.y)*(InitPos.z- m_z_axis_value_drop_float))/ (first_velocity_vector.y*sqrt(first_velocity_vector.z)*sqrt((1* - 2 * InitPos.y * first_velocity_vector.z)+2* InitPos.z-2* m_z_axis_value_drop_float));*/
//
//
//	//	�i�ŏ��̃|�W�V����+�����x�N�g���~�萔�~���j�{�d�́~�i���O2�j/2
//		m_rodFloatPosition = (InitPos + first_velocity_vector * 100*m_scalar_multiply_in_first_velocity_vector * t) +g * t * t * 1 / 2;
//
//		//�v���C�t�B�b�V���O�ɃE�L�̋����̊����𑗂�B
//		m_playFishing = FindGO<PlayFishing>("playFishing");
//		m_playFishing->SetCurrent_range_and_max_range_rate(m_current_range_and_max_range_rate);
//
//		//�C�ɂ��������ׂ�B
//		if (m_rodFloatPosition.y <= water_surface_position_y) {
//
//			m_floatState = buoyancy;
//			t = 0;
//			m_cast_end = true;
//		}
//}

void RodFloatMove::Float()
{
	t += 0.05;
	m_floating.y = (cos(t))*10;//�㉺�ɓ�����
	m_floating.x = (cos(t * 0.7/*���������炷*/)*10 );//���E�ɓ�����
	m_rodFloatPosition = m_rodFloatPosition + m_floating;
}

//void RodFloatMove::RodFloatStateManagement()
//{
//
//	switch (m_floatState)
//	{
//	case initState:
//
//		break;
//	case cast:
//		Cast();
//		break;
//	case buoyancy:
//		/*Buoyancy();
//		break;*/
//	case floating:
//		Float();
//		break;
//	case fightFish:
//		FightFish();
//		break;
//	default:
//		break;
//	}
//}

//void RodFloatMove::SetCastState()
//{
//	m_floatState = cast;
//}

//void RodFloatMove::SetFightFishState()
//{
//	m_floatState = fightFish;
//}

//void RodFloatMove::SetScalar_multiply_in_first_velocity_vector(float scalar_multiply_in_first_velocity_vector)
//{
//	m_scalar_multiply_in_first_velocity_vector = scalar_multiply_in_first_velocity_vector;
//}

void RodFloatMove::SetPosition(Vector3 position)
{

	m_rodFloatPosition = position;
}

void RodFloatMove::SetPosition()
{
	m_playFishing = FindGO<PlayFishing>("playFishing");

	if (m_playFishing->m_playFishingStatus != cast/*, m_playFishing->m_playFishingStatus != wait_castGauge*/) {
		Float();
		//�|�W�V�����𔽉f����B
		m_rodFloatPosition = /*m_floating*/m_sumPosition + Vector3{ 0.0f,0.0f, m_playFishing->m_current_float_range_max_range_rate * m_limit_range_with_ship }+m_floating;
	}
	m_sumPosition = { 0.0f,0.0f,0.0f };
}

void RodFloatMove::SetSumPosition(Vector3 positon)
{
	m_sumPosition = positon;
}

//void RodFloatMove::SetCurrent_range_and_max_range_rate(float current_range_and_max_range_rate)
//{
//	
//	m_playFishing = FindGO<PlayFishing>("playFishing");
//	if (m_playFishing->m_playFishingStatus != cast) {
//		Float();
//		//�|�W�V�����𔽉f����B
//		m_rodFloatPosition = m_floating + Vector3{ 0.0f,0.0f, m_playFishing->m_current_float_range_max_range_rate * m_limit_range_with_ship };
//	}
//}

//void RodFloatMove::FightFish()
//{
//	Float();
//	m_sceneFightFish = FindGO<SceneFightFish>("sceneFightFish");
//	m_range_with_fish.z = m_sceneFightFish->m_range_with_fish * m_limit_range_with_fish;
//	m_rodFloatPosition = m_range_with_fish + m_floating;
//}

void RodFloatMove::Render(RenderContext& rc)
{
	m_rodFloatModel.Draw(rc);
}


//bool RodFloatMove::IsCastEnd()
//{
//	return m_cast_end;
//}
