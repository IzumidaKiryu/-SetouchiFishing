#include "stdafx.h"
#include "Fish.h"
#include "PositionSelection.h"

Fish::Fish()
{
	srand(time(NULL));
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
}

Fish::~Fish()
{
	
}

void Fish::Update()
{
}

/// <summary>
/// 個体値を設定する。
/// </summary>
/// <param name="baseIndividualValue"></param>
void Fish::SetIndividualValue(float baseIndividualValue)
{

	//魚の個体値は基準の個体値×（0.8から1.2までのランダムな数）で計算をする。
	float individualValueMagnification=0.4/(rand()%100)+1;//個体値の倍率
	individualValueMagnification += 0.8;

	m_individualValue = baseIndividualValue* individualValueMagnification;
}

void Fish::SetTimeUntilEscape(float timeUntilEscape)//逃げるまでの時間を設定する。
{
	m_timeUntilEscape = timeUntilEscape;
}

bool Fish::TimeCount()
{
	if (m_time < m_timeUntilEscape) {
		m_time++;
		if (m_time >= m_timeUntilEscape)
		{

			return true;
		}
		else {
			return false;
		}
	}
}

void Fish::ShouldFishChange()
{
	//この魚が選択中の時は別の魚に変えない。
	if (m_isSelected =! true)
	{
		ShouldFishChangeTrue();
	}
}

void Fish::ShouldFishChangeTrue()
{
	m_shouldFishChange=true;
}

void Fish::ShouldFishChangeFalse()
{
	m_shouldFishChange = false;
}

void Fish::SetisSelectedTrue()
{
	m_isSelected = true;
}

void Fish::SetisSelectedFalse()
{
	m_isSelected = false;
}

