#include "stdafx.h"
#include "TensionGauge.h"
#include "GetRotation.h"
#include"PlayFishing.h"
#include"FishingRodHP.h"
#include <random>


TensionGauge::TensionGauge()
{
	srand(time(nullptr));
	//m_tensionGaugeInside.Init("Assets/modelData/tensionGauge.DDS", 500, 100);
	m_tensionGaugeInside.Init("Assets/modelData/Sea.DDS", 500, 100);
	m_tensionGaugeInside.SetPivot(Vector2(0.0f, 0.5f));
	m_tensionGaugeInside.SetPosition(Vector3(-500.0f, -200.0f, 0.0f));
	m_tensionGaugeInside.SetScale(Vector3{ 2.0f, 1.0f, 1.0f });
	m_tensionGaugeInside.Update();

	m_tensionGaugeOutside.Init("Assets/modelData/tensionGaugeFrame.DDS", 500, 100);
	m_tensionGaugeOutside.SetPivot(Vector2(0.0f, 0.5f));
	m_tensionGaugeOutside.SetPosition(Vector3(-700.0f, -200.0f, 0.0f));
	m_tensionGaugeOutside.SetScale(Vector3{ 2.0f, 1.0f, 1.0f });
	m_tensionGaugeOutside.Update();

	m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_Facing_left.DDS", 50, 50);
	m_signs_of_Fish.SetPivot(Vector2(0.5f, 0.0f));
	m_signs_of_Fish.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_getRotation = NewGO<GetRotation>(0, "getRotation");
}

TensionGauge::~TensionGauge()
{
	m_fishingRodHP = FindGO<FishingRodHP>("fishingRodHP");
	m_fishingRodHP->SetIs_playFishingFinishedTrue();

}

void TensionGauge::Update()
{

	FishStateAdminister();
	FishDirectionChange();
	SetFishEscapePower();
	SetSigns_of_Fish_Position();
	Set_signs_of_Fish_UI();
	failure();//成功したかどうか.
	success();//失敗したかどうか。
	//m_playFishing->SetFailure();
}

void TensionGauge::RightAndLeftManagement()
{

}

void TensionGauge::SetSigns_of_Fish_Position()
{
	//SetFishEscapePower();
	if (m_isFishDirectionisLeft == true) {//魚が左を向いているときはまく力を強くする。(左を向いているときにも少しは右に引っ張れるようにするため)。
		m_forcePullFish += m_getRotation->nowFrameRotationQuantity * 200 * 1.3;
	}
	else {
		m_forcePullFish += m_getRotation->nowFrameRotationQuantity * 200;
	}

	m_signs_of_Fish_Position = m_forcePullFish + m_fishEscapePower;
	m_signs_of_Fish.SetPosition(Vector3(m_signs_of_Fish_Position, -250.0f, 0.0f));
	m_signs_of_Fish.Update();
}

void TensionGauge::SetFishEscapePower()
{
	if (m_isFishDirectionisLeft == true) {
		m_fishEscapePower -= 2.0f;
	}

}

void TensionGauge::SetFishDirection()
{


}

/// <summary>
/// 魚の向く方向を変更するための関数。
/// </summary>
void TensionGauge::FishDirectionChange()
{
	std::random_device rd;
	int randum = rd() % 50;
	if (randum == 0)//ゼロが出たら向く方向を変える。
	{
		switch (m_isFishDirectionisLeft)
		{

		case true:
			m_isFishDirectionisLeft = false;
			break;

		case false:
			m_isFishDirectionisLeft = true;
			break;

		default:
			break;
		}
		m_fishChange_in_DirectionTimes++;//方向転換した数を数える。
	}
}

/// <summary>
/// 失敗
/// </summary>
void TensionGauge::failure()
{
	if (m_signs_of_Fish_Position <= m_gaugeLeftmost) {
		m_playFishing = FindGO<PlayFishing>("playFishing");
		m_playFishing->SetFailure();
	}
}

void TensionGauge::success()
{
	if (m_signs_of_Fish_Position >= m_gaugeRightmost) {
		m_playFishing = FindGO<PlayFishing>("playFishing");
		m_playFishing->SetSuccess();
	}
}

float TensionGauge::GetRotationPower()
{
	return m_getRotation->nowFrameRotationQuantity;

}

void TensionGauge::Set_signs_of_Fish_UI()
{
	if (m_previous_isFishDirectionisLeft != m_isFishDirectionisLeft) {//前のフレームと状態が違う時だけ。
		switch (m_fishState)
		{
		case normal:
			switch (m_isFishDirectionisLeft)
			{

			case true:
				m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_Facing_left.DDS", 50, 50);
				break;

			case false:
				m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_Facing_right.DDS", 50, 50);
				break;

			default:
				break;
			}
			break;
		case announce:
			switch (m_isFishDirectionisLeft)
			{

			case true:
				m_signs_of_Fish.Init("Assets/modelData/announce_state_fish_left.DDS", 50, 100);
				break;

			case false:
				m_signs_of_Fish.Init("Assets/modelData/announce_state_fish_right.DDS", 50, 100);
				break;

			default:
				break;
			}
			break;
		case angry:
			switch (m_isFishDirectionisLeft)
			{

			case true:
				m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_angry_state_left.DDS", 50, 50);
				break;

			case false:
				m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_angry_state_right.DDS", 50, 50);
				break;

			default:
				break;
			}
			break;
		case exhausted:
			switch (m_isFishDirectionisLeft)
			{

			case true:
				m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_Facing_left.DDS", 50, 50);
				break;

			case false:
				m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_Facing_right.DDS", 50, 50);
				break;

			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	m_signs_of_Fish.Update();
	m_previous_isFishDirectionisLeft = m_isFishDirectionisLeft;
}

void TensionGauge::SetWhen_State_Announce_Should_State()
{
	//（5から10までのランダムな数）+（この処理をしている段階での魚が方向転換した回数）＝次のステートに進むときの今まで方向転換した回数
	std::random_device rd;

	//この数字23なら方向転換回数が23回目の時にステートをアナウンスにする。
	m_when_state_announce_should += 5;
	m_when_state_announce_should += (rd() % 6);
	m_when_state_announce_should += m_fishChange_in_DirectionTimes;//今まで方向転換した数を数える。

	m_fishState = normal;
}


void TensionGauge::NormalState()
{
	if (m_when_state_announce_should == m_fishChange_in_DirectionTimes) {
		m_fishState = setWhen_State_Angry_or_exhausted_Should;
	}
}

void TensionGauge::When_State_Angry_or_exhausted_Shoul()
{
	std::random_device rd;

	m_when_State_Angry_or_exhausted_Should = 0;
	m_when_State_Angry_or_exhausted_Should += 5;
	m_when_State_Angry_or_exhausted_Should += (rd() % 6);
	m_when_State_Angry_or_exhausted_Should += m_fishChange_in_DirectionTimes;//今まで方向転換した数を数える。

	m_fishState = announce;

}

void TensionGauge::AnnounceState()
{
	if (m_when_State_Angry_or_exhausted_Should == m_fishChange_in_DirectionTimes) {
		m_fishState = change_Angry_or_exhausted;
	}
}

void TensionGauge::Change_Angry_or_Exhausted_State()
{
	if (m_isFishDirectionisLeft == true) {//もし魚が左を向いていたら怒り状態にする。
		m_fishState = angry;
	}
	else {
		m_fishState = exhausted;
	}
}




void TensionGauge::AngerState()
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

void TensionGauge::ExhaustedState()
{
	m_angerState_frame_count++;
	if (m_reduce_Hp_when_angry == true) {//連続で二度以上処理されないようにする。
		m_forcePullFish += m_getRotation->nowFrameRotationQuantity * 200 * 1.3 * 20;
		m_reduce_Hp_when_angry = false;
	}
}

/// <summary>
/// フィッシュステートを管理する
/// </summary>
void TensionGauge::FishStateAdminister()
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

//void TensionGauge::AnnounceChangeFishState()
//{
//
//}

void TensionGauge::Render(RenderContext& rc)
{
	m_tensionGaugeInside.Draw(rc);
	m_tensionGaugeOutside.Draw(rc);
	m_signs_of_Fish.Draw(rc);
}
