#include "stdafx.h"
#include "Buri.h"

Buri::Buri()
{
	SetUI();
	SetBaseScore(100.0f);//基準になるスコア。
	SetScore();//この魚のスコアを設定。
	SetTimeUntilEscape(10.0f);
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