#include "stdafx.h"
#include "PlayFishing.h"
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
#include "HitUIState.h"
#include "FishDetectionRadius.h"
#include "InGameState.h"
#include"BackGround.h"
#include"FishModel.h"
#include "ScoreManager.h"










PlayFishing::PlayFishing()
{




}

PlayFishing::~PlayFishing()
{
	//カメラをもとに戻す。
	ReturnToPositionSelectCamera();

	DeleteGO(m_player);
	DeleteGO(m_fshModel);
	DeleteGO(m_gameCamera);
	DeleteGO(m_tensionGauge);


}

bool PlayFishing::Init()
{


	return true;
}

void PlayFishing::Update()
{
	//if (m_playCastGaugeState != nullptr) {
	//	if (m_playCastGaugeState->GetSuccessful_or_Failure() == success) {
	//		m_castState = NewGO<CastState>(0, "castState");
	//		DeleteGO(m_playCastGaugeState);
	//	};
	//}
	/*StatusManager();*/
	//SetRodFloatModalePosition();
}

bool PlayFishing::Start()
{
	FindGameObjects();
	SetFishData();
	NewGOGameObjects();



	//プレイヤーがコントローラーで動かないようにする。
	m_player->SetMoveDeActive();

	m_current_fish_range_and_max_range_rate = m_fishData.initPos;

	//ステートマネージャーを動かす。
	StatusManager();

	return true;
}

void PlayFishing::NewGOGameObjects()
{

	m_tensionGauge = NewGO<TensionGauge>(0, "tensionGauge");
	m_tensionGauge->Init();

	m_fishDetectionRadius = NewGO<FishDetectionRadius>(0, "fishDetectionRadius");
	m_fishDetectionRadius->Init();

	//魚のモデルを作成。
	m_fshModel = NewGO<FishModel>(0, "fishModel");
	m_fshModel->Init();

	m_player = NewGO<Player>(0, "player_Playfishing");
	m_player->Init();

	m_player->m_position = Vector3{ 0.0f,100.0f,250 };



}

void PlayFishing::InitNewGOGameObjects()
{



}


void PlayFishing::FindGameObjects()
{
	m_fishManager = FindGO<FishManager>(m_currentFishManagerobjectName.c_str());
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_backGround = FindGO<BackGround>("backGround");
	m_gameCamera = FindGO<GameCamera>("PlayFishing");
	m_scoreManager = FindGO<ScoreManager>("scoreManager");
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
	case hitUI:
		m_hitUIState = NewGO<HitUIState>(0, "hitUIState");
		break;
	case sceneFightFish:
		m_fightFishState = NewGO<FightFishState>(0, "fightFishState");
		break;
	default:
		break;
	}
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
		m_playFishingStatus = hitUI;
		StatusManager();

		break;
	case hitUI:
		DeleteGO(m_hitUIState);
		m_playFishingStatus = sceneFightFish;
		StatusManager();
		break;
	case sceneFightFish:
		DeleteGO(m_fightFishState);
		DeleteThisClass();
		m_scoreDisplay = NewGO<ScoreDisplay>(0, "scoreDisplay");

		break;
	default:
		break;
	}

}

void PlayFishing::Failure()
{

	switch (m_playFishingStatus)
	{
	case playCastGauge:
		DeleteGO(m_castGauge);
		m_shouldChangeScene = true;
		break;
	case castAnimasion:
		break;
	case cast:
		break;
	case wait_for_fish:
		m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
		m_rodFloatMove->DeleteThisClass();
		m_rodFloatMove = nullptr;
		m_playCastGaugeState=NewGO<PlayCastGaugeState>(0, "playCastGaugeState");
		DeleteGO(m_waitForFishState);
		m_playFishingStatus = playCastGauge;
		break;
	case sceneFightFish:
		DeleteGO(m_fightFishState);
		m_shouldChangeScene = true;

		break;
	default:

		break;
	}
	
	if (m_shouldChangeScene)
	{
		ChangeScene();
	}
}
void PlayFishing::ChangeScene()
{
	m_positionSelection->SetisDisplayingTrue();
	//ポジションセレクトクラスのオブジェクトをアクティブにする
	m_positionSelection->SetActivate();
	DeleteThisClass();
}

/// <summary>
/// ポジションセレクト画面のカメラの位置と
/// ターゲットにリセット。
/// </summary>
void PlayFishing::ReturnToPositionSelectCamera()
{
	m_gameCamera->SetPosition(m_backGround->m_shipPosition + Vector3{ 0.0f,1500.0f,0.0f });
	m_gameCamera->SetTarget(m_backGround->m_shipPosition + Vector3{ 0.0f,0.0f,100.0f });
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

/// <summary>
/// 魚の個体値に基づいて魚のスケールを設定
/// </summary>
/// <param name="scale"></param>
void PlayFishing::SetFishScaleByIndividualFactor()
{
	m_fshModel->SetScaleByIndividualFactor(m_fishData.individualFactor);
	m_tensionGauge->SetFishUIScaleByIndividualFactor(m_fishData.individualFactor);

}




void PlayFishing::DeleteThisClass()
{
	DeleteGO(this);
}








void PlayFishing::SetCurrentFishManagerObjectName(std::string string_objectName)
{
	//フィッシュマネージャーにつけるオブジェクトネームの設定。
	m_currentFishManagerobjectName= string_objectName;
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


/// <summary>
/// キャストの強さを設定。
/// </summary>
/// <param name="castStrength"></param>
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

