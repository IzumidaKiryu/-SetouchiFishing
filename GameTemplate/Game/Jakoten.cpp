#include "stdafx.h"
#include "Jakoten.h"

Jakoten::Jakoten()
{
	m_fishData.rarity = FishRarity::Common;


}

Jakoten::~Jakoten() = default;

bool Jakoten::OnInit()
{
	SetUI("Assets/modelData/jakotenUI.DDS", Vector3::One * m_fishData.individualFactor);
	SetFishType(FishType::JAKOTENN);
	SetTimeUntilEscape(15.0f);
	SetArrowSpeed(10.0f);
	SetBaseScore(100.0f);
	SetScore();
	SetInitPos(0.7);
	SetUpWardBias(45);
	SetDownwardBias(80);
	SetFishDetectionRadius(0.4);
	SetEscapeForce(0.004);
	SetBuff(BuffType::StaminaRegenBuff,1);
	return true;
}