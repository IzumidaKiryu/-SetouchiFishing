#include "stdafx.h"
#include "Tatiuo.h"

Tatiuo::Tatiuo()
{
	SetUI();
	SetBaseScore(120.0f);
	SetScore();
	SetTimeUntilEscape(10.0f);
}

Tatiuo::~Tatiuo()
{

}

/// <summary>
/// UIの設定
/// </summary>
void Tatiuo::SetUI()
{
	m_ui.Init("Assets/modelData/tatiuo.DDS", 150, 150);
	/*m_ui.SetPivot(Vector2(0.5f, 0.5f));
	m_ui.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_ui.Update();*/
}
