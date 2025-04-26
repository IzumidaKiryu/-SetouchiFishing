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

	//�|�W�V������ݒ�B
	SetPosition();
}

void FishModel::Render(RenderContext& rc)
{
	m_fishModel.Draw(rc);

}

void FishModel::SetPosition(Vector3 position)
{
	m_position = position;
}

void FishModel::SetInitPositon()
{
	
}
/// <summary>
/// �v���C�t�B�b�V���̋����̊����������ƂɃ|�W�V������ݒ肷��B
/// </summary>
void FishModel::SetPosition()
{
	m_fishModel.SetPosition({ 0.0f,3.0f, m_playFishing->m_current_fish_range_and_max_range_rate * m_limit_range_with_ship });
	m_fishModel.Update();
}
