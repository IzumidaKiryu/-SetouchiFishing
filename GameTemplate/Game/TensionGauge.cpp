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


TensionGauge::TensionGauge()
{

	


}

TensionGauge::~TensionGauge()
{

}

bool TensionGauge::Init()
{
	srand(time(nullptr));
	//１８０度回すための変数を初期化。
	m_upward.SetRotationDegZ(0.0);
	m_downward.SetRotationDegZ(180);

	m_tensionGaugeInside.Init("Assets/modelData/new_sea_gauge.DDS", 100, 700);
	m_tensionGaugeInside.SetPivot(Vector2(0.5f, 0.5f));
	m_tensionGaugeInside.SetPosition(Vector3(650.0f, 0.0f, 0.0f));
	m_tensionGaugeInside.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_tensionGaugeInside.Update();

	m_tensionGaugeOutside.Init("Assets/modelData/tensionGaugeFrame.DDS", 100, 500);
	m_tensionGaugeOutside.SetPivot(Vector2(0.0f, 0.5f));
	m_tensionGaugeOutside.SetPosition(Vector3(-700.0f, -200.0f, 0.0f));
	m_tensionGaugeOutside.SetScale(Vector3{ 2.0f, 1.0f, 1.0f });
	m_tensionGaugeOutside.Update();

	m_signs_of_Fish.Init("Assets/modelData/new_signs_of_fish.DDS", 50, 50);
	m_signs_of_Fish.SetPivot(Vector2(0.5f, 1.0f));
	m_signs_of_Fish.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });


	m_rodFloatUI.Init("Assets/modelData/rod_float.DDS", 50, 50);
	m_rodFloatUI.SetPivot(Vector2(0.5f, 0.5f));
	m_rodFloatUI.SetPosition(Vector3(650.0f, 0.0f, 0.0f));
	m_rodFloatUI.SetScale(m_baseSigns_of_FishUiSize);
	m_rodFloatUI.Update();

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
	/*SetFishUI_Position();*/
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

void TensionGauge::SetFishUI_Position(float current_fish_range_and_max_range_rate)
{
	m_fishUIPos = Vector3(650.0f, m_bar_length * current_fish_range_and_max_range_rate + m_barBottom, 0.0f);
	m_signs_of_Fish.SetPosition(m_fishUIPos);
	m_signs_of_Fish.Update();
}
void TensionGauge::SetFloatUI_Position(float current_float_range_max_range_rate)
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
		m_rodFloatUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f }*(1 + (m_rodFloatMove->m_position.y / 300)));
	}
}
/// <summary>
/// 魚の個体値に基づいて魚のスケールを設定
/// </summary>
/// <param name="scale"></param>
void TensionGauge::SetFishUIScaleByIndividualFactor(float scale)
{
	m_signs_of_Fish.SetScale(m_baseSigns_of_FishUiSize*scale);
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
void TensionGauge::Set_signs_of_Fish_UI()
{
	if (m_fightFishState->m_previous_fishFacing != m_fightFishState->m_fishFacing) {//前のフレームと状態が違う時だけ。
		switch (m_fightFishState->m_fishState)
		{
		case normal:
			switch (m_fightFishState->m_fishFacing)
			{

			case Upward:
				m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_Facing_left.DDS", 50, 50);
				break;

			case Downward:
				/*m_signs_of_Fish.SetRotation();*/
				m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_Facing_right.DDS", 50, 50);
				break;

			default:
				break;
			}
			break;
		case announce:
			switch (m_fightFishState->m_fishFacing)
			{

			case Upward:
				m_signs_of_Fish.Init("Assets/modelData/announce_state_fish_left.DDS", 50, 100);
				break;

			case Downward:
				m_signs_of_Fish.Init("Assets/modelData/announce_state_fish_right.DDS", 50, 100);
				break;

			default:
				break;
			}
			break;
		case angry:
			switch (m_fightFishState->m_fishFacing)
			{

			case Upward:
				m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_angry_state_left.DDS", 50, 50);
				break;

			case Downward:
				m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_angry_state_right.DDS", 50, 50);
				break;

			default:
				break;
			}
			break;
		case exhausted:
			switch (m_fightFishState->m_fishFacing)
			{

			case Upward:
				m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_Facing_left.DDS", 50, 50);
				break;

			case Downward:
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
	m_fightFishState->m_previous_fishFacing = m_fightFishState->m_fishFacing;
}

void TensionGauge::SetUpwardFishUI()
{
	m_signs_of_Fish.SetRotation(m_upward);
	m_signs_of_Fish.Update();
}

void TensionGauge::SetDownwardFishUI()
{
	m_signs_of_Fish.SetRotation(m_downward);
	m_signs_of_Fish.Update();
}


void TensionGauge::Render(RenderContext& rc)
{


	m_tensionGaugeInside.Draw(rc);
	if (m_playFishing->m_playFishingStatus < PlayFishingStatus::wait_for_fish) {
		m_fishDetectionRadius->GetUI().Draw(rc);
	}

	m_tensionGaugeOutside.Draw(rc);

	m_signs_of_Fish.Draw(rc);


	if (m_playFishing->m_playFishingStatus >= PlayFishingStatus::cast) {

			m_rodFloatUI.Draw(rc);

	}

	if (m_rodFloatMove != nullptr) {//ウキが作られていなに時は表示しない。
	}

}
