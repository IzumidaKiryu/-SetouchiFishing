#include "stdafx.h"
#include "TensionGauge.h"
#include "GetRotation.h"

TensionGauge::TensionGauge()
{
	m_tensionGaugeInside.Init("Assets/modelData/tensionGauge.DDS", 500, 100);
	m_tensionGaugeInside.SetPivot(Vector2(0.5f, 0.5f));
	m_tensionGaugeInside.SetPosition(Vector3(0.0f,-200.0f, 0.0f));
	m_tensionGaugeInside.SetScale(Vector3{ 2.0f, 1.0f, 1.0f });
	m_tensionGaugeInside.Update();

	m_tensionGaugeOutside.Init("Assets/modelData/tensionGaugeFrame.DDS", 500, 100);
	m_tensionGaugeOutside.SetPivot(Vector2(0.5f, 0.5f));
	m_tensionGaugeOutside.SetPosition(Vector3(0.0f, -200.0f, 0.0f));
	m_tensionGaugeOutside.SetScale(Vector3{ 2.0f, 1.0f, 1.0f });
	m_tensionGaugeOutside.Update();

	m_tensionGaugeArrow.Init("Assets/modelData/tensionGaugeArrow.DDS", 10, 110);
	m_tensionGaugeArrow.SetPivot(Vector2(0.5f, 0.5f));
	m_tensionGaugeArrow.SetScale(Vector3{ 2.0f, 1.0f, 1.0f });
	m_getRotation = NewGO<GetRotation>(0,"getRotation");
}

TensionGauge::~TensionGauge()
{
}

void TensionGauge::Update()
{
	SetArrowPosition();
}

void TensionGauge::RightAndLeftManagement()
{

}

void TensionGauge::SetArrowPosition()
{
	m_arrowPosition = m_getRotation->rotationQuantity;
	m_tensionGaugeArrow.SetPosition(Vector3(m_arrowPosition, -200.0f, 0.0f));
	m_tensionGaugeArrow.Update();
}

void TensionGauge::Render(RenderContext& rc)
{
	m_tensionGaugeInside.Draw(rc);
	m_tensionGaugeOutside.Draw(rc);
	m_tensionGaugeArrow.Draw(rc);
}
