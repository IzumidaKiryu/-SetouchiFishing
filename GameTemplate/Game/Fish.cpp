#include "stdafx.h"
#include "Fish.h"
#include "PositionSelection.h"
#include "InGameState.h"
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
	UpdateEscapeTimer();
}

bool Fish::Init()
{
	SetRandomIndividualFactor();
	OnInit();
	return true;
}

bool Fish::Start()
{

	FindGameObjects();
	m_initialTime = m_inGameState->GetTime();
	return true;
}

void Fish::SetRandomIndividualFactor()
{
	std::random_device rd;
	//個体値の倍率をランダムに決める。0.4%~1.2%の間で決まる。
	m_fishData.individualFactor = (0.4f / 100) * (rd() % 100 + 1);//??????{??
	m_fishData.individualFactor += 0.8;
}

void Fish::SetFishType(FishType fishtype)
{
	m_fishData.fishType = fishtype;;
}

void Fish::FindGameObjects()
{
	m_inGameState = FindGO<InGameState>("inGameState");
}


/// <summary>
/// ???l??????B
/// </summary>
/// <param name="baseIndividualValue"></param>
void Fish::SetScore()
{
	m_fishData.score = m_baseScore * m_fishData.individualFactor;//???X?R?A?~??????{???B
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
	
	if (fishDetectionRadius < 0) {
		fishDetectionRadius = 0;
	}

	if (fishDetectionRadius > 0.5) {
		fishDetectionRadius = 0.5;
	}
	m_fishData.fishDetectionRadius = fishDetectionRadius;
}

void Fish::SetEscapeForce(float escapeForce)
{
	m_fishData.escapeForce = escapeForce;
}

void Fish::SetUI(std::string filePath,Vector3 scale)
{
	m_ui.Init(filePath.c_str(), 150, 150);
	m_ui.SetPivot(Vector2(0.5f, 0.5f));
	m_ui.SetScale(scale);
	m_ui.Update();
}

void Fish::SetParameter(
	float timeUntilEscape,
	float arrowspeed, 
	float baseScore,
	float initpos,
	float upwardBias,
	float downwardBias,
	float fishDetectionRadius,
	float escapeForce)
{
	SetTimeUntilEscape(timeUntilEscape);
	SetArrowSpeed(arrowspeed);
	SetBaseScore(baseScore);
	SetScore();
	SetInitPos(initpos);
	SetUpWardBias(upwardBias);
	SetDownwardBias(downwardBias);
	SetFishDetectionRadius(fishDetectionRadius);
	SetEscapeForce(escapeForce);
}

void Fish::SetBuff(BuffType bufftype,float buffValue)
{
	m_fishData.buffEffect[bufftype] = buffValue* m_fishData.individualFactor;
}

/// <summary>
/// 魚が逃げるまでの時間を確認し、条件を満たせば変更フラグを立てる。
/// </summary>
/// <returns></returns>
void Fish::UpdateEscapeTimer()
{
	m_nowTime = m_inGameState->GetTime();

	//魚が逃げるまでの残り時間を計算する。
	m_timeRatio = ((m_initialTime-m_nowTime)/m_fishData.timeUntilEscape);

	if (m_initialTime - m_nowTime <= m_fishData.timeUntilEscape)
	{
	}
	if(m_initialTime - m_nowTime >= m_fishData.timeUntilEscape) {
		ShouldFishChangeTrue();
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
	m_shouldFishChange = true;
}

void Fish::ShouldFishChangeFalse()
{
	m_shouldFishChange = false;
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

