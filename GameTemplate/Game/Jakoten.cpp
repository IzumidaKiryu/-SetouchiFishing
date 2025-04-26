#include "stdafx.h"
#include "Jakoten.h"

Jakoten::Jakoten()
{
	SetUI();
	SetBaseScore(120.0f);
	SetScore();
	SetTimeUntilEscape(10.0f);
	SetInitPos(0.7f);
}

Jakoten::~Jakoten()
{

}

/// <summary>
/// UIの設定
/// </summary>
void Jakoten::SetUI()
{
	m_ui.Init("Assets/modelData/jakotenUI.DDS", 150, 150);
	/*m_ui.SetPivot(Vector2(0.5f, 0.5f));
	m_ui.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_ui.Update();*/
}
