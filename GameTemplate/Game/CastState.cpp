#include "stdafx.h"
#include "CastState.h"
#include "PlayFishingStateBase.h"
#include "RodFloatMove.h"
#include"Player.h"
#include"PlayFishing.h"
#define _USE_MATH_DEFINES
#include <math.h>

CastState::CastState()
{
	////ウキを作成。
	//m_rodFloatMove = NewGO<RodFloatMove>(0, "rodFloatMove");

	//initCameraPos = m_cameraPos;
	//endCameraPos = { 500.0f,500.0f,20.0f };
	//initCameraTarget = m_cameraTarget;
	//endCameraTarget = m_rodFloatMove->GetPosition();

}

CastState::~CastState()
{	
}

void CastState::Update()
{
	/*Cast();*/
		//カメラを管理する。
	CameraManagement();
	StateManager();
	Rotation();
	m_player = FindGO<Player>("player_Playfishing");
	SetFloat();
	SumRodFloatPosition(m_rodFloatPosition + m_float_initPos);
	


}

bool CastState::Start()
{
	//ウキを作成。
	m_rodFloatMove = NewGO<RodFloatMove>(0, "rodFloatMove");
	m_rodFloatMove->Init();

	PlayFishingStateBase::Start();


	m_initCameraPos = m_rodFloatMove->m_position + Vector3{ 300.0f,300.0f,-500.0f };;
	m_initCameraTarget = m_rodFloatMove->GetPosition();
	m_endCameraTarget = m_rodFloatMove->GetPosition();
	return true;
}

void CastState::CameraManagement()
{
	m_endCameraPos = m_rodFloatMove->m_position+Vector3{ 300.0f,300.0f,-500.0f };

	m_cameraPos_t += 0.02;
	m_cameraTarget_t += 0.12;

	if (m_cameraPos_t >= 1.0f) {
		m_cameraPos_t = 1;
	}
	if (m_cameraTarget_t >= 1.0f) {
		m_cameraTarget_t = 1;
	}
	m_cameraPos.Lerp(m_cameraPos_t, m_initCameraPos, m_endCameraPos);

	m_endCameraTarget = m_rodFloatMove->GetPosition();
	m_cameraTarget.Lerp(m_cameraTarget_t, m_initCameraTarget, m_endCameraTarget);



	SetCamera(
		m_cameraPos,
		m_cameraTarget
	);
}
//void CastState::Cast()
//{
//	t += 0.1;
//	m_playFishing = FindGO<PlayFishing>("playFishing");
//	//m_rodFloatPosition = m_float_initPos + (first_velocity_vector * 100 * m_playFishing->m_castStrength * t) + g * t * t * 1 / 2;
//	//SumRodFloatPosition(m_rodFloatPosition);
//	//SetFloat();
//	float z_slope= g.z * t + (100 * first_velocity_vector.z * m_playFishing->m_castStrength)*0.075f;
//	float y_slope= (g.y * t + (100 * first_velocity_vector.y * m_playFishing->m_castStrength))*0.075f;
//
//
//	forceVector = { 0.0f, y_slope, z_slope};
//
//	
//	/*SumRodFloatPosition(m_rodFloatPosition+ m_float_initPos);*/
//	if (m_is_landing == false) {
//		if (m_rodFloatPosition.y + m_float_initPos.y <= water_surface_position_y) {
//			/*Success();*/
//			m_is_landing = true;
//		}
//	}
//	if (m_is_landing) {
//		RiseUP();
//	}
//}
//
//void CastState::Rotation()
//{
//	//float high_position_when_t;//ウキが一番高いところにいるときのtの値。
//
//	////この式はウキをキャストしたときのウキの高さの関数（x=t（時間）,y=高さ)の導関数のyがの0になっている、
//	////時のtの値を求める式。
//	////つまり、元の関数の接線がｘ軸と並行になっている地点のｔの値を求めている。
//	//high_position_when_t = -(100 * first_velocity_vector.y * m_playFishing->m_castStrength) / g.y;
//
//	//float high_position_y;//今回の場合のウキの最大の高さ。（この高さはキャストゲージの入力によって変わる。）
//
//	//high_position_y = m_float_initPos.y + (first_velocity_vector.y * 100 * m_playFishing->m_castStrength * high_position_when_t) + g.y * high_position_when_t * high_position_when_t * 1 / 2;
//
//	float floatAngle;
//
//	//ウキの向きとキャストしたときのウキの高さの関数（x=t（時間）,y=高さ)の傾きが比例するようにする。
//
//	//導関数を使って傾きを求める。
//	floatAngle = g.y * t + (100 * first_velocity_vector.y * m_playFishing->m_castStrength);
//
//	m_floatRotation.SetRotationX(-floatAngle/100+M_PI);
//	m_rodFloatMove->SetRotation(m_floatRotation);
//
//}
//
///// <summary>
///// 浮き上がる。
///// </summary>
//void CastState::RiseUP()
//{
//	float sinkDistance;//どれだけ海に沈んでいるか。
//	sinkDistance = water_surface_position_y - m_rodFloatPosition.y;
//
//	
//	HydraulicPressureDifference += sinkDistance*0.002f;//水圧差は沈んでいる深さに比例する。
//	if (sinkDistance < 0) {
//		HydraulicPressureDifference = 0;
//	}
//	 
//	//水圧を考慮する。
//
//	forceVector.z *= 1/(HydraulicPressureDifference*0.8);
//	//forceVector.y *= 1/(HydraulicPressureDifference);
//	forceVector.y += HydraulicPressureDifference;
//	//if (forceVector.y > 0) {
//	//	forceVector.y =0;
//	//}
//	m_rodFloatPosition += forceVector;
//	if (m_rodFloatPosition.y<0) {
//		m_rodFloatPosition.y= -500;
//	}
//	if (m_rodFloatPosition.y + m_float_initPos.y >= water_surface_position_y) {
//		/*Success();*/
//		//m_rodFloatPosition.y-=200;
//	}
//
//}

void CastState::Cast()
{
	t += 0.1;
	m_playFishing = FindGO<PlayFishing>("playFishing");
	//m_rodFloatPosition = m_float_initPos + (first_velocity_vector * 100 * m_playFishing->m_castStrength * t) + g * t * t * 1 / 2;
	//SumRodFloatPosition(m_rodFloatPosition);
	//SetFloat();
	z_slope = g.z * t + (100 * first_velocity_vector.z * m_playFishing->m_castStrength) * 0.075f;
	y_slope = (g.y * t + (100 * first_velocity_vector.y * m_playFishing->m_castStrength)) * 0.075f;


	forceVector = { 0.0f, y_slope, z_slope };

	m_rodFloatPosition += forceVector;
	/*SumRodFloatPosition(m_rodFloatPosition+ m_float_initPos);*/
		if (m_rodFloatPosition.y + m_float_initPos.y <= water_surface_position_y) {
			/*Success();*/
			m_castMoveState = riseUP;
		}
}

void CastState::Rotation()
{
	//float high_position_when_t;//ウキが一番高いところにいるときのtの値。

	////この式はウキをキャストしたときのウキの高さの関数（x=t（時間）,y=高さ)の導関数のyがの0になっている、
	////時のtの値を求める式。
	////つまり、元の関数の接線がｘ軸と並行になっている地点のｔの値を求めている。
	//high_position_when_t = -(100 * first_velocity_vector.y * m_playFishing->m_castStrength) / g.y;

	//float high_position_y;//今回の場合のウキの最大の高さ。（この高さはキャストゲージの入力によって変わる。）

	//high_position_y = m_float_initPos.y + (first_velocity_vector.y * 100 * m_playFishing->m_castStrength * high_position_when_t) + g.y * high_position_when_t * high_position_when_t * 1 / 2;


	//float floatAngle;

	////ウキの向きとキャストしたときのウキの高さの関数（x=t（時間）,y=高さ)の傾きが比例するようにする。

	////導関数を使って傾きを求める。
	//Vector3 movement;//このフレームでの移動量{横方向(ｚ),高さ（ｙ）}
	//movement = { 0.0f,y_slope,z_slope};
	//movement.Normalize();//

	//float angle;//角度
	//angle=Dot(movement, Vector3{ 0.0f,0.0f,1.0f });//このフレームで動きた軌跡とz軸との傾き具合を計算する。
	////度数法の範囲にリマップする。

	//angle += 1;

	////外積を計算してベクトルが下を向ているか上を向ているか計算する。
	//if (0 < Cross(movement, Vector3{ 0.0f,0.0f,1.0f }).z) {
	//	//下を向いていたらマイナスを掛ける。
	//	angle *= -1;
	//}

	//angle += 2;//+2をして0～4の範囲にする。

	//angle *= 2*M_PI / 4;//範囲を0～360にする


	//m_floatRotation.SetRotationX(-angle/*-floatAngle / 100 + M_PI*/);
	//m_rodFloatMove->SetRotation(m_floatRotation);


	float floatAngle;

	//ウキの向きとキャストしたときのウキの高さの関数（x=t（時間）,y=高さ)の傾きが比例するようにする。

	//導関数を使って傾きを求める。
	floatAngle = g.y * t + (100 * first_velocity_vector.y * m_playFishing->m_castStrength);

	m_floatRotation.SetRotationX(-floatAngle / 100 + M_PI);
	m_rodFloatMove->SetRotation(m_floatRotation);

}

/// <summary>
/// 浮き上がる。
/// </summary>
void CastState::RiseUP()
{
	t += 0.1;
	z_slope = g.z * t + (100 * first_velocity_vector.z * m_playFishing->m_castStrength) * 0.075f;
	y_slope = (g.y * t + (100 * first_velocity_vector.y * m_playFishing->m_castStrength)) * 0.075f;



	float sinkDistance;//どれだけ海に沈んでいるか。
	sinkDistance = water_surface_position_y - m_rodFloatPosition.y;


	HydraulicPressureDifference += sinkDistance * 0.002f;//水圧差は沈んでいる深さに比例する。
	if (sinkDistance < 0) {
		HydraulicPressureDifference = 0;
	}

	//水圧を考慮する。

	forceVector.z *= 1 / (HydraulicPressureDifference * 0.8);
	forceVector.y += HydraulicPressureDifference;


	m_rodFloatPosition += forceVector;


	if (m_rodFloatPosition.y + m_float_initPos.y >= water_surface_position_y) {
		/*Success();*/
		//m_rodFloatPosition.y-=200;
		m_castMoveState = swing;
	}

}


void CastState::Swing()
{
	//float sinkDistance;//どれだけ海に沈んでいるか。
	//sinkDistance = water_surface_position_y - m_rodFloatPosition.y;


	//HydraulicPressureDifference += sinkDistance * 0.002f;//水圧差は沈んでいる深さに比例する。
	///*if (sinkDistance < 0) {
	//	HydraulicPressureDifference = 0;
	//}*/

	////水圧を考慮する。

	//forceVector.z *= 1 / (HydraulicPressureDifference * 0.8);


	//m_rodFloatPosition += forceVector;

	swing_t+=0.08;
	//float swing = ((sin(swing_t) / swing_t) -1) * 100.0f;
	
	float swing = -(std::pow(e, -0.3 * swing_t))* abs(sin(swing_t));
	m_rodFloatPosition.y = (swing*100)-500;
	m_rodFloatPosition += Floating();
	if (swing_t >= 0.03*60*5) {
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
