#include "stdafx.h"
#include "Hirame.h"

Hirame::Hirame()
{
	SetUI();
	SetBaseScore(120.0f);
	SetScore();
	SetTimeUntilEscape(15.0f);
	SetInitPos(0.7f);
}

Hirame::~Hirame()
{

}

/// <summary>
/// UIの設定
/// </summary>
void Hirame::SetUI()
{
	m_ui.Init("Assets/modelData/hirameUI.DDS", 150, 150);
	/*m_ui.SetPivot(Vector2(0.5f, 0.5f));
	m_ui.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_ui.Update();*/
}

void Hirame::Effect()
{

}
