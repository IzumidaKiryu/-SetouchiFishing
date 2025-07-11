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
	

}

PlayFishingStateBase::~PlayFishingStateBase()
{
	if (m_rodFloatMove != nullptr) {
		m_sumCurrentFloatRangeMaxRangeRate = GetCurrent_Float_Range_Max_Range_Rate();
	}

	if (m_playFishing != nullptr) {
		Pass_Current_Fish_Range_And_Max_Range_Rate();
		Pass_Current_Float_Range_And_Max_Range_Rate();
		Pass_FishModelPos();
		Pass_FloatModelPos();
		Pass_CameraPos();
		Pass_CameraTarget();
	}

}

bool PlayFishingStateBase::Start()
{
	m_playFishing = FindGO<PlayFishing>("playFishing");
	m_fishModel = FindGO<FishModel>("fishModel");
	m_tensionGauge = FindGO<TensionGauge>("tensionGauge");
	m_player = FindGO<Player>("player_Playfishing");


	if (m_playFishing->m_playFishingStatus == PlayFishingStatus::cast) {
		//ウキを作成。
		m_rodFloatMove = NewGO<RodFloatMove>(0, "rodFloatMove");
		m_rodFloatMove->Init();
	}

	if (m_playFishing->m_playFishingStatus >= PlayFishingStatus::successUI)
	{
		m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");

	}

	SetFishData();


	Set_Init_Current_Fish_Range_And_Max_Range_Rate();
	Set_Init_Current_Float_Range_And_Max_Range_Rate();
	Set_Init_FishModelPos();
	Set_Init_FloatModelPos();

	Set_Init_CameraPos();
	Set_Init_CameraTarget();

	OnStart();
	return true;
}


bool PlayFishingStateBase::Init()
{
	OnInit();
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
	m_successfulOrFailure = success;
}

void PlayFishingStateBase::SetFailure()
{
	m_successfulOrFailure = failure;
}

Successful_or_Failure PlayFishingStateBase::GetSuccessful_or_Failure()
{
	return m_successfulOrFailure;
}

void PlayFishingStateBase::SetCamera(Vector3 position, Vector3 targete)
{
	m_gameCamera->SetPosition(position);
	m_gameCamera->SetTarget(targete);
}

void PlayFishingStateBase::SumFishModelPosition(Vector3 position)
{
	m_sumFishModelPos += position;
}

void PlayFishingStateBase::SumFishModelPosition(float current_fish_range_and_max_range_rate)
{
	m_sumFishModelPos += Vector3{ 0.0f,0.0f,m_fishModel->ChangePosition_Z(current_fish_range_and_max_range_rate) };
}

void PlayFishingStateBase::SumRodFloatPosition(Vector3 position)
{
	m_sumFloatModelPos += position;
}

void PlayFishingStateBase::SumRodFloatPosition(float current_float_range_max_range_rate)
{
	m_sumFloatModelPos += Vector3{ 0.0f,0.0f,m_rodFloatMove->ChangePosition_Z(current_float_range_max_range_rate) };
}

void PlayFishingStateBase::SetFishData()
{
	m_fishData = m_playFishing->GetFishData();
}

void PlayFishingStateBase::SetFish()
{
	//魚のモデルの場所を設定。
	SetFishModelPos();

	//魚のUIの場所を設定。
	SetFishUIPosition(m_fishModel->GetCurrentFishRangeAndMaxRangeRate(m_fishModelPos.z));

	//次回も足し算ができるようにポジションをゼロにする。
	ResetFishModelPosition();

}


void PlayFishingStateBase::ResetFishModelPosition()
{
	m_sumFishModelPos = Vector3{ 0.0f,0.0f,0.0f };
}

void PlayFishingStateBase::ResetFloatModelPosition()
{
	m_sumFloatModelPos = Vector3{ 0.0f,0.0f,0.0f };
}

void PlayFishingStateBase::SetFloat()
{
	//ウキのモデルの場所を設定
	SetFloatPosition();
	//ウキのUIの場所を設定。
	SetFloatUIPosition(m_rodFloatMove->GetCurrent_Float_Range_Max_Range_Rate(m_rodFloatMove->m_position.z));
	//次回も足し算ができるようにポジションをゼロにする。
	ResetFloatModelPosition();
}

void PlayFishingStateBase::SetFloatPosition()
{
	m_floatModelPos = m_initFloatModelPos + m_sumFloatModelPos;
	m_rodFloatMove->SetPosition(m_floatModelPos);
}

void PlayFishingStateBase::SetFishModelPos()
{
	
	m_fishModelPos = m_sumFishModelPos + m_initFishModelPos;
	m_fishModel->SetPosition(m_fishModelPos);

}

void PlayFishingStateBase::SetFishUIPosition(float current_fish_range_and_max_range_rate)
{
	m_tensionGauge->SetFishUIPosition(current_fish_range_and_max_range_rate);
}

void PlayFishingStateBase::SetFloatUIPosition(float current_float_range_max_range_rate)
{
	m_tensionGauge->SetFloatUIPosition(current_float_range_max_range_rate);

}

void PlayFishingStateBase::SetCurrentFishRangeAndMaxRangeRate(float current_fish_range_and_max_range_rate)
{
	m_currentFishRangeAndMaxRangeRate = current_fish_range_and_max_range_rate;
}

Vector3 PlayFishingStateBase::GetRodPosition()
{
	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
	return m_rodFloatMove->GetPosition();
}

Vector3 PlayFishingStateBase::GetFishModelPosition()
{
	return m_fishModel->GetPosistion();
}

void PlayFishingStateBase::Success()
{
	m_playFishing->Success();
}

void PlayFishingStateBase::Failure()
{
	m_playFishing->Failure();
}

void PlayFishingStateBase::Pass_Current_Fish_Range_And_Max_Range_Rate()
{
	m_playFishing->m_current_fish_range_and_max_range_rate = m_currentFishRangeAndMaxRangeRate;
}

void PlayFishingStateBase::Pass_Current_Float_Range_And_Max_Range_Rate()
{
	m_playFishing->m_current_float_range_max_range_rate = m_sumCurrentFloatRangeMaxRangeRate;

}

void PlayFishingStateBase::Pass_FishModelPos()
{
	m_playFishing->m_fishModelPos = m_fishModelPos;
}

void PlayFishingStateBase::Pass_FloatModelPos()
{
	m_playFishing->m_rodFloatModelPos = m_floatModelPos;
}

void PlayFishingStateBase::Pass_CameraPos()
{
	m_playFishing->m_cameraPos = m_cameraPos;
}

void PlayFishingStateBase::Pass_CameraTarget()
{
	m_playFishing->m_cameraTarget = m_cameraTarget;
}

void PlayFishingStateBase::Set_Init_Current_Fish_Range_And_Max_Range_Rate()
{

	m_currentFishRangeAndMaxRangeRate = m_playFishing->m_current_fish_range_and_max_range_rate;
}

void PlayFishingStateBase::Set_Init_Current_Float_Range_And_Max_Range_Rate()
{

	m_sumCurrentFloatRangeMaxRangeRate = m_playFishing->m_current_float_range_max_range_rate;
}

void PlayFishingStateBase::Set_Init_FishModelPos()
{

	m_initFishModelPos = m_playFishing->m_fishModelPos;
}

void PlayFishingStateBase::Set_Init_FloatModelPos()
{
	
	m_initFloatModelPos = m_playFishing->m_rodFloatModelPos;
}

void PlayFishingStateBase::Set_Init_CameraPos()
{
	m_cameraPos = m_playFishing->m_cameraPos;
}

void PlayFishingStateBase::Set_Init_CameraTarget()
{
	m_cameraTarget = m_playFishing->m_cameraTarget;
}

void PlayFishingStateBase::SetFishModelDownward()
{
	m_fishModel->SetISTurningUpwardTrue();
}

void PlayFishingStateBase::SetFishModelUpward()
{
	m_fishModel->SetISTurningDownwardTrue();

}

void PlayFishingStateBase::SetFishDownward()
{
	m_fishFacing = Downward;
	m_tensionGauge->SetDownwardFishUI();
	SetFishModelDownward();


}

void PlayFishingStateBase::SetFishUpward()
{
	m_fishFacing = Upward;
	m_tensionGauge->SetUpwardFishUI();
	SetFishModelUpward();
}

 void PlayFishingStateBase::CameraManagement()
{
}


float PlayFishingStateBase::GetCurrentFishRangeAndMaxRangeRate()
{
	return m_fishModel->GetCurrentFishRangeAndMaxRangeRate(m_fishModelPos.z);
}

float PlayFishingStateBase::GetCurrent_Float_Range_Max_Range_Rate()
{
	return m_rodFloatMove->GetCurrent_Float_Range_Max_Range_Rate(m_rodFloatMove->m_position.z);
}

Vector3 PlayFishingStateBase::GetPlayerPos()
{
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

void PlayFishingStateBase::SetFloatGameObject(RodFloatMove* rodfloatmove)
{
	m_rodFloatMove = rodfloatmove;
}


Vector3 PlayFishingStateBase::Floating(FloatingPattern floatingPattern)
{
	switch (floatingPattern)
	{
	case PlayFishingStateBase::CameraPattern:
		m_floatingTime += 0.08;
		m_floating.y = (cos(m_floatingTime * 0.2)) * 12.0f;//上下に動かす
		//m_floating.z = (cos(m_floating_t * 0.5/*周期をずらす*/) *8.0f);
		m_floating.x = (cos(m_floatingTime * 0.5) * 2.0f);//左右に動かす
		break;
	case PlayFishingStateBase::ModelPattern:
		m_floatingTime += 0.05;
		m_floating.y = (cos(m_floatingTime * 0.9)) * 0.3;//上下に動かす
		m_floating.z = (cos(m_floatingTime * 0.7/*周期をずらす*/) * 0.5);
		m_floating.x = (cos(m_floatingTime * 0.3) * 0.2);//左右に動かす
		break;
	default:
		break;
	}
	

	return m_floating;
}
