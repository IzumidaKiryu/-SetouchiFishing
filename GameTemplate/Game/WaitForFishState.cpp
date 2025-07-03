#include "stdafx.h"
#include "WaitForFishState.h"
#include "FishDetectionRadius.h"
#include "Player.h"
namespace 
{
	static const Vector3 CAMERA_ADD_POS = Vector3(200.0f, 200.0f, 200.0f);//カメラの最終座標に加算する値。
	static const Vector3 CAMERA_ADD_TARGET = Vector3(0.0f, 100.0f, 0.0f);//カメラの最終ターゲットに加算する値。
	static const float ADD_SUBTRACT_RATE = 0.001f;//魚の移動速度。
	static const float CAMERA_POS_TIME_RATE = 0.02f;//カメラの位置を変える時間のレート。
	static const float CAMERA_TARGET_TIME_RATE = 0.2f;//カメラのターゲットを変える時間のレート。
}

WaitForFishState::WaitForFishState() = default;

WaitForFishState::~WaitForFishState()
{
	m_player->EndCastAnimation();
}

bool WaitForFishState::OnInit()
{
	return true;
}


bool WaitForFishState::OnStart()
{
	m_initCameraPos = m_cameraPos;
	m_initCameraTarget = m_cameraTarget;
	m_fishDetectionRadius = FindGO<FishDetectionRadius>("fishDetectionRadius");
	m_endCameraPos = m_initFloatModelPos + CAMERA_ADD_POS;

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
	//ウキが魚の検知範囲に入っているかどうかを調べる。
	switch (m_goFishInWhich)
	{
	case WaitForFishState::up:
		if (m_sumCurrentFloatRangeMaxRangeRate < m_fishDetectionRadius->GetFishDetectionRadius() + m_fishDetectionRadius->GetPos())
		{
			m_isFloatDetected = true;
			m_fishDetectionRadius->DeletThis();
		}
		break;
	case WaitForFishState::down:
		if (m_sumCurrentFloatRangeMaxRangeRate > (-m_fishDetectionRadius->GetFishDetectionRadius() + m_fishDetectionRadius->GetPos())) {
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
	//上に進むか下に進むか決める。
	if (m_currentFishRangeAndMaxRangeRate > m_sumCurrentFloatRangeMaxRangeRate) {
		m_goFishInWhich = down;
	}

	if (m_currentFishRangeAndMaxRangeRate < m_sumCurrentFloatRangeMaxRangeRate) {
		m_goFishInWhich = up;
	}
}

void WaitForFishState::CameraManagement()
{
	m_endCameraTarget = GetFishModelPos() + ((GetFloatModelPos() - GetFishModelPos()) / 2) + CAMERA_ADD_TARGET;

	m_cameraPosTime += CAMERA_POS_TIME_RATE;
	m_cameraTargetTime += CAMERA_TARGET_TIME_RATE;

	if (m_cameraPosTime > 1) {
		m_cameraPosTime = 1;
	}
	if (m_cameraTargetTime > 1) {
		m_cameraTargetTime = 1;
	}
	m_cameraPos.Lerp(m_cameraPosTime, m_initCameraPos, m_endCameraPos);
	m_cameraTarget.Lerp(m_cameraTargetTime, m_initCameraTarget, m_endCameraTarget);

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


	switch (m_goFishInWhich)
	{
	case WaitForFishState::up:
		SetFishUpward();
		m_currentFishRangeAndMaxRangeRate += ADD_SUBTRACT_RATE;
		if (m_currentFishRangeAndMaxRangeRate - m_sumCurrentFloatRangeMaxRangeRate >= 0) {
			Success();
			return;
		}
		break;
	case WaitForFishState::down:
		SetFishDownward();
		m_currentFishRangeAndMaxRangeRate -= ADD_SUBTRACT_RATE;
		if (-m_sumCurrentFloatRangeMaxRangeRate + m_currentFishRangeAndMaxRangeRate <= 0) {
			Success();
			return;
		}
		break;
	default:
		break;
	}

	SumFishModelPosition(m_currentFishRangeAndMaxRangeRate);
	SetFish();
}
