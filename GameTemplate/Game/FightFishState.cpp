#include "stdafx.h"
#include "FightFishState.h"
#include "TensionGauge.h"
#include "GetRotation.h"
#include"PlayFishing.h"
#include"FishingRodHP.h"
#include"RodFloatMove.h"
#include"GameCamera.h"
#include"PositionSelection.h"
#include"FishingRodHP.h"
#include"BuffManager.h"
#include <random>


FightFishState::FightFishState()
{
	srand(time(nullptr));
}

FightFishState::~FightFishState()
{
	DeleteGO(m_tensionGauge);
	DeleteGO(m_fishingRodHP);
	DeleteGO(m_rodFloatMove);
	m_fishingRodHP->SetIs_playFishingFinishedTrue();
}

bool FightFishState::OnInit()
{
	return true;
}

bool FightFishState::OnStart()
{
	m_fishingRodHP = NewGO<FishingRodHP>(0, "fishingRodHP");
	m_getRotation = NewGO<GetRotation>(0, "getRotation");
	m_buffManager = FindGO<BuffManager>("buffManager");
	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
	m_tensionGauge = FindGO<TensionGauge>("tensionGauge");
	m_playFishing = FindGO<PlayFishing>("playFishing");
	SetInitFishDirection();
	return true;
}



void FightFishState::Update()
{
	//カメラを管理する。
	CameraManagement();

	//フレーム数を更新。
	m_frameCount++;

	//魚の向く方向を決める。
	FishDirectionChange();

	//魚が逃げていく力を計算する。
	CalculateFishEscapePower();

	//魚を引っ張る力を計算する。
	CalculateCalculateFishPullForce();

	//魚の移動距離を計算する。
	CalculateFishDisplacement();

	SumFishModelPosition(m_fishDistanceRate);
	m_floatDistanceRate = m_fishDistanceRate;

	SumRodFloatPosition(m_floatDistanceRate);

	SetFish();
	SetFloat();

	CheckFailure();//成功したかどうか.
	CheckSuccess();//失敗したかどうか。
}

void FightFishState::CalculateDistanceMultiplier()
{
	//1倍から0.5倍の範囲で魚が逃げる力を小さくする。
	//遠ければ低い値、近ければ高い値になる。
	m_distanceMultiplier = 1 - ((m_fishDistanceRate) * 0.5);
}

void FightFishState::CalculateCalculateFishPullForce()
{
	float basePullForce = 0.0f;

	//コントローラーの回転量からベースの魚を引っ張る力を計算する。
	switch (m_fishFacing)
	{
		//回転量×体力率
	case Upward:
		basePullForce = GetRotationPower() * m_upwardBiasPullForce;
		break;
	case Downward:
		basePullForce = GetRotationPower() * m_downwardBiasPullForce;
		break;
	default:
		break;
	}
	//プレイヤーの体力を考慮する。
	m_forcePullFish -= (basePullForce * m_fishingRodHP->GetPowerMultiplier())*(1+m_buffManager->GetTotalPullStrengthBuff()/*バフを掛ける*/);
}


/// <summary>
/// 魚が逃げる力を計算するための関数。
/// </summary> 
void FightFishState::CalculateFishEscapePower()
{

	//距離による逃げる力を計算する。
	CalculateDistanceMultiplier();

	//魚が上を向いているときだけ逃げる力を加える。
	if (m_fishFacing == Upward) {
		m_fishEscapePower += m_fishData.escapeForce * m_distanceMultiplier;
	}

}


/// <summary>
/// 魚の移動距離を計算する。
/// </summary>
void FightFishState::CalculateFishDisplacement()
{

	float fishDisplacement;
	//逃げる力＋引く力。
	fishDisplacement=(m_forcePullFish)+m_fishEscapePower;


	m_fishDistanceRate = fishDisplacement;
}


/// <summary>
/// 魚の向く方向を変更するための関数。
/// </summary>
void FightFishState::FishDirectionChange()
{
	//if (m_isFightActive == true) {//キリュウ追加この行
		if (m_frameCount % 30 == 0) {//3０フレームに一回方向を変えるかどうか抽選をする。
			std::random_device rd;
			int randum = rd() % 100;
			//if (randum == 0)//ゼロが出たら向く方向を変える。
			//{
			switch (m_fishFacing)
			{

			case Upward:
				if (randum < m_fishData.downwardBias) {
					SetFishDownward();
				}
				break;

			case Downward:
				if (randum < m_fishData.upwardBias) {
					SetFishUpward();
					m_tensionGauge->SetIsFinFlapping(true);//UIの魚のヒレを動かす。
				}
				break;

			default:
				break;
				/*}*/
				m_fishChange_in_DirectionTimes++;//方向転換した数を数える。
			}
		}
}

void FightFishState::SetInitFishDirection()
{
		std::random_device rd;
		int randum = rd() % 2;

		switch (randum)
		{

		case 0:
				SetFishDownward();
			break;

		case 1:
				SetFishUpward();
			break;

		default:
			break;
			m_fishChange_in_DirectionTimes++;//方向転換した数を数える。
		}
}

/// <summary>
/// 失敗
/// </summary>
void FightFishState::CheckFailure()
{
	if (GetCurrentFishRangeAndMaxRangeRate() >= 1) {//上端まで行ったら。
		/*m_playFishing = FindGO<PlayFishing>("playFishing");
		m_playFishing->SetFailure();*/
		Failure();
	}
}

/// <summary>
/// 成功したとき。
/// </summary>
void FightFishState::CheckSuccess()
{
	if (GetCurrentFishRangeAndMaxRangeRate() <= 0) {//下端まで行ったら。

		Success();
	}
}

float FightFishState::GetRotationPower()
{
	return m_getRotation->nowFrameRotationQuantity;

}

/// <summary>
/// 魚が疲弊ステートのときの処理
/// </summary>
void FightFishState::ExhaustedState()
{
	m_angerState_frame_count++;
	if (m_reduce_Hp_when_angry == true) {//連続で二度以上処理されないようにする。
		m_forcePullFish -= m_getRotation->nowFrameRotationQuantity * 200 * 1.3 * 20;
		m_reduce_Hp_when_angry = false;
	}
}

void FightFishState::CameraManagement()
{
	m_cameraTarget = GetFishModelPos()+ Floating(ModelPattern)*5;
	SetCamera(m_cameraPos, m_cameraTarget);
}

FishFacing FightFishState::GetFishFacing()
{
	return m_fishFacing;
}