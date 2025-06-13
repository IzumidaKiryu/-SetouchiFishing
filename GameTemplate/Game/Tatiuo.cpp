#include "stdafx.h"
#include "Tatiuo.h"

Tatiuo::Tatiuo()
{
	m_fishData.rarity = FishRarity::Rare;
}

Tatiuo::~Tatiuo()
{
}

bool Tatiuo::OnInit()
{
	SetUI("Assets/modelData/tatiuo.DDS",Vector3::One * m_fishData.individualFactor);
	SetFishType(FishType::TATIUO);
	SetParameter(
		12.0f,
		5.0f,
		120.0f,
		0.7,
		80,
		30,
		0.3f
	);
	return true;
}