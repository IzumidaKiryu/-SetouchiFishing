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
	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");

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

	return true;
}



void FightFishState::Update()
{
	m_tensionGauge = FindGO<TensionGauge>("tensionGauge");

	m_playFishing = FindGO<PlayFishing>("playFishing");

	//カメラを管理する。
	CameraManagement();
	//フレーム数を計る
	FrameCount();
	//ステータス管理
	FishStateAdminister();

	//魚の向く方向を決める。
	FishDirectionChange();

	//魚が逃げていく力を計算する。
	CalculateFishEscapePower();

	//魚を引っ張る力を計算する。
	CalculateCalculateFishPullForce();

	//魚の移動距離を計算する。
	CalculateFishDisplacement();



	SumFishModelPosition(m_current_fish_range_and_max_range_rate);
	m_sum_current_float_range_max_range_rate = m_current_fish_range_and_max_range_rate;

	SumRodFloatPosition(m_sum_current_float_range_max_range_rate);

	SetFish();
	SetFloat();

	CheckFailure();//成功したかどうか.
	CheckSuccess();//失敗したかどうか。
	////キリュウ追加
	//if (m_fishingRodHP->m_Hp <= 0) {
	//	m_isFightActive = false;
	//}
	////ここまで
}



//bool SceneFightFish::Start()
//{
//	return false;
//}


void FightFishState::CalculateDistanceMultiplier()
{
	//1倍から0.5倍の範囲で魚が逃げる力を小さくする。
	//遠ければ低い値、近ければ高い値になる。
	m_distanceMultiplier = 1 - ((m_current_fish_range_and_max_range_rate) * 0.5);
}

void FightFishState::CalculateCalculateFishPullForce()
{
	//SetFishEscapePower();
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

	/*m_current_fish_range_and_max_range_rate = -(m_forcePullFish) + m_fishEscapePower;*/

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


	m_current_fish_range_and_max_range_rate = fishDisplacement;
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
				}
				break;

			default:
				break;
				/*}*/
				m_fishChange_in_DirectionTimes++;//方向転換した数を数える。
			}
		}
	//}
	////キリュウ追加
	//else {
	//	m_fishFacing = Upward;
	//	SetFishUpward();
	//}
	//ここまで
}

//void FightFishState::InitFishDirection()
//{
//	std::random_device rd;
//	int randum = rd() % 2;
//
//
//	switch (randum)
//	{
//
//	case 0:
//		SetFishDownward();
//		break;
//
//	case 1:
//		SetFishUpward();
//		break;
//
//	default:
//		break;
//	}
//	m_fishChange_in_DirectionTimes++;//方向転換した数を数える。
//}

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

void FightFishState::SetWhen_State_Announce_Should_State()
{
	//（5から10までのランダムな数）+（この処理をしている段階での魚が方向転換した回数）＝次のステートに進むときの今まで方向転換した回数
	std::random_device rd;

	//この数字23なら方向転換回数が23回目の時にステートをアナウンスにする。
	m_when_state_announce_should += 5;
	m_when_state_announce_should += (rd() % 6);
	m_when_state_announce_should += m_fishChange_in_DirectionTimes;//今まで方向転換した数を数える。

	m_fishState = normal;
}


void FightFishState::NormalState()
{
	if (m_when_state_announce_should == m_fishChange_in_DirectionTimes) {
		m_fishState = setWhen_State_Angry_or_exhausted_Should;
	}
}

void FightFishState::When_State_Angry_or_exhausted_Shoul()
{
	std::random_device rd;

	m_when_State_Angry_or_exhausted_Should = 0;
	m_when_State_Angry_or_exhausted_Should += 5;
	m_when_State_Angry_or_exhausted_Should += (rd() % 6);
	m_when_State_Angry_or_exhausted_Should += m_fishChange_in_DirectionTimes;//今まで方向転換した数を数える。

	m_fishState = announce;

}

void FightFishState::AnnounceState()
{
	if (m_when_State_Angry_or_exhausted_Should == m_fishChange_in_DirectionTimes) {
		m_fishState = change_Angry_or_exhausted;
	}
}

void FightFishState::Change_Angry_or_Exhausted_State()
{
	if (m_fishFacing == Upward) {//もし魚が左を向いていたら怒り状態にする。
		m_fishState = angry;
	}
	else {
		m_fishState = exhausted;
	}
}




void FightFishState::AngerState()
{
	m_angerState_frame_count++;
	if (m_angerState_frame_count <= 4 && m_getRotation->nowFrameRotationQuantity > 0) {//4フレーム間に入力があったら。

		if (m_reduce_Hp_when_angry == true) {//連続で二度以上処理されないようにする。
			m_fishingRodHP = FindGO<FishingRodHP>("fishingRodHP");
			m_fishingRodHP->m_Hp -= 100.0f;
			if (m_fishingRodHP->m_Hp <= 30) {
				m_fishingRodHP->m_Hp = 30;
			}
			m_reduce_Hp_when_angry = false;
		}
	}

	if (m_angerState_frame_count > 100)//100フレーム超えたら
	{
		m_angerState_frame_count = 0;
		m_fishState = setWhen_State_Announce_Should;
	}
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

/// <summary>
/// フィッシュステートを管理する
/// </summary>
void FightFishState::FishStateAdminister()
{
	switch (m_fishState)
	{

	case setWhen_State_Announce_Should:

		SetWhen_State_Announce_Should_State();

		break;


	case normal:

		NormalState();

		break;


	case setWhen_State_Angry_or_exhausted_Should:

		When_State_Angry_or_exhausted_Shoul();

		break;


	case announce:

		AnnounceState();

		break;
	case change_Angry_or_exhausted:

		Change_Angry_or_Exhausted_State();

		break;

	case angry:

		AngerState();

		break;

	case exhausted:

		break;

	default:
		break;
	}


}

void FightFishState::SetRodFloatModel()
{
}


void FightFishState::FrameCount()
{
	m_frameCount++;
}

void FightFishState::Set3DFishPosition()
{
	m_playFishing->m_current_fish_range_and_max_range_rate;
}


void FightFishState::CameraManagement()
{
	//m_cameraPos = GetPlayerPos() + Vector3{ 0.0f,100.0f,100.0f } + Floating();
	m_cameraTarget = GetFishModelPos()+ Floating(ModelPattern)*5;
	SetCamera(m_cameraPos, m_cameraTarget);
}

FishFacing FightFishState::GetFishFacing()
{
	return m_fishFacing;
}



//void TensionGauge::AnnounceChangeFishState()
//{
//
//}
