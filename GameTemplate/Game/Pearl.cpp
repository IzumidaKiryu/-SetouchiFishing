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
	SetParameter(
		12.0f,
		5.0f,
		120.0f,
		0.7,
		80,
		30,
		0.3f
	);
	SetBuff(BuffType::PullStrengthBuff, 5);
	return true;
}
