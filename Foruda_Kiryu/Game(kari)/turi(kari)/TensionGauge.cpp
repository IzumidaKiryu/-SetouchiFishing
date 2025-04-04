#include "stdafx.h"
#include "TensionGauge.h"
#include "GetRotation.h"
#include <Time.h>


TensionGauge::TensionGauge()
{
	srand(time(nullptr));
	//m_tensionGaugeInside.Init("Assets/modelData/tensionGauge.DDS", 500, 100);
	m_tensionGaugeInside.Init("Assets/modelData/castGauge_inside.DDS", 500, 100);
	m_tensionGaugeInside.SetPivot(Vector2(0.5f, 0.5f));
	m_tensionGaugeInside.SetPosition(Vector3(0.0f, -200.0f, 0.0f));
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
	m_getRotation = NewGO<GetRotation>(0, "getRotation");
}

TensionGauge::~TensionGauge()
{
}

void TensionGauge::Update()
{
	SetFishEscapePower();
	SetArrowPosition();
}

void TensionGauge::RightAndLeftManagement()
{

}

void TensionGauge::SetArrowPosition()
{
	m_arrowPosition = m_getRotation->rotationQuantity*100+ m_fishEscapePower;
	m_tensionGaugeArrow.SetPosition(Vector3(m_arrowPosition, -200.0f, 0.0f));
	m_tensionGaugeArrow.Update();
}

void TensionGauge::SetFishEscapePower()
{
	//float randum = rand() % 10000;
	//randum -= 5000.0f;
	//randum /= 1000.0f;

	//m_fishEscapePower+=randum;
}

void TensionGauge::m_isfishEscapePowerDirectionChange()
{
}

void TensionGauge::m_fishEscapePowerDirectionChange()
{
	float randum = rand() % 100;
}

void TensionGauge::Render(RenderContext& rc)
{
	m_tensionGaugeInside.Draw(rc);
	m_tensionGaugeOutside.Draw(rc);
	m_tensionGaugeArrow.Draw(rc);
}
