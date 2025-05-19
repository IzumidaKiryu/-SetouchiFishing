#pragma once
#include "PlayFishingStateBase.h"


class RodFloatMove;
class PlayFishing;
class TensionGauge;
class CastState :public PlayFishingStateBase
{
public:
	enum CastMoveState {
		cast,
		riseUP,
		swing
	};


	CastState();
	~CastState();

	/*using PlayFishingStateBase::Start;*/
	void Update();
	bool Start();
	void CameraManagement()override;
	void Cast();
	void Rotation();
	void RiseUP();//浮力の計算。
	void Swing();
	void StateManager();


	float t;
	float swing_t;
	float z_slope;
	float y_slope;
	const float e=2.71828;

	

	Vector3 g{ 0.0f,-30.0f,0.0f };//重力。
	Vector3 m_float_initPos{ 0.0f,500.0f,10.0f };
	Vector3 m_rodFloatPosition = m_float_initPos;
	Vector3 forceVector = { 0.0f,0.0f,0.0f };
	bool m_is_landing=false;
	float HydraulicPressureDifference = 0;//水圧差
	float water_surface_position_y = 0;//うみのy軸での場所。
	float m_castStrength;//キャストの強さ（ウキのとび具合が変わる）
	float first_velocity_vector_z = 2;//初速ベクトルｚの値（ｙとｚの比率）。
	Vector3 first_velocity_vector{ 0.0f,1.0f,first_velocity_vector_z };//初速ベクトル（ｙは必ず1にしておく）。

	RodFloatMove* m_rodFloatMove;
	PlayFishing* m_playFishing;
	Quaternion m_floatRotation;

	CastMoveState m_castMoveState;
	TensionGauge* m_tensionGauge;

};

