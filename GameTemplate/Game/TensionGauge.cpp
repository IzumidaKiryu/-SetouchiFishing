#include "stdafx.h"
#include "TensionGauge.h"
#include "GetRotation.h"
#include"PlayFishing.h"
#include"FishingRodHP.h"
#include"RodFloatMove.h";
#include "SceneFightFish.h"
#include "FightFishState.h"
#include "FishDetectionRadius.h"
#include <numbers>
#include <random>


namespace {
	static const float TENSION_GAUGE_INSIDE_WIDE = 100.0f;
	static const float TENSION_GAUGE_INSIDE_HEIGHT = 700.0f;
	static const float TENSION_GAUGE_OUTSIDE_WIDE = 100.0f;
	static const float TENSION_GAUGE_OUTSIDE_HEIGHT = 500.0f;

}

TensionGauge::TensionGauge() = default;

TensionGauge::~TensionGauge() = default;

bool TensionGauge::Init()
{
	srand(time(nullptr));
	//１８０度回すための変数を初期化。
	m_upward.SetRotationDegZ(0.0);
	m_downward.SetRotationDegZ(180);

	m_tensionGaugeInside.Init("Assets/modelData/new_sea_gauge.DDS", TENSION_GAUGE_INSIDE_WIDE, TENSION_GAUGE_INSIDE_HEIGHT);
	//m_tensionGaugeInside.SetPivot(Vector2(0.5f, 0.5f));
	m_tensionGaugeInside.SetPosition(Vector3(650.0f, 0.0f, 0.0f));
	m_tensionGaugeInside.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_tensionGaugeInside.Update();

	m_tensionGaugeOutside.Init("Assets/modelData/tensionGaugeFrame.DDS", TENSION_GAUGE_OUTSIDE_WIDE, TENSION_GAUGE_OUTSIDE_HEIGHT);
	m_tensionGaugeOutside.SetPivot(Vector2(0.0f, 0.5f));
	m_tensionGaugeOutside.SetPosition(Vector3(-700.0f, -200.0f, 0.0f));
	m_tensionGaugeOutside.SetScale(Vector3{ 2.0f, 1.0f, 1.0f });
	m_tensionGaugeOutside.Update();

	m_signsOfFish.Init("Assets/modelData/FishShadow/new_signs_of_fish.DDS", 50, 80);
	m_signsOfFish.SetPivot(Vector2(0.5f, 0.8f));
	m_signsOfFish.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });

	m_signsOfFishFlappingFins[0];
	m_signsOfFishFlappingFins[0].Init("Assets/modelData/FishShadow/fish_FinFlap_a.DDS", 50, 80);
	m_signsOfFishFlappingFins[0].SetPivot(Vector2(0.5f, 0.8f));

	m_signsOfFishFlappingFins[1];
	m_signsOfFishFlappingFins[1].Init("Assets/modelData/FishShadow/fish_FinFlap_b.DDS", 50, 80);
	m_signsOfFishFlappingFins[1].SetPivot(Vector2(0.5f, 0.8f));



	m_rodFloatUI.Init("Assets/modelData/rod_float.DDS", 50, 50);
	//m_rodFloatUI.SetPivot(Vector2(0.5f, 0.5f));
	m_rodFloatUI.SetPosition(Vector3(650.0f, 0.0f, 0.0f));
	m_rodFloatUI.SetScale(m_baseSignsOfFishUiSize);
	m_rodFloatUI.Update();

	m_shipUI.Init("Assets/modelData/shipUI.DDS", 100, 50);
	//m_shipUI.SetPivot(Vector2(0.5f, 0.5f));
	m_shipUI.SetPosition(m_shipUIPos);
	m_shipUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f }*2.5f);
	m_shipUI.Update();

	

	return true;
}

bool TensionGauge::Start()
{
	FindGOGameObject();
	return true;
}

void TensionGauge::Update()
{
	//if (m_fightFishState != nullptr) {
	//	Set_signs_of_Fish_UI();
	//}

	/*SetFishUI_Position();*/
	SetFloatScale();
	SwayShipUIByWaves();
	/*SetFishUI_Position();*/
	if (m_isFinFlapping) {
		FishUIFinFlap();
	}
}

void TensionGauge::FindGOGameObject()
{
	m_fightFishState = FindGO<FightFishState>("fightFishState");

	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");

	m_playFishing = FindGO<PlayFishing>("playFishing");
}


void TensionGauge::RightAndLeftManagement()
{

}

void TensionGauge::SetFishUIPosition(float current_fish_range_and_max_range_rate)
{
	m_fishUIPos = Vector3(650.0f, m_bar_length * current_fish_range_and_max_range_rate + m_barBottom, 0.0f);
	m_signsOfFish.SetPosition(m_fishUIPos);
	m_signsOfFish.Update();
}
void TensionGauge::SetFloatUIPosition(float current_float_range_max_range_rate)
{
	m_rodFloatUI.SetPosition(Vector3(650.0f, m_bar_length * current_float_range_max_range_rate + m_barBottom, 0.0f));
	m_rodFloatUI.Update();
}
/// <summary>
/// 大きさを変更。
/// </summary>
void TensionGauge::SetFloatScale()
{

	//時間があれば影も合わせたい。
	if (m_rodFloatMove != nullptr) {//ウキが作成されていない場合は行わない。
		m_rodFloatUI.SetScale(Vector3::One*(1 + (m_rodFloatMove->m_position.y / 300)));
	}
}
/// <summary>
/// 魚の個体値に基づいて魚のスケールを設定
/// </summary>
/// <param name="scale"></param>
void TensionGauge::SetFishUIScaleByIndividualFactor(float scale)
{
	m_signsOfFish.SetScale(m_baseSignsOfFishUiSize*scale);
}

void TensionGauge::SwayShipUIByWaves()
{
	m_shipFloating_t += 0.01f; // 波の揺れの時間を進める。0.01fは調整可能な値。
	m_shipUI.SetScale(m_shipUIScale *(1+sin(m_shipFloating_t*2)* 0.05f)); // スケールを調整
	m_shipUI.Update();
}

Vector3 TensionGauge::GetFishUIPosition()
{

	return m_fishUIPos;
}

void TensionGauge::FindGOFishDetectionRadius()
{
	m_fishDetectionRadius = FindGO<FishDetectionRadius>("fishDetectionRadius");
}

void TensionGauge::FindGORodFloatMove()
{
	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
}

void TensionGauge::FishUIFinFlap()
{
	m_flapElapsedTime ++;

	if (m_flapElapsedTime > m_flapSwitchInterval) {
		m_flapElapsedTime = 0.0f;
		m_flapFrameType = (m_flapFrameType == FlapFrameType::A) ? FlapFrameType::B : FlapFrameType::A;
	}
	if (m_isFinFlapping) {//ヒレをパタパタさせる。
		m_signsOfFishFlappingFins[static_cast<int>(m_flapFrameType)].SetPosition(m_signsOfFish.GetPosition());
	}
	m_signsOfFishFlappingFins[static_cast<int>(m_flapFrameType)].Update();
}

void TensionGauge::SetIsFinFlapping(bool isFinFlapping)
{
	m_isFinFlapping = isFinFlapping;
}

//void TensionGauge::Set_signs_of_Fish_UI()
//{
//	if (m_fightFishState->m_previous_is_fish_suited_for_upper_side != m_fightFishState->is_fish_suited_for_upper_side) {//前のフレームと状態が違う時だけ。
//		switch (m_fightFishState->m_fishState)
//		{
//		case normal:
//			switch (m_fightFishState->is_fish_suited_for_upper_side)
//			{
//
//			case true:
//				m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_Facing_left.DDS", 50, 50);
//				break;
//				
//			case false:
//				/*m_signs_of_Fish.SetRotation();*/
//				m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_Facing_right.DDS", 50, 50);
//				break;
//
//			default:
//				break;
//			}
//			break;
//		case announce:
//			switch (m_fightFishState->is_fish_suited_for_upper_side)
//			{
//
//			case true:
//				m_signs_of_Fish.Init("Assets/modelData/announce_state_fish_left.DDS", 50, 100);
//				break;
//
//			case false:
//				m_signs_of_Fish.Init("Assets/modelData/announce_state_fish_right.DDS", 50, 100);
//				break;
//
//			default:
//				break;
//			}
//			break;
//		case angry:
//			switch (m_fightFishState->is_fish_suited_for_upper_side)
//			{
//
//			case true:
//				m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_angry_state_left.DDS", 50, 50);
//				break;
//
//			case false:
//				m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_angry_state_right.DDS", 50, 50);
//				break;
//
//			default:
//				break;
//			}
//			break;
//		case exhausted:
//			switch (m_fightFishState->is_fish_suited_for_upper_side)
//			{
//
//			case true:
//				m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_Facing_left.DDS", 50, 50);
//				break;
//
//			case false:
//				m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_Facing_right.DDS", 50, 50);
//				break;
//
//			default:
//				break;
//			}
//			break;
//		default:
//			break;
//		}
//	}
//	m_signs_of_Fish.Update();
//	m_fightFishState->m_previous_is_fish_suited_for_upper_side = m_fightFishState->is_fish_suited_for_upper_side;
//}
void TensionGauge::SetSignsOfFishUI()
{
	if (m_fightFishState->m_previous_fishFacing != m_fightFishState->m_fishFacing) {//前のフレームと状態が違う時だけ。
		switch (m_fightFishState->m_fishState)
		{
		case normal:
			switch (m_fightFishState->m_fishFacing)
			{

			case Upward:
				m_signsOfFish.Init("Assets/modelData/signs_of_fish_Facing_left.DDS", 50, 50);
				break;

			case Downward:
				/*m_signs_of_Fish.SetRotation();*/
				m_signsOfFish.Init("Assets/modelData/signs_of_fish_Facing_right.DDS", 50, 50);
				break;

			default:
				break;
			}
			break;
		case announce:
			switch (m_fightFishState->m_fishFacing)
			{

			case Upward:
				m_signsOfFish.Init("Assets/modelData/announce_state_fish_left.DDS", 50, 100);
				break;

			case Downward:
				m_signsOfFish.Init("Assets/modelData/announce_state_fish_right.DDS", 50, 100);
				break;

			default:
				break;
			}
			break;
		case angry:
			switch (m_fightFishState->m_fishFacing)
			{

			case Upward:
				m_signsOfFish.Init("Assets/modelData/signs_of_fish_angry_state_left.DDS", 50, 50);
				break;

			case Downward:
				m_signsOfFish.Init("Assets/modelData/signs_of_fish_angry_state_right.DDS", 50, 50);
				break;

			default:
				break;
			}
			break;
		case exhausted:
			switch (m_fightFishState->m_fishFacing)
			{

			case Upward:
				m_signsOfFish.Init("Assets/modelData/signs_of_fish_Facing_left.DDS", 50, 50);
				break;

			case Downward:
				m_signsOfFish.Init("Assets/modelData/signs_of_fish_Facing_right.DDS", 50, 50);
				break;

			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	m_signsOfFish.Update();
	m_fightFishState->m_previous_fishFacing = m_fightFishState->m_fishFacing;
}

void TensionGauge::SetUpwardFishUI()
{
	m_signsOfFish.SetRotation(m_upward);
	m_signsOfFish.Update();
	//シーンファイトフィッシュの時はヒレをパタパタさせる。
	if (m_playFishing->GetPlayFishingStatus() == sceneFightFish) {
		m_isFinFlapping = true; //上向きの魚影はひれをバタバタさせる。
	}
}

void TensionGauge::SetDownwardFishUI()
{
	m_signsOfFish.SetRotation(m_downward);
	m_signsOfFish.Update();

		m_isFinFlapping = false;//下向きの魚影はヒレをパタパタさせない。
}


void TensionGauge::Render(RenderContext& rc)
{


	m_tensionGaugeInside.Draw(rc);
	if (m_playFishing->m_playFishingStatus < PlayFishingStatus::wait_for_fish) {
		m_fishDetectionRadius->GetUI().Draw(rc);
	}

	m_tensionGaugeOutside.Draw(rc);

	if (m_isFinFlapping) {
		m_signsOfFishFlappingFins[static_cast<int>(m_flapFrameType)].Draw(rc);

	}
	else {
		m_signsOfFish.Draw(rc);

	}
	m_shipUI.Draw(rc);

	if (m_playFishing->m_playFishingStatus >= PlayFishingStatus::cast) {

			m_rodFloatUI.Draw(rc);

	}

	if (m_rodFloatMove != nullptr) {//ウキが作られていなに時は表示しない。
	}



}
