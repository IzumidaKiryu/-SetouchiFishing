#include "stdafx.h"
#include "PlayFishing.h"
#include"PlayFishingBackGround.h"
#include "GameCamera.h"
#include "CastGauge.h"
#include "PositionSelection.h"


PlayFishing::PlayFishing()
{
	m_playFishingBackGround = NewGO< PlayFishingBackGround>(0, "playFishingBackGround");
	//ゲームカメラのオブジェクトを作る。
	gameCamera = NewGO<GameCamera>(0, "gamecamera");
	CallCastGauge();
}

PlayFishing::~PlayFishing()
{
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_positionSelection->SetisDisplayingTrue();

	DeleteGO(m_playFishingBackGround);
	DeleteGO(m_castGauge);
	DeleteGO(gameCamera);

	//ポジションセレクトクラスのオブジェクトをアクティブにする
	m_positionSelection->SetActivate();
}

void PlayFishing::Update()
{
}

void PlayFishing::CallCastGauge()
{
	m_castGauge = NewGO< CastGauge>(0, "CastGauge");
}

void PlayFishing::DeleteThisClass()
{
	DeleteGO(this);
}
