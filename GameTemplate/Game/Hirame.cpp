#include "stdafx.h"
#include "Hirame.h"

Hirame::Hirame()
{
	SetUI();
	SetParameter(15.0f, 10.0f, 120.0f, 0.7);
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
