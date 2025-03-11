#include "stdafx.h"
#include "TensionGauge.h"

TensionGauge::TensionGauge()
{
	m_tensionGaugeInside.Init("Assets/modelData/castGauge_Outside.DDS", 500, 100);
	m_tensionGaugeInside.SetPivot(Vector2(0.0f, 0.5f));
	m_tensionGaugeInside.SetPosition(Vector3(500.0f, 0.0f, 0.0f));
	m_tensionGaugeInside.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_tensionGaugeInside.Update();

	m_tensionGaugeOutside.Init("Assets/modelData/castGauge_Outside.DDS", 500, 100);
	m_tensionGaugeOutside.SetPivot(Vector2(0.0f, 0.5f));
	m_tensionGaugeOutside.SetPosition(Vector3(500.0f, 0.0f, 0.0f));
	m_tensionGaugeOutside.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_tensionGaugeOutside.Update();
}

TensionGauge::~TensionGauge()
{
}

void TensionGauge::Render(RenderContext& rc)
{
	m_tensionGaugeInside.Draw(rc);
	m_tensionGaugeOutside.Draw(rc);
}
