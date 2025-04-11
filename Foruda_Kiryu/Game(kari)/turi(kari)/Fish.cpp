#include "stdafx.h"
#include "Fish.h"
#include "PositionSelection.h"

Fish::Fish()
{
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	//m_initialTime= m_positionSelection->GetTime();
	srand(time(NULL));
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
void Fish::SetScore()
{
	//���̃X�R�A�Ɍ̍���o���B
	//���̃X�R�A�͊�̃X�R�A�~�i0.8����1.2�܂ł̃����_���Ȑ��j�Ōv�Z�����B
	float individualValueMagnification =( 0.4f / 100 )* (rand() % 100 + 1);//�̍��̔{��
	individualValueMagnification += 0.8;

	m_fishData.score = m_baseScore * individualValueMagnification;//��̃X�R�A�~�̍��̔{���B
}

/// <summary>
/// 逃げるまでの時間を設定する。
/// </summary>
/// <param name="timeUntilEscape"></param>
void Fish::SetTimeUntilEscape(float timeUntilEscape)
{
	m_fishData.timeUntilEscape = timeUntilEscape;
}

/// <summary>
/// 時間をはかる。
/// </summary>
/// <returns></returns>
bool Fish::TimeCount()
{
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_nowTime=m_positionSelection->GetTime();

		if (m_initialTime -m_nowTime >= m_fishData.timeUntilEscape)
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

