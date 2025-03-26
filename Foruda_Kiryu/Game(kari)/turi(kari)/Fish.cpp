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
	TimeCount();
}

/// <summary>
/// �̒l��ݒ肷��B
/// </summary>
/// <param name="baseIndividualValue"></param>
void Fish::SetIndividualValue(float baseIndividualValue)
{

	//���̌̒l�͊�̌̒l�~�i0.8����1.2�܂ł̃����_���Ȑ��j�Ōv�Z������B
	float individualValueMagnification =( 0.4f / 100 )* (rand() % 100 + 1);//�̒l�̔{��
	individualValueMagnification += 0.8;

	m_individualValue = baseIndividualValue* individualValueMagnification;
}

/// <summary>
/// ������܂ł̎��Ԃ�ݒ肷��B
/// </summary>
/// <param name="timeUntilEscape"></param>
void Fish::SetTimeUntilEscape(float timeUntilEscape)
{
	m_timeUntilEscape = timeUntilEscape;
}

/// <summary>
/// ���Ԃ��͂���B
/// </summary>
/// <returns></returns>
bool Fish::TimeCount()
{
		m_time++;
		if (m_time >= m_timeUntilEscape)
		{
			ShouldFishChangeTrue();
			return true;
		}
		else {
			return false;
		}
}

/// <summary>
/// ����ʂ̋��ɕς��Ă��������f����֐�
/// </summary>
//void Fish::ShouldFishChange()
//{
//	//���̋����I�𒆂̎��͕ʂ̋��ɕς��Ȃ��B
//	if (m_isSelected =! true)
//	{
//		ShouldFishChangeTrue();
//	}
//}

void Fish::ShouldFishChangeTrue()
{
	//���̋����I�𒆂̎��͕ʂ̋��ɕς��Ȃ��B
	if (m_isSelected = !true)
	{
		m_shouldFishChange = true;
	}
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

