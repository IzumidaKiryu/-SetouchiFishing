#include "stdafx.h"
#include "CastGauge.h"

CastGauge::CastGauge()
{
	m_castGaugeOutside.Init("Assets/modelData/castGauge_inside.DDS", 100, 500);
	m_castGaugeOutside.SetPivot(Vector2(0.0f, 0.5f));
	m_castGaugeOutside.SetPosition(Vector3(-850.0f, 450.0f, 0.0f));
	m_castGaugeOutside.SetScale(Vector3{ 0.35f, 0.5f, 1.0f });
	
	
}

CastGauge::~CastGauge()
{
}

void CastGauge::Update()
{
}

void CastGauge::Render(RenderContext& rc)
{
	m_castGaugeOutside.Draw(rc);
}
