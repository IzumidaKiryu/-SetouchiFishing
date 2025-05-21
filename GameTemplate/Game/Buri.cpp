#include "stdafx.h"
#include "Buri.h"

Buri::Buri()
{
	SetUI();

	SetParameter(10.0f, 5.0f, 100.0f, 0.6,50,50);
}

Buri::~Buri()
{

}

/// <summary>
/// UIの設定
/// </summary>
void Buri::SetUI()
{
	m_ui.Init("Assets/modelData/buriUI.DDS", 150, 150);
	m_ui.SetPivot(Vector2(0.5f, 0.5f));
	m_ui.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_ui.Update();
}