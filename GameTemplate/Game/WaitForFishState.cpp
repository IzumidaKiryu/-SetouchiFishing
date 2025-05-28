#include "stdafx.h"
#include "WaitForFishState.h"
#include "FishDetectionRadius.h"

WaitForFishState::WaitForFishState()
{
	
}

WaitForFishState::~WaitForFishState()
{
}

bool WaitForFishState::Start()
{
	PlayFishingStateBase::Start();

	m_initCameraPos = m_cameraPos;
	m_endCameraPos = m_init_floatModelPos + Vector3{ 200.0f,200.0f,200.0f };
	m_initCameraTarget = m_cameraTarget;

	SetGoFishInWhich();
	IsFloatInDetectionRange();

	if (m_isFloatDetected==false) {
		Failure();
	}
	

	return true;
}

//bool WaitForFishState::Start()
//{
//	return true;
//}

void WaitForFishState::IsFloatInDetectionRange()
{

	m_fishDetectionRadius = FindGO<FishDetectionRadius>("fishDetectionRadius");


	//ウキが魚の検知範囲に入っているかどうかを調べる。

	switch (m_go_fish_in_which)
	{
	case WaitForFishState::up:

		if (m_sum_current_float_range_max_range_rate < m_fishDetectionRadius->GetFishDetectionRadius() + m_fishDetectionRadius->GetPos())
		{
			m_isFloatDetected = true;
			m_fishDetectionRadius->DeletThis();
		}

		break;
	case WaitForFishState::down:
		if (m_sum_current_float_range_max_range_rate > (-m_fishDetectionRadius->GetFishDetectionRadius() + m_fishDetectionRadius->GetPos())) {
			m_isFloatDetected = true;
			m_fishDetectionRadius->DeletThis();
		}
		break;
	default:
		break;
	}
	
	

}

void WaitForFishState::SetGoFishInWhich()
{
	//上に進むか下に進むか決める。j
	if (m_current_fish_range_and_max_range_rate > m_sum_current_float_range_max_range_rate) {
		m_go_fish_in_which = down;
	}

	if (m_current_fish_range_and_max_range_rate < m_sum_current_float_range_max_range_rate) {
		m_go_fish_in_which = up;
	}
}

void WaitForFishState::CameraManagement()
{
	m_endCameraTarget = GetFishModelPos() + ((GetFloatModelPos() - GetFishModelPos()) / 2) + Vector3{0.0f,100.0f,0.0f};

	m_cameraPos_t += 0.02;
	m_cameraTarget_t += 0.2;

	if (m_cameraPos_t > 1) {
		m_cameraPos_t = 1;
	}
	if (m_cameraTarget_t > 1) {
		m_cameraTarget_t = 1;
	}
	m_cameraPos.Lerp(m_cameraPos_t, m_initCameraPos, m_endCameraPos);
	m_cameraTarget.Lerp(m_cameraTarget_t, m_initCameraTarget, m_endCameraTarget);

	SetCamera(m_cameraPos,m_cameraTarget);
}

void WaitForFishState::Update()
{

	//カメラを管理する。
	CameraManagement();



	if (m_isFloatDetected == true) {
		ComingFish();
	}

	SumRodFloatPosition(Floating());

	SetFloat();

}

void WaitForFishState::ComingFish()
{


	switch (m_go_fish_in_which)
	{
	case WaitForFishState::up:
		SetFishUpward();
		m_current_fish_range_and_max_range_rate += 0.001;
		if (m_current_fish_range_and_max_range_rate - m_sum_current_float_range_max_range_rate >= 0) {
			Success();
			return;
		}
		break;
	case WaitForFishState::down:
		SetFishDownward();
		m_current_fish_range_and_max_range_rate -= 0.001;
		if (-m_sum_current_float_range_max_range_rate + m_current_fish_range_and_max_range_rate <= 0) {
			Success();
			return;
		}
		break;
	default:
		break;
	}

	SumFishModelPosition(m_current_fish_range_and_max_range_rate);
	SetFish();
}
