#include "stdafx.h"
#include "Tai.h"



Tai::Tai()
{
	SetFishType(FishType::TAI);
	SetUI();
	SetParameter(10.0f, 5.0f, 10000.0f, 0.6, 50, 50);
	SetTimeUntilEscape(5.0f);
	SetInitPos(0.6f);
	SetScore();
}

Tai::~Tai()
{

}

/// <summary>
/// UIの設定
/// </summary>
void Tai::SetUI()
{
	m_ui.Init("Assets/modelData/taiUI.DDS", 150, 150);
	m_ui.SetPivot(Vector2(0.5f, 0.5f));
	m_ui.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_ui.Update();
}
