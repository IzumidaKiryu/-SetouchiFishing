#include "stdafx.h"
#include "TensionGauge.h"

TensionGauge::TensionGauge()
{
	m_tensionGauge.Init("Assets/modelData/castGauge_Outside.DDS", 100, 500);
	m_tensionGauge.SetPivot(Vector2(0.0f, 0.5f));
	m_tensionGauge.SetPosition(Vector3(500.0f, 0.0f, 0.0f));
	m_tensionGauge.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_tensionGauge.Update();
}

TensionGauge::~TensionGauge()
{
}
