#include "stdafx.h"
#include "TensionGauge.h"
#include "GetRotation.h"
#include"PlayFishing.h"
#include"FishingRodHP.h"
#include"RodFloatMove.h";
#include "SceneFightFish.h"

#include <random>


TensionGauge::TensionGauge()
{
	srand(time(nullptr));
	//m_tensionGaugeInside.Init("Assets/modelData/tensionGauge.DDS", 500, 100);
	m_tensionGaugeInside.Init("Assets/modelData/new_sea_gauge.DDS", 100, 700);
	m_tensionGaugeInside.SetPivot(Vector2(0.5f, 0.5f));
	m_tensionGaugeInside.SetPosition(Vector3(650.0f,0.0f, 0.0f));
	m_tensionGaugeInside.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_tensionGaugeInside.Update();

	m_tensionGaugeOutside.Init("Assets/modelData/tensionGaugeFrame.DDS", 100, 500);
	m_tensionGaugeOutside.SetPivot(Vector2(0.0f, 0.5f));
	m_tensionGaugeOutside.SetPosition(Vector3(-700.0f, -200.0f, 0.0f));
	m_tensionGaugeOutside.SetScale(Vector3{ 2.0f, 1.0f, 1.0f });
	m_tensionGaugeOutside.Update();

	m_signs_of_Fish.Init("Assets/modelData/new_signs_of_fish.DDS", 50, 50);
	m_signs_of_Fish.SetPivot(Vector2(0.5f, 0.0f));
	m_signs_of_Fish.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
}

TensionGauge::~TensionGauge()
{

}

void TensionGauge::Update()
{
	m_sceneFightFish=FindGO<SceneFightFish>("sceneFightFish");
	/*Set_signs_of_Fish_UI();*/

	/*SetFishUI_Position();*/
}

void TensionGauge::RightAndLeftManagement()
{

}

void TensionGauge::SetFishUI_Position(float position)
{
	m_signs_of_Fish_UI_Position= position/*m_sceneFightFish->m_range_with_fish*/;
	m_signs_of_Fish.SetPosition(Vector3(650.0f, m_bar_length * m_signs_of_Fish_UI_Position+ m_barBottom, 0.0f));
	m_signs_of_Fish.Update();

}

void TensionGauge::Set_signs_of_Fish_UI()
{
	if (m_sceneFightFish->m_previous_is_fish_suited_for_upper_side != m_sceneFightFish->is_fish_suited_for_upper_side) {//前のフレームと状態が違う時だけ。
		switch (m_sceneFightFish->m_fishState)
		{
		case normal:
			switch (m_sceneFightFish->is_fish_suited_for_upper_side)
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
			switch (m_sceneFightFish->is_fish_suited_for_upper_side)
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
			switch (m_sceneFightFish->is_fish_suited_for_upper_side)
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
			switch (m_sceneFightFish->is_fish_suited_for_upper_side)
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
	m_sceneFightFish->m_previous_is_fish_suited_for_upper_side = m_sceneFightFish->is_fish_suited_for_upper_side;
}

void TensionGauge::Render(RenderContext& rc)
{
	m_tensionGaugeInside.Draw(rc);
	m_tensionGaugeOutside.Draw(rc);
	m_signs_of_Fish.Draw(rc);
}
