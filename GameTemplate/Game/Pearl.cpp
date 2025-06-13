#include "stdafx.h"
#include "Pearl.h"

Pearl::Pearl()
{
	m_fishData.rarity = FishRarity::Common;

}

Pearl::~Pearl()
{
}

bool Pearl::OnInit()
{
	SetUI("Assets/modelData/sinnjuUI.DDS", Vector3::One * m_fishData.individualFactor);
	SetFishType(FishType::SINJU);
	SetTimeUntilEscape(15.0f);
	SetArrowSpeed(10.0f);
	SetBaseScore(100.0f);
	SetScore();
	SetInitPos(0.7);
	SetUpWardBias(60);
	SetDownwardBias(60);
	SetFishDetectionRadius(0.4);
	SetEscapeForce(0.005);
	SetBuff(BuffType::PullStrengthBuff, 5);
	return true;
}
