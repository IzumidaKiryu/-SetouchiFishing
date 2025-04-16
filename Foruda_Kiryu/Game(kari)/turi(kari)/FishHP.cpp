#include "stdafx.h"
#include "FishHP.h"

FishHP::FishHP()
{
	m_fishHPBar.Init("Assets/sprite/fishHPBar.DDS", 100, 500);
	m_fishHPBar.SetPivot(Vector2(0.0f, 0.5f));
	m_fishHPBar.SetPosition(Vector3(500.0f, 0.0f, 0.0f));
	m_fishHPBar.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_fishHPBar.Update();

	m_fishHPBarFrame.Init("Assets/sprite/fishHPBarFrame.DDS", 100, 500);
	m_fishHPBarFrame.SetPivot(Vector2(0.0f, 0.5f));
	m_fishHPBarFrame.SetPosition(Vector3(500.0f, 0.0f, 0.0f));
	m_fishHPBarFrame.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_fishHPBarFrame.Update();
}

FishHP::~FishHP()
{

}

void FishHP::Update()
{
	
}

void FishHP::FishHPManagement()
{
	m_fishHP -= 0.1f;
}

void FishHP::Render(RenderContext& rc)
{
	m_fishHPBar.Draw(rc);
	m_fishHPBarFrame.Draw(rc);
}

