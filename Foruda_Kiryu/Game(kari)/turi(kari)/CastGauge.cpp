#include "stdafx.h"
#include "CastGauge.h"

CastGauge::CastGauge()
{
	m_castGaugeOutside.Init("Assets/modelData/castGauge_Outside.DDS", 100, 500);
	m_castGaugeOutside.SetPivot(Vector2(0.0f, 0.5f));
	m_castGaugeOutside.SetPosition(Vector3(500.0f, 0.0f, 0.0f));
	m_castGaugeOutside.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_castGaugeOutside.Update();

	m_castGaugeInside.Init("Assets/modelData/castGauge_inside.DDS", 100, 500);
	m_castGaugeInside.SetPivot(Vector2(0.0f, 0.5f));
	m_castGaugeInside.SetPosition(Vector3(500.0f, 0.0f, 0.0f));
	m_castGaugeInside.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_castGaugeInside.Update();

	m_castGaugeArrow.Init("Assets/modelData/castGauge_arrow.DDS", 110, 10);
	m_castGaugeArrow.SetPivot(Vector2(0.0f, 0.5f));
	m_castGaugeArrow.SetPosition(Vector3(490.0f, -237.0f, 0.0f));
	m_castGaugeArrow.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_castGaugeArrow.Update();
	
}

CastGauge::~CastGauge()
{
}

void CastGauge::Update()
{
}

void CastGauge::Render(RenderContext& rc)
{
	m_castGaugeInside.Draw(rc);
	m_castGaugeArrow.Draw(rc);
	m_castGaugeOutside.Draw(rc);
}
