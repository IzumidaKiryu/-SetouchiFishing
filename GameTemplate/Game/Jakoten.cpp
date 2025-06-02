#include "stdafx.h"
#include "Jakoten.h"

Jakoten::Jakoten()
{

	SetFishType(FishType::JAKOTENN);

	SetUI();
	SetParameter(
		12.0f, 
		5.0f, 
		120.0f, 
		0.7,
		80,
		30,
		0.3f
	);
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
