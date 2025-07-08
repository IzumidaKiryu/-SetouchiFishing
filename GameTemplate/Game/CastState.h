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

	/// <summary>
	/// オブジェクトがゲームに登場するタイミングで一度だけ実行される初期処理。
	/// 依存するオブジェクトの取得や初期位置設定を行う。
	/// </summary>
	bool OnStart();

	/// <summary>
	/// 初期化処理。モデルやパラメータの初期値設定などを行う。
	/// </summary>
	bool OnInit();

	/// <summary>
	/// カメラの位置や向きを更新し、プレイヤーやウキの動きに追従させる。
	/// </summary>
	void CameraManagement() override;

	/// <summary>
	/// キャスト動作を開始し、ウキの初速度や方向を決定する。
	/// </summary>
	void Cast();

	/// <summary>
	/// ウキの回転角度を計算し、自然な落下を表現する。
	/// </summary>
	void Rotation();

	/// <summary>
	/// ウキが水面に上昇するアニメーションを制御。
	/// </summary>
	void RiseUP();

	/// <summary>
	/// ウキの揺れ（スイング）を表現するアニメーション制御。
	/// </summary>
	void Swing();

	/// <summary>
	/// 現在の釣り状態（キャスト、ヒット、巻き上げなど）を管理し、必要に応じて遷移を行う。
	/// </summary>
	void StateManager();

private:
	// 時間管理用変数
	float m_castTimer = 0.0f;
	float m_swingTimer = 0.0f;

	// 傾き
	float m_zSlope = 0.0f;
	float m_ySlope = 0.0f;

	// 浮きの状態など
	Vector3 m_float_initPos= Vector3::Zero;
	Vector3 m_floatOffset=Vector3::Zero;
	Vector3 forceVector = Vector3::Zero;

	Quaternion m_floatRotation = Quaternion::Identity;

	//水圧差
	float m_hydraulicPressureDifference = 0.0f;

	CastMoveState m_castMoveState;

	// ゲージやプレイ情報
	TensionGauge* m_tensionGauge = nullptr;
};
