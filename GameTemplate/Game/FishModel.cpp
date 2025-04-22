#include "stdafx.h"
#include "FishModel.h"

FishModel::FishModel()
{
	m_fishModel.SetPosition(Vector3{ 0.0f,0.0f,0.0f });;
	m_fishModel.SetScale(Vector3{ 1.0f,1.0f,1.0f });
	m_fishModel.Init("Assets/modelData/uki.tkm");
	m_fishModel.Update();
}

FishModel::~FishModel()
{

}

void FishModel::Update()
{

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
