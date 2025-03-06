#include "stdafx.h"
#include "PlayFishing.h"
#include"PlayFishingBackGround.h"
#include "GameCamera.h"
#include "CastGauge.h"

PlayFishing::PlayFishing()
{
	m_playFishingBackGround = NewGO< PlayFishingBackGround>(0, "playFishingBackGround");
}

PlayFishing::~PlayFishing()
{
}

void PlayFishing::Update()
{
	CallCastGauge();
}

void PlayFishing::CallCastGauge()
{
	castGauge=NewGO< CastGauge>(0, "CastGauge");
}
