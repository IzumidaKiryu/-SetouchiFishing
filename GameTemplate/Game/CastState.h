#pragma once
#include "PlayFishingStateBase.h"

class RodFloatMove;
class PlayFishing;
class TensionGauge;

/// <summary>
/// キャスト状態を管理するステート。
/// </summary>
class CastState : public PlayFishingStateBase {
public:
	/// <summary>
	/// キャスト状態のフェーズ
	/// </summary>
	enum CastMoveState {
		cast,      ///< 投げ中
		riseUP,    ///< 浮き上がり中
		swing      ///< 揺れ中
	};

	CastState();
	~CastState();

	void Update();
	bool OnStart();
	bool OnInit();
	void CameraManagement() override;
	void Cast();
	void Rotation();
	void RiseUP();
	void Swing();
	void StateManager();

private :

private:
	// 時間管理用変数
	float t = 0.0f;
	float swing_t = 0.0f;

	// 傾き
	float z_slope = 0.0f;
	float y_slope = 0.0f;

	// 浮きの状態など
	Vector3 m_float_initPos= { 0.0f, 500.0f, 10.0f };
	Vector3 m_rodFloatPosition= { 0.0f, 500.0f, 10.0f };
	Vector3 forceVector = Vector3::Zero;

	Quaternion m_floatRotation = Quaternion::Identity;

	float HydraulicPressureDifference = 0.0f;

	CastMoveState m_castMoveState;

	// ゲージやプレイ情報
	TensionGauge* m_tensionGauge = nullptr;
};
