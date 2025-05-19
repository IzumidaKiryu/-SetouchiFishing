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
#include "ScoreDisplay.h"
#include"Player.h"
#include"SceneFightFish.h"
#include "FishModel.h"
#include"RodFloatMove.h";
#include "PlayCastGaugeState.h"
#include "CastState.h"
#include "WaitForFishState.h"
#include "FightFishState.h"
#include "FishingAnimationState.h"






PlayFishing::PlayFishing()
{
	

	m_objectName = new char[6];// フィッシュマネージャーのオブジェクトネームのメモリ確保

	m_playFishingBackGround = NewGO< PlayFishingBackGround>(0, "playFishingBackGround");
	//ゲームカメラのオブジェクトを作る。
	gameCamera = NewGO<GameCamera>(0, "PlayFishing_GameCamera");

	//魚のモデルを作成。
	m_fshModel = NewGO<FishModel>(0, "fishModel");

	////ウキを作成。
	//m_rodFloatMove = NewGO<RodFloatMove>(0, "rodFloatMove");


	m_player = NewGO<Player>(0, "player_Playfishing");
	m_player->m_position = Vector3{ 0.0f,100.0f,250 };
	//プレイヤーがコントローラーで動かないようにする。
	m_player->SetMoveDeActive();

	//m_playFishingStatus = sceneFightFish;

	//StatusManager();
	/*m_rodFloatMove->SetPosition(m_rodFloatPosition);*/

}

PlayFishing::~PlayFishing()
{
	DeleteGO(m_player);
	DeleteGO(m_fshModel);
	DeleteGO(m_playFishingBackGround);
	DeleteGO(gameCamera);
	//DeleteGO(m_fishManager);
	DeleteGO(m_tensionGauge);
	m_positionSelection = FindGO<PositionSelection>("positionSelection");

}

void PlayFishing::Init()
{
	//フィッシュマネージャーを探す。
	FindeFishManager();

	SetFishData();

	m_tensionGauge = NewGO<TensionGauge>(0, "tensionGauge");
	m_current_fish_range_and_max_range_rate = m_fishData.initPos;

	/*m_tensionGauge->SetFishUI_Position(m_fishData.initPos);*/
	StatusManager();
}

void PlayFishing::Update()
{
	if (m_playCastGaugeState != nullptr) {
		if (m_playCastGaugeState->GetSuccessful_or_Failure() == success) {
			m_castState = NewGO<CastState>(0, "castState");
			DeleteGO(m_playCastGaugeState);
		};
	}
	/*StatusManager();*/
	//SetRodFloatModalePosition();
}

/// <summary>
/// シーンの推移。
/// このクラスの一番初めか、成功か失敗したときに動かす。
/// </summary>
void PlayFishing::StatusManager()
{
	switch (m_playFishingStatus)
	{
	case playCastGauge:
		m_playCastGaugeState = NewGO<PlayCastGaugeState>(0, "playCastGaugeState");

		break;
	case castAnimasion:
		m_fishingAnimationState = NewGO<FishingAnimationState>(0, "fishingAnimationState");

		break;
	case cast:
		m_castState = NewGO<CastState>(0, "castState");

		break;
	case wait_for_fish:
		m_waitForFishState = NewGO<WaitForFishState>(0, "waitForFishState");
		break;
	case sceneFightFish:
		m_fightFishState = NewGO<FightFishState>(0, "fightFishState");
		break;
	default:
		break;
	}
	//switch (m_playFishingStatus)
	//{
	//case castGauge:
	//	NewGOCastGauge();
	//	m_playFishingStatus = wait_castGauge;
	//case wait_castGauge:
	//	float_to_water();
	//	m_rodFloatMove->SetSumPosition(Vector3 {0.0f,500.0f,0.0f});
	//	gameCamera->SetTarget(/*m_rodFloatMove->m_rodFloatPosition*/Vector3{0.0f,0.0f,500.0f}+ m_floating);
	//	//gameCamera->SetPosition(m_player->m_position+Vector3{0.0f,100.0f,100.0f});

	//	break;
	//case cast:
	//	Cast();
	//	/*SetRodFloatModalePosition();*/
	//	gameCamera->SetTarget(m_rodFloatMove->m_position);
	//	break;
	//case wait_for_fish:
	//	
	//	/*float_to_water();*/
	//	gameCamera->SetTarget(m_rodFloatMove->m_position);
	//	WaitForFish();
	//	/*SetRodFloatModalePosition();*/
	//	break;
	//	//case fishingGsauge:
	//	//	/*DeleteGO(m_castGauge);*/
	//	//	NewGOFishingGauge();
	//	//	break;
	//case sceneFightFish:
	//	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");

	//	NewGOSceneFightFish();
	//	NewGOFishingRodHP();
	//	m_playFishingStatus = wait_ceneFightFish;
	//case wait_ceneFightFish:
	//	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
	//	m_sceneFightFish = FindGO<SceneFightFish>("sceneFightFish");

	//	//m_rodFloatMove->SetCurrent_range_and_max_range_rate(m_current_fish_range_and_max_range_rate);
	//default:
	//	break;
	//}
}

void PlayFishing::Success()
{


	switch (m_playFishingStatus)
	{
	case playCastGauge:
		DeleteGO(m_playCastGaugeState);
		m_playFishingStatus = castAnimasion;
		StatusManager();
		break;
	case castAnimasion:
		DeleteGO(m_fishingAnimationState);
		m_playFishingStatus = cast;
		StatusManager();
		break;
	case cast:
		DeleteGO(m_castState);
		m_playFishingStatus = wait_for_fish;
		StatusManager();
		break;
	case wait_for_fish:
		DeleteGO(m_waitForFishState);
		m_playFishingStatus = sceneFightFish;
		StatusManager();

		break;
	case sceneFightFish:
		DeleteGO(m_fightFishState);
		DeleteThisClass();
		m_positionSelection = FindGO<PositionSelection>("positionSelection");
		m_positionSelection->SetTotalValue(m_fishData.score);
		m_scoreDisplay = NewGO<ScoreDisplay>(0, "scoreDisplay");

		break;
	default:
		break;
	}
	//if (m_successful_or_failure == success) {
	//	switch (m_playFishingStatus)
	//	{
	//	case wait_castGauge:
	//		DeleteGO(m_castGauge);
	//		m_playFishingStatus = /*fishingGsauge*/cast;
	//		m_successful_or_failure = unfixed;//成功か失敗かどうかを未確定にする。
	//		StatusManager();//ステータスマネージャーを動かす。
	//		break;
	//	case castAnimasion:
	//		m_successful_or_failure = unfixed;
	//		m_playFishingStatus = cast;
	//		StatusManager();
	//		break;
	//	case cast:
	//		m_successful_or_failure = unfixed;//成功か失敗かどうかを未確定にする。
	//		/*m_playFishingStatus = wait_for_fish;*/
	//		m_playFishingStatus = wait_for_fish;
	//		break;
	//	case wait_for_fish:
	//		m_successful_or_failure = unfixed;//成功か失敗かどうかを未確定にする。
	//		m_playFishingStatus = sceneFightFish;
	//		break;
	//	case wait_ceneFightFish:
	//		DeleteGO(m_sceneFightFish);
	//		DeleteGO(m_fishingRodHP);
	//		m_positionSelection = FindGO<PositionSelection>("positionSelection");
	//		m_positionSelection->SetTotalValue(m_fishData.score);
	//		//スコアディスプレイに移動する。
	//		m_scoreDisplay = NewGO<ScoreDisplay>(0, "scoreDisplay");
	//		DeleteGO(this);
	//		break;
	//	default:
	//		break;
	//	}
	//}
}

void PlayFishing::Failure()
{
	switch (m_playFishingStatus)
	{
	case playCastGauge:
		DeleteGO(m_castGauge);
		break;
	case castAnimasion:
		break;
	case cast:
		break;
	case sceneFightFish:
		DeleteGO(m_fightFishState);
		break;
	default:

		break;
	}
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_positionSelection->SetisDisplayingTrue();
	//ポジションセレクトクラスのオブジェクトをアクティブにする
	m_positionSelection->SetActivate();
	DeleteThisClass();

}














/// <summary>
/// 水に浮かんでいるように動かす。
/// </summary>
void PlayFishing::float_to_water()
{
	m_floating_t += 0.05;
	m_floating.y = (cos(m_floating_t * 0.9)) * 3;//上下に動かす
	m_floating.z = (cos(m_floating_t * 0.7/*周期をずらす*/) * 5);//左右に動かす
	/*m_rodFloatPosition = m_rodFloatPosition + m_floating;*/
}

///// <summary>
///// ウキの距離と最大距離の割合を計算。
///// ウキモデルのポジションからウキの距離と最大距離の割合を求める。
///// </summary>
//void PlayFishing::CalculateCurrent_float_range_and_max_range_rate()
//{
//	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
//
//	//割合を求める
//	 m_current_float_range_max_range_rate=m_rodFloatMove->m_position.z / m_rodFloatMove->m_limit_range_with_ship;
//}



//
//
//void PlayFishing::NewGOFishingRodHP()
//{
//	if (canNewGOFishingRodHP == true) {
//		m_fishingRodHP = NewGO<FishingRodHP>(0, "fishingRodHP");
//
//	}
//	canNewGOFishingRodHP = false;
//}
void PlayFishing::NewGOCastGauge()
{
	m_castGauge = NewGO<CastGauge>(0, "CastGauge");
}

void PlayFishing::NewGOFishingGauge()
{
	m_fishingGauge = NewGO< FishingGauge>(0, "fishingGauge");

}

void PlayFishing::NewGOSceneFightFish()
{
	m_sceneFightFish = NewGO<SceneFightFish>(0, "sceneFightFish");
}


void PlayFishing::FindeFishManager()
{
	m_fishManager = FindGO<FishManager>(m_objectName);
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


/// <summary>
/// 成功したら各クラスでこのメソッドを呼ぶ。
/// 呼ぶと自動的に次のステートへ行く準備（いらないクラスを消したり）をして、次のステートへ進む。
/// </summary>
void PlayFishing::SetSuccess()
{
	m_successful_or_failure = success;
	Success();
}

/// <summary>
/// 失敗したら各クラスでこのメソッドを呼ぶ。
/// </summary>
void PlayFishing::SetFailure()
{
	m_successful_or_failure = failure;
	Failure();
}

void PlayFishing::SetFishData()
{
	p_fishData = &(m_fishManager->GetFishData());
	m_fishData = *p_fishData;
}


void PlayFishing::SetCurrent_range_and_max_range_rate(float range_of_fish_and_ship)
{
	m_current_fish_range_and_max_range_rate = range_of_fish_and_ship;
}


void PlayFishing::SetRange_of_fish_and_float(float range_of_fish_and_float)
{
	m_current_float_range_max_range_rate = range_of_fish_and_float;
}


void PlayFishing::SetCastStrength(float castStrength)
{
	m_castStrength = castStrength;
}







FishData& PlayFishing::GetFishData()
{
	return m_fishData;
}

float PlayFishing::GetFIshScore()
{
	return m_fishData.score;
}

