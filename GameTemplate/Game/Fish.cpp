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
	//????X?R?A??őT??X?R?A?~?i0.8????1.2????????_??????j??v?Z?????B
	float individualValueMagnification = (0.4f / 100) * (rd() % 100 + 1);//??????{??
	individualValueMagnification += 0.8;

	m_fishData.score = m_baseScore * individualValueMagnification;//?őT??X?R?A?~??????{???B
}

/// <summary>
/// Ś°éÜĹĚÔđÝčˇéB
/// </summary>
/// <param name="timeUntilEscape"></param>
void Fish::SetTimeUntilEscape(float timeUntilEscape)
{
	m_fishData.timeUntilEscape = timeUntilEscape;
}

/// <summary>
/// ÔđÍŠéB
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
/// đĘĚÉĎŚÄ˘˘ŠťfˇéÖ
/// </summary>
//void Fish::ShouldFishChange()
//{
//	//ąĚŞIđĚÍĘĚÉĎŚČ˘B
//	if (m_isSelected =! true)
//	{
//		ShouldFishChangeTrue();
//	}
//}

void Fish::ShouldFishChangeTrue()
{
	//ąĚŞIđĚÍĘĚÉĎŚČ˘B
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

