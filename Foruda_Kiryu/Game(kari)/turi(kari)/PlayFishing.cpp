#include "stdafx.h"
#include "PlayFishing.h"
#include"PlayFishingBackGround.h"
#include "GameCamera.h"
#include "CastGauge.h"

PlayFishing::PlayFishing()
{
	m_playFishingBackGround = NewGO< PlayFishingBackGround>(0, "playFishingBackGround");
	CallCastGauge();

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
