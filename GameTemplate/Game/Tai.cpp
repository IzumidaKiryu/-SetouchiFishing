#include "stdafx.h"
#include "Tai.h"



Tai::Tai()
{
	m_fishData.rarity=FishRarity::SuperRare;
}

Tai::~Tai()
{

}

bool Tai::OnInit()
{
	SetUI("Assets/modelData/taiUI.DDS",Vector3::One*m_fishData.individualFactor);
	SetTimeUntilEscape(30.0f);
	SetArrowSpeed(20.0f);
	SetBaseScore(1500.0f);
	SetScore();
	SetInitPos(0.7);
	SetUpWardBias(80);
	SetDownwardBias(20);
	SetFishDetectionRadius(0.3);
	SetEscapeForce(0.008);
	return true;
}
