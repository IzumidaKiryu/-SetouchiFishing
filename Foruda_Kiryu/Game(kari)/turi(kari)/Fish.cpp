#include "stdafx.h"
#include "Fish.h"

Fish::Fish()
{

}

Fish::~Fish()
{
}

void Fish::Update()
{
}


void Fish::SetIndividualValue(float individualValue)//個体値を設定する。
{
	m_individualValue = individualValue;
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
