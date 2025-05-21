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
	TimeCount();
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
	//????X?R?A????X?R?A?~?i0.8????1.2????????_??????j??v?Z?????B
	float individualValueMagnification = (0.4f / 100) * (rd() % 100 + 1);//??????{??
	individualValueMagnification += 0.8;

	m_fishData.score = m_baseScore * individualValueMagnification;//???X?R?A?~??????{???B
}

/// <summary>
/// 逃げるまでの時間を設定する。
/// </summary>
/// <param name="timeUntilEscape"></param>
void Fish::SetTimeUntilEscape(float timeUntilEscape)
{
	m_fishData.timeUntilEscape = timeUntilEscape;
}

void Fish::SetArrowSpeed(float arrowspeed)
{
	m_fishData.arrowSpeed = arrowspeed;
}

void Fish::SetBaseScore(float baseScore)
{
	m_baseScore = baseScore;
}

void Fish::SetInitPos(float initpos)
{
	m_fishData.initPos = initpos;
}

void Fish::SetUpWardBias(float bias)
{
	//範囲を超えた値が入ったら0以上100以下にする。
	if (bias < 0) {
		bias = 0;
	}

	if (bias > 100) {
		bias = 100;
	}
	m_fishData.upwardBias = bias;

}

void Fish::SetDownwardBias(float bias)
{
	//範囲を超えた値が入ったら0以上100以下にする。
	if (bias < 0) {
		bias = 0;
	}

	if (bias > 100) {
		bias = 100;
	}
	m_fishData.downwardBias = bias;
}

void Fish::SetFishDetectionRadius(float fishDetectionRadius)
{
	
	//範囲を超えた値が入ったら0以上100以下にする。
	if (fishDetectionRadius < 0) {
		fishDetectionRadius = 0;
	}

	if (fishDetectionRadius > 1) {
		fishDetectionRadius = 1;
	}
	m_fishData.fishDetectionRadius = fishDetectionRadius;
}

void Fish::SetParameter(float timeUntilEscape, float arrowspeed, 
	float baseScore, float initpos,
	float upwardBias,float downwardBias,
	float fishDetectionRadius)
{
	SetTimeUntilEscape(timeUntilEscape);
	SetArrowSpeed(arrowspeed);
	SetBaseScore(baseScore);
	SetInitPos(initpos);
	SetUpWardBias(upwardBias);
	SetDownwardBias(downwardBias);
	SetFishDetectionRadius(fishDetectionRadius);
}

/// <summary>
/// 時間をはかる。
/// </summary>
/// <returns></returns>
bool Fish::TimeCount()
{
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_nowTime = m_positionSelection->GetTime();

	//魚が逃げるまでの残り時間を計算する。
	m_timeRatio = ((m_initialTime-m_nowTime)/m_fishData.timeUntilEscape);

	if (m_initialTime - m_nowTime <= m_fishData.timeUntilEscape)
	{
		return true;
	}
	if(m_initialTime - m_nowTime >= m_fishData.timeUntilEscape) {
		ShouldFishChangeTrue();
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

float Fish::GetTimeRatio()
{
	return m_timeRatio;
}


/// <summary>
/// 釣った後の効果。
/// </summary>
void Fish::Effect()
{
}



FishData& Fish::GetFishData()
{
	return m_fishData;
}

SpriteRender& Fish::GetUI()
{
	return m_ui;
}

