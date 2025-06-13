#include "stdafx.h"
#include "Jakoten.h"

Jakoten::Jakoten()
{
	m_fishData.rarity = FishRarity::Common;


}

Jakoten::~Jakoten()
{

}

bool Jakoten::OnInit()
{
	SetUI("Assets/modelData/jakotenUI.DDS", Vector3::One * m_fishData.individualFactor);
	SetFishType(FishType::JAKOTENN);
	SetTimeUntilEscape(15);
	SetArrowSpeed(5);
	SetBaseScore(100.0f);
	SetScore();
	SetInitPos(0.6);
	SetUpWardBias(40);
	SetDownwardBias(10);
	SetFishDetectionRadius(0.2);
	SetEscapeForce(0.004);
	//SetParameter(
	//	12.0f,
	//	5.0f,
	//	120.0f,
	//	0.7,
	//	80,
	//	30,
	//	0.3f
	//);
	SetBuff(BuffType::StaminaRegenBuff,1);
	return true;
}