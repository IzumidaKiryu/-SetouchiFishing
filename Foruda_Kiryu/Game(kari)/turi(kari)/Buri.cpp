#include "stdafx.h"
#include "Buri.h"

Buri::Buri()
{
	SetUI();
	SetIndividualValue(m_individualValue);
	SetTimeUntilEscape(10.0f);
}

Buri::~Buri()
{

}

/// <summary>
/// UIÇÃê›íË
/// </summary>
void Buri::SetUI()
{
	m_ui->Init("Assets/modelData/buriUI.DDS", 150, 150);
	m_ui->SetPivot(Vector2(0.5f, 0.5f));
	m_ui->SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_ui->Update();
}