#include "stdafx.h"
#include "PlayFishing.h"
#include"PlayFishingBackGround.h"
#include "GameCamera.h"
#include "CastGauge.h"
#include"FishingGauge.h"

PlayFishing::PlayFishing()
{
	m_playFishingBackGround = NewGO< PlayFishingBackGround>(1, "playFishingBackGround");
	CallCastGauge();
	CallFishingGauge();

}

PlayFishing::~PlayFishing()
{
}

void PlayFishing::Update()
{
}

void PlayFishing::CallCastGauge()
{
	castGauge = NewGO< CastGauge>(0, "CastGauge");
}

void PlayFishing::CallFishingGauge()
{
	fishingGauge = NewGO<FishingGauge>(1, "FishingGauge");
}
