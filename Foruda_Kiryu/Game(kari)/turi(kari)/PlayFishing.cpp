#include "stdafx.h"
#include "PlayFishing.h"
#include"PlayFishingBackGround.h"
#include "GameCamera.h"
#include "CastGauge.h"
#include"FishingGauge.h"
#include "PositionSelection.h"


PlayFishing::PlayFishing()
{
	m_playFishingBackGround = NewGO< PlayFishingBackGround>(0, "playFishingBackGround");
	CallCastGauge();

}

PlayFishing::~PlayFishing()
{
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_positionSelection->SetisDisplayingTrue();

	DeleteGO(m_playFishingBackGround);
	DeleteGO(m_castGauge);
}

void PlayFishing::Update()
{
}

void PlayFishing::CallCastGauge()
{
	m_castGauge = NewGO< CastGauge>(0, "CastGauge");
}
}
