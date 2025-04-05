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
/// �̒l��ݒ肷��B
/// </summary>
/// <param name="baseIndividualValue"></param>
void Fish::SetIndividualValue(float baseIndividualValue)
{

	//���̌̒l�͊�̌̒l�~�i0.8����1.2�܂ł̃����_���Ȑ��j�Ōv�Z������B
	float individualValueMagnification=0.4/(rand()%100)+1;//�̒l�̔{��
	individualValueMagnification += 0.8;

	m_individualValue = baseIndividualValue* individualValueMagnification;
}

void Fish::SetTimeUntilEscape(float timeUntilEscape)//������܂ł̎��Ԃ�ݒ肷��B
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
	//���̋����I�𒆂̎��͕ʂ̋��ɕς��Ȃ��B
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

