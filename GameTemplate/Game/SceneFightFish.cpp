#include "stdafx.h"
#include "SceneFightFish.h"
#include "TensionGauge.h"
#include "GetRotation.h"
#include"PlayFishing.h"
#include"FishingRodHP.h"
#include"RodFloatMove.h"
#include"TensionGauge.h"
#include"GameCamera.h"
#include"PositionSelection.h"
#include"FishingRodHP.h"
#include <random>



SceneFightFish::SceneFightFish()
{
	srand(time(nullptr));
	//m_tensionGaugeInside.Init("Assets/modelData/tensionGauge.DDS", 500, 100);
	/*m_tensionGauge = NewGO<TensionGauge>(0, "tensionGauge");*/
	m_fishingRodHP=NewGO<FishingRodHP>(0,"fishingRodHP");
	m_getRotation = NewGO<GetRotation>(0, "getRotation");
	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
	m_playFishing = FindGO<PlayFishing>("playFishing");
	m_initRangeRate += m_playFishing->m_current_float_range_max_range_rate;

}

SceneFightFish::~SceneFightFish()
{
	DeleteGO(m_tensionGauge);
	DeleteGO(m_fishingRodHP);

	m_fishingRodHP->SetIs_playFishingFinishedTrue();
}

void SceneFightFish::Update()
{
	m_tensionGauge= FindGO<TensionGauge>("tensionGauge");

	m_playFishing = FindGO<PlayFishing>("playFishing");

	//フレーム数を計る
	FrameCount();
	//ステータス管理
	FishStateAdminister();

	//魚の向く方向を決める。
	FishDirectionChange();

	//魚が逃げていく力を計算する。
	SetFishEscapePower();

	//魚影の位置を決める。
	SetSigns_of_Fish_Position();

	SetRangeRate();
	

	failure();//成功したかどうか.
	success();//失敗したかどうか。

	SetCamera();
	m_playFishing->m_current_float_range_max_range_rate = m_playFishing->m_current_fish_range_and_max_range_rate;
	m_playFishing->m_current_fish_range_and_max_range_rate = m_playFishing->m_current_float_range_max_range_rate;
	//m_tensionGauge->SetFishUI_Position(m_playFishing->m_current_fish_range_and_max_range_rate);
	// 
	// 
	// 
	//m_playFishing->SetFailure();
}

//bool SceneFightFish::Start()
//{
//	return false;
//}

void SceneFightFish::RightAndLeftManagement()
{

}

void SceneFightFish::SetSigns_of_Fish_Position()
{
	//SetFishEscapePower();
	if (is_fish_suited_for_upper_side == true) {//魚が上を向いているときにも引き寄せる力を加える。(上を向いているときにも少しは下に引っ張れるようにするため)。
		m_forcePullFish += m_getRotation->nowFrameRotationQuantity/* * 200*/ * 1.3 *0.05;
	}
	else {
		m_forcePullFish += m_getRotation->nowFrameRotationQuantity /** 200*/*0.1;
	}

	m_playFishing->m_current_fish_range_and_max_range_rate =-m_forcePullFish + m_fishEscapePower+ m_initRangeRate;
	//m_signs_of_Fish.SetPosition(Vector3(m_signs_of_Fish_2D_Position, -250.0f, 0.0f));
	//m_signs_of_Fish.Update();
}

void SceneFightFish::SetFishEscapePower()
{
	if (is_fish_suited_for_upper_side == true) {
		m_fishEscapePower += 0.002;
	}

}

void SceneFightFish::SetFishDirection()
{


}

/// <summary>
/// 魚の向く方向を変更するための関数。
/// </summary>
void SceneFightFish::FishDirectionChange()
{
	if (m_frameCount % 10 == 0) {//1０フレームに一回方向を変えるかどうか抽選をする。
		std::random_device rd;
		int randum = rd() % 2;
		if (randum == 0)//ゼロが出たら向く方向を変える。
		{
			switch (is_fish_suited_for_upper_side)
			{

			case true:
				is_fish_suited_for_upper_side = false;
				break;

			case false:
				is_fish_suited_for_upper_side = true;
				break;

			default:
				break;
			}
			m_fishChange_in_DirectionTimes++;//方向転換した数を数える。
		}
	}
}

/// <summary>
/// 失敗
/// </summary>
void SceneFightFish::failure()
{
	if (m_playFishing->m_current_fish_range_and_max_range_rate >= 1) {//上端まで行ったら。
		m_playFishing = FindGO<PlayFishing>("playFishing");
		m_playFishing->SetFailure();
	}
}

/// <summary>
/// 成功したとき。
/// </summary>
void SceneFightFish::success()
{
	if (m_playFishing->m_current_fish_range_and_max_range_rate <= 0) {//下端まで行ったら。
		m_playFishing = FindGO<PlayFishing>("playFishing");
		m_positionSelection = FindGO<PositionSelection>("positionSelection");
		m_fishingRodHP = FindGO<FishingRodHP>("fishingRodHP");
		m_positionSelection->m_stealPositionPoint += m_fishingRodHP->m_Hp;
		m_playFishing->SetSuccess();
	}
}

float SceneFightFish::GetRotationPower()
{
	return m_getRotation->nowFrameRotationQuantity;

}

void SceneFightFish::SetWhen_State_Announce_Should_State()
{
	//（5から10までのランダムな数）+（この処理をしている段階での魚が方向転換した回数）＝次のステートに進むときの今まで方向転換した回数
	std::random_device rd;

	//この数字23なら方向転換回数が23回目の時にステートをアナウンスにする。
	m_when_state_announce_should += 5;
	m_when_state_announce_should += (rd() % 6);
	m_when_state_announce_should += m_fishChange_in_DirectionTimes;//今まで方向転換した数を数える。

	m_fishState = normal;
}


void SceneFightFish::NormalState()
{
	if (m_when_state_announce_should == m_fishChange_in_DirectionTimes) {
		m_fishState = setWhen_State_Angry_or_exhausted_Should;
	}
}

void SceneFightFish::When_State_Angry_or_exhausted_Shoul()
{
	std::random_device rd;

	m_when_State_Angry_or_exhausted_Should = 0;
	m_when_State_Angry_or_exhausted_Should += 5;
	m_when_State_Angry_or_exhausted_Should += (rd() % 6);
	m_when_State_Angry_or_exhausted_Should += m_fishChange_in_DirectionTimes;//今まで方向転換した数を数える。

	m_fishState = announce;

}

void SceneFightFish::AnnounceState()
{
	if (m_when_State_Angry_or_exhausted_Should == m_fishChange_in_DirectionTimes) {
		m_fishState = change_Angry_or_exhausted;
	}
}

void SceneFightFish::Change_Angry_or_Exhausted_State()
{
	if (is_fish_suited_for_upper_side == true) {//もし魚が左を向いていたら怒り状態にする。
		m_fishState = angry;
	}
	else {
		m_fishState = exhausted;
	}
}




void SceneFightFish::AngerState()
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
void SceneFightFish::ExhaustedState()
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
void SceneFightFish::FishStateAdminister()
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

void SceneFightFish::SetRodFloatModel()
{
}

void SceneFightFish::SetCamera()
{
	m_gameCamera = FindGO<GameCamera>("gameCamera");
	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
	m_gameCamera->SetTarget(m_rodFloatMove->m_rodFloatPosition);
}

void SceneFightFish::FrameCount()
{
	m_frameCount++;
}

void SceneFightFish::Set3DFishPosition()
{
	m_playFishing->m_current_fish_range_and_max_range_rate;
}

void SceneFightFish::SetRangeRate()
{
	//m_range_rate = m_initRangeRate;
	//m_total_by_fish_advanced_distance+=m_this_frame_by_fish_advanced_distance;
	//m_range_rate += m_total_by_fish_advanced_distance;
}

//void TensionGauge::AnnounceChangeFishState()
//{
//
//}
