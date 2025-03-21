#include "stdafx.h"
#include "Tatiuo.h"

Tatiuo::Tatiuo()
{
	SetUI();
	SetIndividualValue(m_individualValue);
	SetTimeUntilEscape(10.0f);
}

Tatiuo::~Tatiuo()
{

}

/// <summary>
/// UIÇÃê›íË
/// </summary>
void Tatiuo::SetUI()
{
	m_ui.Init("Assets/modelData/tatiuoUI.DDS", 150, 150);
	m_ui.SetPivot(Vector2(0.5f, 0.5f));
	m_ui.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_ui.Update();
}
