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

void Fish::SetIndividualValue()
{
	m_individualValue = individualValue;
}

void Fish::SetTimeUntilEscape(float timeUntilEscape)//“¦‚°‚é‚Ü‚Å‚ÌŠÔ‚ğİ’è‚·‚éB
{
	m_timeUntilEscape = timeUntilEscape;
}

bool Fish::TimeCount()
{
	/*if (m_time < m_timeUntilEscape) {*/
		m_time++;
		if (m_time >= m_timeUntilEscape)
		{
			return true;
		}
		else {
			return false;
		}
	//}
}
