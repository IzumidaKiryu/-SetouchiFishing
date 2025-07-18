#include "stdafx.h"
#include "RodFloatMove.h"
#include "GameCamera.h"
#include"SceneFightFish.h";
#include"PlayFishing.h"
#include"TensionGauge.h"
#include <cmath>  // sqrt関数を使うために必要
#include <complex>   // 複素数ライブラリ

RodFloatMove::RodFloatMove()
{
}

RodFloatMove::~RodFloatMove()
{
}

bool RodFloatMove::Init()
{
	m_rodFloatModel.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_rodFloatModel.SetScale(Vector3{ 1.0f,1.0f,1.0f });
	m_rodFloatModel.Init("Assets/modelData/uki.tkm");
	m_rodFloatModel.Update();
	return true;
}


bool RodFloatMove::Start()
{
	m_playFishing = FindGO<PlayFishing>("playFishing");

	m_tensionGauge = FindGO<TensionGauge>("tensionGauge");
	m_tensionGauge->FindGORodFloatMove();

	return true;
}


void RodFloatMove::Update()
{
}

void RodFloatMove::ModelUpdate()
{
	m_rodFloatModel.SetPosition(m_position);
	m_rodFloatModel.Update();
}

void RodFloatMove::Float()
{
	t += 0.05;
	m_floating.y = (cos(t)) * 10;//上下に動かす
	m_floating.x = (cos(t * 0.7/*周期をずらす*/) * 10);//左右に動かす
	m_position = m_position + m_floating;
}

void RodFloatMove::SetPosition(Vector3 position)
{

	m_position = position;
	m_rodFloatModel.SetPosition(m_position);
	m_rodFloatModel.Update();
}

float RodFloatMove::ChangePosition_Z(float currentFloatDistanceRate)
{
	float positon_z = m_limit_range_with_ship * currentFloatDistanceRate;
	return positon_z;
}

float RodFloatMove::GetCurrentFloatDistanceRate(float position_x)
{
	float currentFloatDistanceRate;
	currentFloatDistanceRate = position_x / m_limit_range_with_ship;
	return currentFloatDistanceRate;
}

void RodFloatMove::SetRotation(Quaternion rot)
{
	m_rodFloatModel.SetRotation(rot);
	m_rodFloatModel.Update();
}

void RodFloatMove::SetPosition()
{
	if (m_playFishing->m_playFishingStatus != cast) {
		Float();
		//ポジションを反映する。
		m_position =m_sumPosition + Vector3{ 0.0f,0.0f, m_playFishing->m_floatDistanceRate * m_limit_range_with_ship } + m_floating;
	}
	m_sumPosition = Vector3::Zero;
}

void RodFloatMove::SetSumPosition(Vector3 positon)
{
	m_position += positon;
}

void RodFloatMove::Render(RenderContext& rc)
{
	m_rodFloatModel.Draw(rc);
}

Vector3 RodFloatMove::GetPosition()
{
	return m_position;
}

void RodFloatMove::DeleteThisClass()
{
	DeleteGO(this);	
}