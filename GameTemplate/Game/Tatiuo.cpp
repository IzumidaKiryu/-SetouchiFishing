#include "stdafx.h"
#include "Tatiuo.h"

Tatiuo::Tatiuo()
{
	m_fishData.rarity = FishRarity::Rare;
}

Tatiuo::~Tatiuo() = default;

bool Tatiuo::OnInit()
{
	SetUI("Assets/modelData/tatiuo.DDS",Vector3::One * m_fishData.individualFactor);
	SetFishType(FishType::TATIUO);
	SetTimeUntilEscape(10.0f);
	SetArrowSpeed(15.0f);
	SetBaseScore(500.0f);
	SetScore();
	SetInitPos(0.7);
	SetUpWardBias(80);
	SetDownwardBias(20);
	SetFishDetectionRadius(0.3);
	SetEscapeForce(0.004);
	return true;
}