#include "stdafx.h"
#include "Buri.h"

Buri::Buri()
{
	m_fishData.rarity = FishRarity::Rare;


}

Buri::~Buri()
{

}

bool Buri::OnInit()
{
	SetFishType(FishType::BURI);
	//SetParameter(10.0f, 5.0f, 100.0f, 0.6, 50, 50);
	SetTimeUntilEscape(10.0f);
	SetArrowSpeed(20.0f);
	SetBaseScore(300.0f);
	SetScore();
	SetInitPos(0.7);
	SetUpWardBias(50);
	SetDownwardBias(50);
	SetFishDetectionRadius(0.3);
	SetEscapeForce(0.01);

	SetUI("Assets/modelData/buriUI.DDS",Vector3::One * m_fishData.individualFactor);

	return true;
}