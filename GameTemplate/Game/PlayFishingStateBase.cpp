#include "stdafx.h"
#include "PlayFishingStateBase.h"
#include "GameCamera.h"
#include "FishModel.h"
#include "RodFloatMove.h"
#include "PlayFishing.h"
#include "TensionGauge.h"
#include "Player.h"

PlayFishingStateBase::PlayFishingStateBase()
{
}

PlayFishingStateBase::~PlayFishingStateBase()
{
    // ウキが生成されていないときは実行しない。
    if (m_rodFloatMove != nullptr) {
        // ウキの距離の割合いを更新。
        m_floatDistanceRate = m_rodFloatMove->GetCurrentFloatDistanceRate(m_rodFloatMove->m_position.z);
    }

    // 現在のステートの情報をPlayFishingに同期する。
    SyncStateToPlayFishing();
}

bool PlayFishingStateBase::Start()
{
    m_playFishing = FindGO<PlayFishing>("playFishing");
    m_fishModel = FindGO<FishModel>("fishModel");
    m_tensionGauge = FindGO<TensionGauge>("tensionGauge");
    m_player = FindGO<Player>("player_Playfishing");

    if (m_playFishing->m_playFishingStatus == PlayFishingStatus::cast) {
        // ウキを作成。
        m_rodFloatMove = NewGO<RodFloatMove>(0, "rodFloatMove");
        m_rodFloatMove->Init();
    }

    if (m_playFishing->m_playFishingStatus >= PlayFishingStatus::successUI) {
        m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
    }

    SetFishData();
    LoadInitialStateFromPlayFishing();
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

void PlayFishingStateBase::SetFishData()
{
    m_fishData = m_playFishing->GetFishData();
}

void PlayFishingStateBase::SetFish()
{
    SetFishModelPos();
    SetFishUIPosition(m_fishModel->GetCurrentFishDistanceRate(m_fishModelPos.z));
    ResetFishModelPosition();
}

void PlayFishingStateBase::SetFloat()
{
    SetFloatPosition();
    SetFloatUIPosition(m_rodFloatMove->GetCurrentFloatDistanceRate(m_rodFloatMove->m_position.z));
    ResetFloatModelPosition();
}

void PlayFishingStateBase::SetCamera(Vector3 position, Vector3 targete)
{
    m_gameCamera->SetPosition(position);
    m_gameCamera->SetTarget(targete);
}

void PlayFishingStateBase::SetFishModelPos()
{
    m_fishModelPos = m_sumFishModelPos + m_initFishModelPos;
    m_fishModel->SetPosition(m_fishModelPos);
}

void PlayFishingStateBase::SetFloatPosition()
{
    m_floatModelPos = m_initFloatModelPos + m_sumFloatModelPos;
    m_rodFloatMove->SetPosition(m_floatModelPos);
}

void PlayFishingStateBase::SetFishUIPosition(float currentFishDistanceRate)
{
    m_tensionGauge->SetFishUI_Position(currentFishDistanceRate);
}

void PlayFishingStateBase::SetFloatUIPosition(float currentFloatDistanceRate)
{
    m_tensionGauge->SetFloatUI_Position(currentFloatDistanceRate);
}

void PlayFishingStateBase::ResetFishModelPosition()
{
    m_sumFishModelPos = Vector3::Zero;
}

void PlayFishingStateBase::ResetFloatModelPosition()
{
    m_sumFloatModelPos = Vector3::Zero;
}

void PlayFishingStateBase::SumFishModelPosition(Vector3 position)
{
    m_sumFishModelPos += position;
}

void PlayFishingStateBase::SumFishModelPosition(float currentFishDistanceRate)
{
    m_sumFishModelPos += Vector3{ 0.0f, 0.0f, m_fishModel->ChangePosition_Z(currentFishDistanceRate) };
}

void PlayFishingStateBase::SumRodFloatPosition(Vector3 position)
{
    m_sumFloatModelPos += position;
}

void PlayFishingStateBase::SumRodFloatPosition(float currentFloatDistanceRate)
{
    m_sumFloatModelPos += Vector3{ 0.0f, 0.0f, m_rodFloatMove->ChangePosition_Z(currentFloatDistanceRate) };
}

void PlayFishingStateBase::SetCurrentFishDistanceRate(float currentFishDistanceRate)
{
    m_fishDistanceRate = currentFishDistanceRate;
}

float PlayFishingStateBase::GetCurrentFishRangeAndMaxRangeRate()
{
    return m_fishModel->GetCurrentFishDistanceRate(m_fishModelPos.z);
}

float PlayFishingStateBase::GetCurrent_Float_Range_Max_Range_Rate()
{
    return m_rodFloatMove->GetCurrentFloatDistanceRate(m_rodFloatMove->m_position.z);
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

void PlayFishingStateBase::Success()
{
    m_playFishing->Success();
}

void PlayFishingStateBase::Failure()
{
    m_playFishing->Failure();
}

void PlayFishingStateBase::CameraManagement()
{
    // 必要に応じてオーバーライドされるカメラ処理
}

void PlayFishingStateBase::SyncStateToPlayFishing()
{
    // 現在のステート情報をPlayFishingにコピー
    m_playFishing->m_fishDistanceRate = m_fishDistanceRate;
    m_playFishing->m_floatDistanceRate = m_floatDistanceRate;
    m_playFishing->m_fishModelPos = m_fishModelPos;
    m_playFishing->m_rodFloatModelPos = m_floatModelPos;
    m_playFishing->m_cameraPos = m_cameraPos;
    m_playFishing->m_cameraTarget = m_cameraTarget;
}

void PlayFishingStateBase::LoadInitialStateFromPlayFishing()
{
    // PlayFishingから初期状態を読み込む
    m_fishDistanceRate = m_playFishing->m_fishDistanceRate;
    m_floatDistanceRate = m_playFishing->m_floatDistanceRate;
    m_initFishModelPos = m_playFishing->m_fishModelPos;
    m_initFloatModelPos = m_playFishing->m_rodFloatModelPos;
    m_cameraPos = m_playFishing->m_cameraPos;
    m_cameraTarget = m_playFishing->m_cameraTarget;
}

FishFacing PlayFishingStateBase::GetFishFacing() const
{
    return m_fishFacing;
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
