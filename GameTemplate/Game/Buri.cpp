#include "stdafx.h"
#include "Buri.h"

Buri::Buri()
{
	m_fishData.rarity = FishRarity::Rare;
}

Buri::~Buri() = default;

bool Buri::OnInit()
{
	SetFishType(FishType::BURI);
	SetTimeUntilEscape(10.0f);
	SetArrowSpeed(15.0f);
	SetBaseScore(500.0f);
	SetScore();
	SetInitPos(0.7);
	SetUpWardBias(50);
	SetDownwardBias(70);
	SetFishDetectionRadius(0.3);
	SetEscapeForce(0.008);

	SetUI("Assets/modelData/buriUI.DDS",Vector3::One * m_fishData.individualFactor);

	return true;
}