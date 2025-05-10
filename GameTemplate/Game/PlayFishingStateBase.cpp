#include "stdafx.h"
#include "PlayFishingStateBase.h"
#include "GameCamera.h"
#include"FishModel.h"
#include"RodFloatMove.h"
#include"PlayFishing.h"
#include "TensionGauge.h"
#include"Player.h"


PlayFishingStateBase::PlayFishingStateBase()
{
	SetFishData();

}

PlayFishingStateBase::~PlayFishingStateBase()
{
	if (m_rodFloatMove != nullptr) {
		m_sum_current_float_range_max_range_rate = GetCurrent_Float_Range_Max_Range_Rate();
	}

	m_playFishing = FindGO<PlayFishing>("playFishing");
	if (m_playFishing!=nullptr) {
		Pass_Current_Fish_Range_And_Max_Range_Rate();
		Pass_Current_Float_Range_And_Max_Range_Rate();
		Pass_FishModelPos();
		Pass_FloatModelPos();
	}

}

bool PlayFishingStateBase::Start()
{
	Set_Init_Current_Fish_Range_And_Max_Range_Rate();
	Set_Init_Current_Float_Range_And_Max_Range_Rate();
	Set_Init_FishModelPos();
	Set_Init_FloatModelPos();
	return true;
}

void PlayFishingStateBase::Update()
{

}

void PlayFishingStateBase::ChangeState()
{
	m_isChengeState = true;
}

bool PlayFishingStateBase::GetIsChengeState()
{
	return m_isChengeState;
}

void PlayFishingStateBase::SetSuccess()
{
	m_successful_or_Failure = success;
}

void PlayFishingStateBase::SetFailure()
{
	m_successful_or_Failure = failure;
}

Successful_or_Failure PlayFishingStateBase::GetSuccessful_or_Failure()
{
	return m_successful_or_Failure;
}

void PlayFishingStateBase::SetCamera(Vector3 position, Vector3 targete)
{
	m_gameCamera = FindGO<GameCamera>("PlayFishing_GameCamera");
	m_gameCamera->SetPosition(position);
	m_gameCamera->SetTarget(targete);
}

void PlayFishingStateBase::SumFishModelPosition(Vector3 position)
{
	m_sum_fishModelPos += position;
}

void PlayFishingStateBase::SumFishModelPosition(float current_fish_range_and_max_range_rate)
{
	m_fishModel = FindGO<FishModel>("fishModel");
	m_sum_fishModelPos += Vector3{ 0.0f,0.0f,m_fishModel->ChangePosition_Z(current_fish_range_and_max_range_rate) };
}

void PlayFishingStateBase::SumRodFloatPosition(Vector3 position)
{
	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
	m_sum_floatModelPos += position;
}

void PlayFishingStateBase::SumRodFloatPosition(float current_float_range_max_range_rate)
{
	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
	m_sum_floatModelPos += Vector3{ 0.0f,0.0f,m_rodFloatMove->ChangePosition_Z(current_float_range_max_range_rate) };
}

void PlayFishingStateBase::SetFishData()
{
	m_playFishing = FindGO<PlayFishing>("playFishing");
	m_fishData = m_playFishing->m_fishData;
}

void PlayFishingStateBase::SetFish()
{
	m_fishModel = FindGO<FishModel>("fishModel");
	//魚のモデルの場所を設定。
	SetFishModelPos();

	//魚のUIの場所を設定。
	SetFishUIPosition(m_fishModel->GetCurrentFishRangeAndMaxRangeRate(m_fishModelPos.z));
	
	//次回も足し算ができるようにポジションをゼロにする。
	ResetFishModelPosition();

}


void PlayFishingStateBase::ResetFishModelPosition()
{
	m_sum_fishModelPos = Vector3{0.0f,0.0f,0.0f};
}

void PlayFishingStateBase::ResetFloatModelPosition()
{
	m_sum_floatModelPos =Vector3{ 0.0f,0.0f,0.0f };
}

void PlayFishingStateBase::SetFloat()
{
	//ウキのモデルの場所を設定
	SetFloatPosition();
	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
	//ウキのUIの場所を設定。
	SetFloatUIPosition(m_rodFloatMove->GetCurrent_Float_Range_Max_Range_Rate(m_rodFloatMove->m_position.z));
	//次回も足し算ができるようにポジションをゼロにする。
	ResetFloatModelPosition();
}

void PlayFishingStateBase::SetFloatPosition()
{
	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
	m_floatModelPos = m_init_floatModelPos + m_sum_floatModelPos;
	m_rodFloatMove->SetPosition(m_floatModelPos);
}

void PlayFishingStateBase::SetFishModelPos()
{
	m_fishModel = FindGO<FishModel>("fishModel");
	m_fishModelPos = m_sum_fishModelPos + m_init_fishModelPos;
	m_fishModel->SetPosition(m_fishModelPos);

}

void PlayFishingStateBase::SetFishUIPosition(float current_fish_range_and_max_range_rate)
{
	m_tensionGauge = FindGO<TensionGauge>("tensionGauge");
	m_tensionGauge->SetFishUI_Position(current_fish_range_and_max_range_rate);
}

void PlayFishingStateBase::SetFloatUIPosition(float current_float_range_max_range_rate)
{
	m_tensionGauge = FindGO<TensionGauge>("tensionGauge");
	m_tensionGauge->SetFloatUI_Position(current_float_range_max_range_rate);

}

void PlayFishingStateBase::SetCurrentFishRangeAndMaxRangeRate(float current_fish_range_and_max_range_rate)
{
	m_sum_current_fish_range_and_max_range_rate= current_fish_range_and_max_range_rate;
}

Vector3 PlayFishingStateBase::GetRodPosition()
{
	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
	return m_rodFloatMove->GetPosition();
}

Vector3 PlayFishingStateBase::GetFishModelPosition()
{
	m_fishModel = FindGO<FishModel>("fishModel");
	return m_fishModel->GetPosistion();
}

void PlayFishingStateBase::Success()
{
	m_playFishing = FindGO<PlayFishing>("playFishing");
	m_playFishing->Success();
}

void PlayFishingStateBase::Failure()
{
	m_playFishing = FindGO<PlayFishing>("playFishing");
	m_playFishing->Failure();
}

void PlayFishingStateBase::Pass_Current_Fish_Range_And_Max_Range_Rate()
{
	m_playFishing->m_current_fish_range_and_max_range_rate = m_sum_current_fish_range_and_max_range_rate;
}

void PlayFishingStateBase::Pass_Current_Float_Range_And_Max_Range_Rate()
{
	m_playFishing->m_current_float_range_max_range_rate = m_sum_current_float_range_max_range_rate;

}

void PlayFishingStateBase::Pass_FishModelPos()
{
	m_playFishing->m_fishModelPos=m_fishModelPos;
}

void PlayFishingStateBase::Pass_FloatModelPos()
{
	m_playFishing->m_rodFloatModelPos = m_floatModelPos;
}

void PlayFishingStateBase::Set_Init_Current_Fish_Range_And_Max_Range_Rate()
{
	m_playFishing = FindGO<PlayFishing>("playFishing");
	m_sum_current_fish_range_and_max_range_rate = m_playFishing->m_current_fish_range_and_max_range_rate;
}

void PlayFishingStateBase::Set_Init_Current_Float_Range_And_Max_Range_Rate()
{
	m_playFishing = FindGO<PlayFishing>("playFishing");
	m_sum_current_float_range_max_range_rate = m_playFishing->m_current_float_range_max_range_rate;
}

void PlayFishingStateBase::Set_Init_FishModelPos()
{
	m_playFishing = FindGO<PlayFishing>("playFishing");
	m_init_fishModelPos = m_playFishing->m_fishModelPos;
}

void PlayFishingStateBase::Set_Init_FloatModelPos()
{
	m_playFishing = FindGO<PlayFishing>("playFishing");
	m_init_floatModelPos= m_playFishing->m_rodFloatModelPos;
}

float PlayFishingStateBase::GetCurrentFishRangeAndMaxRangeRate()
{
	m_fishModel = FindGO<FishModel>("fishModel");
	return m_fishModel->GetCurrentFishRangeAndMaxRangeRate(m_fishModelPos.z);
}

float PlayFishingStateBase::GetCurrent_Float_Range_Max_Range_Rate()
{
	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
	return m_rodFloatMove->GetCurrent_Float_Range_Max_Range_Rate(m_rodFloatMove->m_position.z);
}

Vector3 PlayFishingStateBase::GetPlayerPos()
{
	m_player = FindGO<Player>("player_Playfishing");
	return m_player->m_position;
}

Vector3 PlayFishingStateBase::GetFishModelPos()
{
	return m_fishModelPos;
}

Vector3 PlayFishingStateBase::GetFloatModelPos()
{
	return m_floatModelPos;
}

Vector3 PlayFishingStateBase::Floating()
{
	m_floating_t += 0.05;
	m_floating.y = (cos(m_floating_t * 0.9))*0.3 ;//上下に動かす
	m_floating.z = (cos(m_floating_t * 0.7/*周期をずらす*/)*0.5 );//左右に動かす
	m_floating.x = (cos(m_floating_t * 0.3) * 0.2);
	return m_floating;
}
