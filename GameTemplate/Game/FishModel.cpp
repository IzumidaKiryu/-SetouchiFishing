#include "stdafx.h"
#include "FishModel.h"
#include"PlayFishing.h"

FishModel::FishModel()
{
	m_fishModel.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_fishModel.SetScale(Vector3{ 1.0f,1.0f,1.0f });
	m_fishModel.Init("Assets/modelData/uki.tkm");
	m_fishModel.Update();
}

FishModel::~FishModel()
{

}

void FishModel::Update()
{
	m_playFishing = FindGO<PlayFishing>("playFishing");

	////ポジションを設定。
	//SetPosition();
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
	m_fishModel.SetPosition({ 0.0f,3.0f, m_playFishing->m_current_fish_range_and_max_range_rate * m_limit_range_with_ship });
	m_fishModel.Update();
}

void FishModel::SetSumPosition(Vector3 position)
{
	m_position += position;
}

/// <summary>
/// 最大距離と今いる距離の割合いからZ軸のポジションを求める。
/// </summary>
/// <param name="current_fish_range_and_max_range_rate"></param>
/// <returns></returns>
float FishModel::ChangePosition_Z(float current_fish_range_and_max_range_rate)
{
	float position_z=m_limit_range_with_ship* current_fish_range_and_max_range_rate;
	return position_z;
}

float FishModel::GetCurrentFishRangeAndMaxRangeRate(float position_z)
{
	float current_fish_range_and_max_range_rate;
	current_fish_range_and_max_range_rate = position_z / m_limit_range_with_ship;
	return current_fish_range_and_max_range_rate;
}

Vector3 FishModel::GetPosistion()
{
	return m_position;
}
