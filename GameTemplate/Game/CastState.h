#pragma once
#include "PlayFishingStateBase.h"

class RodFloatMove;
class PlayFishing;
class CastState :public PlayFishingStateBase
{
public:

	CastState();
	~CastState();

	void Update();
	void Cast();

	float t;
	Vector3 g{ 0.0f,-30.0f,0.0f };//重力。
	Vector3 m_float_initPos{ 0.0f,500.0f,10.0f };
	Vector3 m_rodFloatPosition = m_float_initPos;
	float water_surface_position_y = 0;//うみのy軸での場所。
	float m_castStrength;//キャストの強さ（ウキのとび具合が変わる）
	float first_velocity_vector_z = 2;//初速ベクトルｚの値（ｙとｚの比率）。
	Vector3 first_velocity_vector{ 0.0f,1.0f,first_velocity_vector_z };//初速ベクトル（ｙは必ず1にしておく）。
	
	RodFloatMove* m_rodFloatMove;
	PlayFishing* m_playFishing;
};

