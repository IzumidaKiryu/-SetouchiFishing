#include "stdafx.h"
#include "StealPositionBar.h"
#include "PositionSelection.h"

StealPositionBar::StealPositionBar()
{
	m_stealPositionBarOutsideUI.Init("Assets/modelData/landscape_gauge_inside.DDS", 500, 100);
	m_stealPositionBarOutsideUI.SetPivot(Vector2(0.5f, 0.5f));
	m_stealPositionBarOutsideUI.SetPosition(Vector3{ 500.0f, 390.0f, 0.0f });
	m_stealPositionBarOutsideUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_stealPositionBarOutsideUI.Update();

	m_stealPositionBarInsideUI.Init("Assets/modelData/landscape_gauge_outer.DDS", 500, 100);
	m_stealPositionBarInsideUI.SetPivot(Vector2(0.5f, 0.5f));
	m_stealPositionBarInsideUI.SetPosition(Vector3{ 500.0f, 390.0f, 0.0f });
	m_stealPositionBarInsideUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_stealPositionBarInsideUI.Update();

	m_stealPositionGaugeUI.Init("Assets/modelData/cast_successful.DDS", 500.0f, 100);
	m_stealPositionGaugeUI.SetPivot(Vector2(0.0f, 0.5f));
		m_stealPositionGaugeUI.SetPosition(Vector3{ 500.0f-240.0f, 390.0f, 0.0f });
		
}

void StealPositionBar::Render(RenderContext& rc)
{
	m_stealPositionBarOutsideUI.Draw(rc);
	m_stealPositionGaugeUI.Draw(rc);
	m_stealPositionBarInsideUI.Draw(rc);
		

}

void StealPositionBar::Update()
{
	AddStealPoint(m_point_increase_in_frame);
	SetBarLength();

}

void StealPositionBar::SetBarLength()
{
	m_piling_up_bar_count = m_stealPoint / m_bar_one_minutes_point;

	m_bar_rate = (m_stealPoint / m_bar_one_minutes_point)- m_piling_up_bar_count;//バーの割合を求める。
	m_bar_Length = m_max_barLength*m_bar_rate;//マックスの長さに割合を掛けて表示する長さを求める。
	m_stealPositionGaugeUI.SetScale(Vector3{ m_bar_Length, 1.0f, 1.0f });
	m_stealPositionGaugeUI.Update();
}

void StealPositionBar::AddStealPoint(float addPoint)
{
	m_stealPoint += addPoint;
}
