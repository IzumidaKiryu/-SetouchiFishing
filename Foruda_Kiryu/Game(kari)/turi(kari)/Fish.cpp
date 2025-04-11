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
/// 個体値を設定する。
/// </summary>
/// <param name="baseIndividualValue"></param>
void Fish::SetScore()
{
	//魚のスコアに個体差を出す。
	//魚のスコアは基準のスコア×（0.8から1.2までのランダムな数）で計算をする。
	float individualValueMagnification =( 0.4f / 100 )* (rand() % 100 + 1);//個体差の倍率
	individualValueMagnification += 0.8;

	m_fishData.score = m_baseScore * individualValueMagnification;//基準のスコア×個体差の倍率。
}

/// <summary>
/// 逃げるまでの時間を設定する。
/// </summary>
/// <param name="timeUntilEscape"></param>
void Fish::SetTimeUntilEscape(float timeUntilEscape)
{
	m_timeUntilEscape = timeUntilEscape;
}

/// <summary>
/// 時間をはかる。
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
/// 魚を別の魚に変えていいか判断する関数
/// </summary>
//void Fish::ShouldFishChange()
//{
//	//この魚が選択中の時は別の魚に変えない。
//	if (m_isSelected =! true)
//	{
//		ShouldFishChangeTrue();
//	}
//}

void Fish::ShouldFishChangeTrue()
{
	//この魚が選択中の時は別の魚に変えない。
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

