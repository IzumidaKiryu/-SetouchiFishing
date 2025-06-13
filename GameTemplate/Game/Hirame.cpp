#include "stdafx.h"
#include "Hirame.h"

Hirame::Hirame()
{
	m_fishData.rarity = FishRarity::Common;

}

Hirame::~Hirame()
{

}


bool Hirame::OnInit()
{
	SetFishType(FishType::HIRAME);
	SetTimeUntilEscape(15.0f);
	SetArrowSpeed(10.0f);
	SetBaseScore(100.0f);
	SetScore();
	SetInitPos(0.7);
	SetUpWardBias(60);
	SetDownwardBias(80);
	SetFishDetectionRadius(0.4);
	SetEscapeForce(0.005);
	SetUI("Assets/modelData/hirameUI.DDS",Vector3::One*m_fishData.individualFactor);
	SetBuff(BuffType::StealBoostBuff,0.01f);

	return true;
}