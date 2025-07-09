#include "stdafx.h"
#include "FishModel.h"
#include"PlayFishing.h"


FishModel::FishModel()
{
}

FishModel::~FishModel()
{

}

bool FishModel::Init()
{
	SetShadowAnimationClipsLoad(
		"Assets/animData/Player/rod.tka"
	);

	SetAnimationClipsLoad();
	m_fishModel.Init("Assets/modelData/fishShadow.tkm"/*, m_animationClips,1, enModelUpAxisY*/);
	m_fishModel.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_fishModel.SetScale(m_scale);


	Quaternion upward;
	upward.SetRotationDegY(180);
	m_fishModel.SetRotation(upward);
	m_fishModel.Update();

	return true;
}

bool FishModel::Start()
{
	m_playFishing = FindGO<PlayFishing>("playFishing");

	return true;
}

void FishModel::Update()
{

	//ポジションを設定。
	SetPosition();

	//上向きにしているかどうか。
	if (m_is_TurningUpward) {
		TurnUpward();
	}
	//下向きにしているかどうか
	if (m_is_TurningDownward) {
		TurnDownward();
	}
}

void FishModel::SetShadowAnimationClipsLoad(const char* animationClip_Shadow)
{
	m_ShadowAnimationClips[enAnimationClip_Shadow].Load(animationClip_Shadow);
	m_ShadowAnimationClips[enAnimationClip_Shadow].SetLoopFlag(true);
}

void FishModel::Render(RenderContext& rc)
{
	m_fishModel.Draw(rc);

}

void FishModel::SetPosition(Vector3 position)
{
	m_position = position;
	m_fishModel.SetPosition(position);
	m_fishModel.Update();
}


void FishModel::SetInitPositon()
{

}
/// <summary>
/// プレイフィッシュの距離の割合いをもとにポジションを設定する。
/// </summary>
void FishModel::SetPosition()
{
	m_fishModel.SetPosition({ 0.0f,3.0f, m_playFishing->m_fishDistanceRate * m_limit_range_with_ship });
	m_fishModel.Update();
}

void FishModel::SetSumPosition(Vector3 position)
{
	m_position += position;
}

/// <summary>
/// 最大距離と今いる距離の割合いからZ軸のポジションを求める。
/// </summary>
/// <param name="currentFishDistanceRate"></param>
/// <returns></returns>
float FishModel::ChangePosition_Z(float currentFishDistanceRate)
{
	float position_z = m_limit_range_with_ship * currentFishDistanceRate;
	return position_z;
}

float FishModel::GetCurrentFishDistanceRate(float positionZ)
{
	float currentFishDistanceRate=0.0f;
	currentFishDistanceRate = positionZ / m_limit_range_with_ship;
	return currentFishDistanceRate;
}

Vector3 FishModel::GetPosistion()
{
	return m_position;
}

void FishModel::SetAnimationClipsLoad()
{
	m_animationClips.Load("Assets/animData/FishShadow/fishShadow.tka");
	m_animationClips.SetLoopFlag(true);
}

void FishModel::TurnUpward()
{
	turn_t += 0.1;
	Quaternion turn;
	Quaternion upward;
	upward.SetRotationDegY(0);
	turn.Slerp(turn_t, m_fishModel.GetRotation(), upward);
	m_fishModel.SetRotation(turn);
	if (turn_t > 1) {
		m_is_TurningUpward = false;
		turn_t = 0;
	}
}

void FishModel::TurnDownward()
{
	turn_t += 0.1;
	Quaternion turn;
	Quaternion downward;

	downward.SetRotationDegY(180);
	turn.Slerp(turn_t, m_fishModel.GetRotation(), downward);
	m_fishModel.SetRotation(turn);
	if (turn_t > 1) {
		m_is_TurningDownward = false;
		turn_t = 0;
	}
}

void FishModel::SetISTurningUpwardTrue()
{
	m_is_TurningUpward = true;
}

void FishModel::SetISTurningDownwardTrue()
{
	m_is_TurningDownward = true;
}

/// <summary>
/// 個体値に基づいてスケールを設定
/// </summary>
/// <param name="scale"></param>
void FishModel::SetScaleByIndividualFactor(float scale)
{
	m_fishModel.SetScale(m_scale*scale);
}
