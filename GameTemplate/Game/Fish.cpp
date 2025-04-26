#include "stdafx.h"
#include "Fish.h"
#include "PositionSelection.h"
#include <random>


Fish::Fish()
{
	srand(time(NULL));
}

Fish::~Fish()
{

}

void Fish::Update()
{
	/*TimeCount();*/
}

bool Fish::Start()
{
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_initialTime = m_positionSelection->GetTime();
	return true;
}

/// <summary>
/// ???l??????B
/// </summary>
/// <param name="baseIndividualValue"></param>
void Fish::SetScore()
{
	std::random_device rd;
	//????X?R?A???????o???B
	//????X?R?A??�T??X?R?A?~?i0.8????1.2????????_??????j??v?Z?????B
	float individualValueMagnification = (0.4f / 100) * (rd() % 100 + 1);//??????{??
	individualValueMagnification += 0.8;

	m_fishData.score = m_baseScore * individualValueMagnification;//?�T??X?R?A?~??????{???B
}

/// <summary>
/// ������܂ł̎��Ԃ�ݒ肷��B
/// </summary>
/// <param name="timeUntilEscape"></param>
void Fish::SetTimeUntilEscape(float timeUntilEscape)
{
	m_fishData.timeUntilEscape = timeUntilEscape;
}

void Fish::SetInitPos(float initpos)
{
	m_fishData.initPos = initpos;
}

/// <summary>
/// ���Ԃ��͂���B
/// </summary>
/// <returns></returns>
bool Fish::TimeCount()
{
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_nowTime = m_positionSelection->GetTime();

	if (m_initialTime - m_nowTime <= m_fishData.timeUntilEscape)
	{
		return true;
	}
	else {
		ShouldFishChangeTrue();
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
	if (m_isSelected != true)
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

bool Fish::GetShouldFishChange()
{
	return m_shouldFishChange;
}


void Fish::SetBaseScore(float individualScore)
{
	m_baseScore = individualScore;
}

FishData& Fish::GetFishData()
{
	return m_fishData;
}

SpriteRender& Fish::GetUI()
{
	return m_ui;
}

