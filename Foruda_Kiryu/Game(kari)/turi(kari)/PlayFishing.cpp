#include "stdafx.h"
#include "PlayFishing.h"
#include"PlayFishingBackGround.h"
#include "GameCamera.h"
#include "CastGauge.h"
#include "PositionSelection.h"
#include "FishManager.h"
#include "FishingGauge.h"
#include "TensionGauge.h"
#include "FishingRodHP.h"


PlayFishing::PlayFishing()
{
	m_objectName= new char[6];// フィッシュマネージャーのオブジェクトネームのメモリ確保

	m_playFishingBackGround = NewGO< PlayFishingBackGround>(0, "playFishingBackGround");
	//ゲームカメラのオブジェクトを作る。
	gameCamera = NewGO<GameCamera>(0, "gamecamera");

	StatusManager();
}

PlayFishing::~PlayFishing()
{
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_positionSelection->SetisDisplayingTrue();

	DeleteGO(m_playFishingBackGround);
	DeleteGO(gameCamera);
	DeleteGO(m_fishManager);

	//ポジションセレクトクラスのオブジェクトをアクティブにする
	m_positionSelection->SetActivate();
}

void PlayFishing::Update()
{

}

void PlayFishing::NewGOCastGauge()
{
	m_castGauge = NewGO< CastGauge>(0, "CastGauge");
}

void PlayFishing::NewGOFishingGauge()
{
	m_fishingGauge = NewGO< FishingGauge>(0, "fishingGauge");

}

void PlayFishing::NewGOTensionGauge()
{
	m_tensionGauge=NewGO< TensionGauge>(0, "tensionGauge");
}

void PlayFishing::DeleteThisClass()
{
	DeleteGO(this); 
}

void PlayFishing::SetFishManagerObjectName(std::string string_objectName)
{
	//フィッシュマネージャーにつけるオブジェクトネームの設定。
	std::char_traits<char>::copy(m_objectName, string_objectName.c_str(), string_objectName.size() + 1);
}

void PlayFishing::FindeFishManager()
{
	m_fishManager = FindGO<FishManager>(m_objectName);
}

void PlayFishing::StatusManager()
{
	switch (m_playFishingStatus)
	{
	case chastGauge:
		NewGOCastGauge();
		break;
	case fishingGsauge:
		DeleteGO(m_castGauge);
		NewGOFishingGauge();
		break;
	case tensionGauge:
		NewGOTensionGauge();
		NewGOFishingRodHP();
		break;
	default:
		break;
	}
}

void PlayFishing::NewGOFishingRodHP()
{
	if (canNewGOFishingRodHP == true) {
		m_fishingRodHP = NewGO<FishingRodHP>(0, "fishingRodHP");

	}
	canNewGOFishingRodHP = false;
}

void PlayFishing::SetSuccess()
{
	m_successful_or_failure = success;
	Success();
}

void PlayFishing::SetFailure()
{
	m_successful_or_failure = failure;
	Failure();
}

void PlayFishing::SetSuccessful_or_Failure_unfixed()
{
	m_successful_or_failure = unfixed;
}

void PlayFishing::Success()
{
	if (m_successful_or_failure == success) {
		switch (m_playFishingStatus)
		{
		case chastGauge:
			m_playFishingStatus = fishingGsauge;
			SetSuccessful_or_Failure_unfixed();//成功か失敗かどうかを未確定にする。
			StatusManager();//ステータスマネージャーを動かす。
			break;
		case fishingGsauge:
			m_playFishingStatus = tensionGauge;
			SetSuccessful_or_Failure_unfixed();//成功か失敗かどうかを未確定にする。;
			StatusManager();//ステータスマネージャーを動かす。
			break;
		case tensionGauge:
			DeleteGO(this);
			break;
		default:
			break;
		}
	}
}

void PlayFishing::Failure()
{
	if (m_successful_or_failure == failure) {
		switch (m_playFishingStatus)
		{
		case chastGauge:
			DeleteThisClass();
			DeleteGO(m_castGauge);
			break;
		case fishingGsauge:
			DeleteThisClass();
			DeleteGO(m_fishingGauge);
			break;
		case tensionGauge:
			DeleteThisClass();
			DeleteGO(m_tensionGauge);
			DeleteGO(m_fishingRodHP);
			break;
		default:
			break;
		}
	}
}

void PlayFishing::SetPlayFishingStatus_FishingGsauge()
{
	m_playFishingStatus = fishingGsauge;
}
