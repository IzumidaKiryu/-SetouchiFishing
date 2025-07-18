#include "stdafx.h"
#include "CastState.h"
#include "PlayFishingStateBase.h"
#include "RodFloatMove.h"
#include "Player.h"
#include "PlayFishing.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace {

	// 初期カメラ位置オフセット
	static const Vector3 INITIAL_CAMERA_OFFSET = { 300.0f, 300.0f, -500.0f };

	// 自然対数の底 e
	static constexpr float EULER_E = 2.71828f;

	// 水面Y座標（海の高さ）
	static constexpr float WATER_SURFACE_Y = 0.0f;

	// 初速ベクトル z 成分
	static constexpr float FIRST_VELOCITY_Z = 2.0f;

	// 重力加速度
	static const Vector3 GRAVITY = { 0.0f,-30.0f,0.0f };

	// 初期浮き位置
	static const Vector3 INITIAL_FLOAT_POSITION = { 0.0f, 500.0f, 10.0f };

	// 初速ベクトル（y = 1.0f で固定）
	static const Vector3 FIRST_VELOCITY = { 0.0f, 1.0f, FIRST_VELOCITY_Z };

}

CastState::CastState() = default;

CastState::~CastState() = default;

void CastState::Update()
{
	CameraManagement();
	StateManager();
	Rotation();
	SetFloat();
	SumRodFloatPosition(m_floatOffset + m_float_initPos);

}

bool CastState::OnInit()
{
	m_float_initPos = INITIAL_FLOAT_POSITION;
	m_floatOffset = m_float_initPos;
	return true;
}

bool CastState::OnStart()
{
	m_initCameraPos = m_rodFloatMove->m_position + INITIAL_CAMERA_OFFSET;
	m_initCameraTarget = m_rodFloatMove->GetPosition();
	m_endCameraTarget = m_rodFloatMove->GetPosition();
	return true;
}

void CastState::CameraManagement()
{
	m_endCameraPos = m_rodFloatMove->m_position + INITIAL_CAMERA_OFFSET;

	m_cameraPosTime += 0.02;
	m_cameraTargetTime += 0.12;

	if (m_cameraPosTime >= 1.0f) {
		m_cameraPosTime = 1;
	}
	if (m_cameraTargetTime >= 1.0f) {
		m_cameraTargetTime = 1;
	}
	m_cameraPos.Lerp(m_cameraPosTime, m_initCameraPos, m_endCameraPos);

	m_cameraPos.Lerp(m_cameraPosTime, m_initCameraPos, m_endCameraPos);
	m_endCameraTarget = m_rodFloatMove->GetPosition();
	m_cameraTarget.Lerp(m_cameraTargetTime, m_initCameraTarget, m_endCameraTarget);

	SetCamera(m_cameraPos, m_cameraTarget);
}

void CastState::Cast()
{
	m_castTimer += 0.1f;
	m_playFishing = FindGO<PlayFishing>("playFishing");

	// ウキにかかる速度成分を計算（重力と初速の合成）
	m_zSlope = GRAVITY.z * m_castTimer + (100 * FIRST_VELOCITY.z * m_playFishing->m_castStrength) * 0.075f;
	m_ySlope = (GRAVITY.y * m_castTimer + (100 * FIRST_VELOCITY.y * m_playFishing->m_castStrength)) * 0.075f;

	forceVector = { 0.0f, m_ySlope, m_zSlope };
	m_floatOffset += forceVector;

	// ウキが水面より下に到達したら次のフェーズへ
	if (m_floatOffset.y + m_float_initPos.y <= WATER_SURFACE_Y) {
		m_castMoveState = riseUP;
	}
}

void CastState::Rotation()
{
	// ウキの回転角度を力の傾きから算出
	float floatAngle = GRAVITY.y * m_castTimer + (100 * FIRST_VELOCITY.y * m_playFishing->m_castStrength);
	floatAngle *= 0.01f;
	floatAngle *= -1.0f;
	floatAngle += M_PI;

	m_floatRotation.SetRotationX(floatAngle);
	m_rodFloatMove->SetRotation(m_floatRotation);
}

void CastState::RiseUP()
{
	m_castTimer += 0.1f;
	m_zSlope = GRAVITY.z * m_castTimer + (100 * FIRST_VELOCITY.z * m_playFishing->m_castStrength) * 0.075f;
	m_ySlope = (GRAVITY.y * m_castTimer + (100 * FIRST_VELOCITY.y * m_playFishing->m_castStrength)) * 0.075f;

	// 水面との高低差から水圧差を計算
	float sinkDistance = WATER_SURFACE_Y - m_floatOffset.y;
	m_hydraulicPressureDifference += sinkDistance * 0.002f;
	if (sinkDistance < 0.0f) m_hydraulicPressureDifference = 0.0f;

	// 水圧に応じて浮力を反映
	forceVector.z *= 1.0f / (m_hydraulicPressureDifference * 0.8f);
	forceVector.y += m_hydraulicPressureDifference;

	m_floatOffset += forceVector;

	// ウキが再度水面に到達したら次のフェーズへ
	if (m_floatOffset.y + m_float_initPos.y >= WATER_SURFACE_Y) {
		m_castMoveState = swing;
	}
}

void CastState::Swing()
{
	m_swingTimer += 0.08f;

	// 減衰するサイン波で上下運動を再現
	float swing = -(std::pow(EULER_E, -0.3f * m_swingTimer)) * std::abs(std::sin(m_swingTimer));
	m_floatOffset.y = (swing * 100.0f) - 500.0f;
	m_floatOffset += Floating();

	// 一定時間後にキャスト成功として処理を移行
	if (m_swingTimer >= 0.03f * 60.0f * 5.0f) {
		Success();
	}
}

void CastState::StateManager()
{
	switch (m_castMoveState)
	{
	case cast:
		Cast();
		break;
	case riseUP:
		RiseUP();
		break;
	case swing:
		Swing();
		break;
	default:
		break;
	}
}
