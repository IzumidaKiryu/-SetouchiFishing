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



PlayFishing::PlayFishing()
{


	m_objectName = new char[6];// フィッシュマネージャーのオブジェクトネームのメモリ確保

	m_playFishingBackGround = NewGO< PlayFishingBackGround>(0, "playFishingBackGround");
	//ゲームカメラのオブジェクトを作る。
	gameCamera = NewGO<GameCamera>(0, "PlayFishing_GameCamera");

	//魚のモデルを作成。
	m_fshModel= NewGO<FishModel>(0,"fshModel");

	//ウキを作成。
	m_rodFloatMove = NewGO<RodFloatMove>(0, "rodFloatMove");


	//m_player= NewGO<Player>(0, "player_Playfishing");

	//m_playFishingStatus = sceneFightFish;

	StatusManager();
	m_rodFloatMove->SetPosition(m_rodFloatPosition);
}

PlayFishing::~PlayFishing()
{
	//DeleteGO(m_player);
	DeleteGO(m_fshModel);
	DeleteGO(m_playFishingBackGround);
	DeleteGO(gameCamera);
	DeleteGO(m_rodFloatMove);
	//DeleteGO(m_fishManager);

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
}

void PlayFishing::Update()
{
	StatusManager();
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
	case castGauge:
		NewGOCastGauge();
		m_playFishingStatus = wait_castGauge;
	case wait_castGauge:
		float_to_water();
		m_rodFloatMove->SetSumPosition(Vector3 {0.0f,500.0f,0.0f});
		gameCamera->SetTarget(/*m_rodFloatMove->m_rodFloatPosition*/Vector3{0.0f,0.0f,500.0f}+ m_floating);
		//gameCamera->SetPosition(m_player->m_position+Vector3{0.0f,100.0f,100.0f});

		break;
	case cast:
		Cast();
		/*SetRodFloatModalePosition();*/
		gameCamera->SetTarget(m_rodFloatMove->m_rodFloatPosition);
		break;
	case wait_for_fish:
		
		/*float_to_water();*/
		gameCamera->SetTarget(m_rodFloatMove->m_rodFloatPosition);
		WaitForFish();
		/*SetRodFloatModalePosition();*/
		break;
		//case fishingGsauge:
		//	/*DeleteGO(m_castGauge);*/
		//	NewGOFishingGauge();
		//	break;
	case sceneFightFish:
		m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");

		NewGOSceneFightFish();
		NewGOFishingRodHP();
		m_playFishingStatus = wait_ceneFightFish;
	case wait_ceneFightFish:
		m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
		m_sceneFightFish = FindGO<SceneFightFish>("sceneFightFish");

		//m_rodFloatMove->SetCurrent_range_and_max_range_rate(m_current_fish_range_and_max_range_rate);
	default:
		break;
	}
}

void PlayFishing::Success()
{
	if (m_successful_or_failure == success) {
		switch (m_playFishingStatus)
		{
		case wait_castGauge:
			DeleteGO(m_castGauge);
			m_playFishingStatus = /*fishingGsauge*/cast;
			m_successful_or_failure = unfixed;//成功か失敗かどうかを未確定にする。
			StatusManager();//ステータスマネージャーを動かす。
			break;
		case castAnimasion:
			m_successful_or_failure = unfixed;
			m_playFishingStatus = cast;
			StatusManager();
			break;
		case cast:
			m_successful_or_failure = unfixed;//成功か失敗かどうかを未確定にする。
			/*m_playFishingStatus = wait_for_fish;*/
			m_playFishingStatus = wait_for_fish;
			break;
		case wait_for_fish:
			m_successful_or_failure = unfixed;//成功か失敗かどうかを未確定にする。
			m_playFishingStatus = sceneFightFish;
			break;
		case wait_ceneFightFish:
			DeleteGO(m_sceneFightFish);
			DeleteGO(m_fishingRodHP);
			m_positionSelection = FindGO<PositionSelection>("positionSelection");
			m_positionSelection->SetTotalValue(m_fishData.score);
			//スコアディスプレイに移動する。
			m_scoreDisplay = NewGO<ScoreDisplay>(0, "scoreDisplay");
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
		case castGauge:
			DeleteGO(m_castGauge);
			break;
		case castAnimasion:
			break;
		case cast:
			break;
		case wait_ceneFightFish:
			DeleteGO(m_sceneFightFish);
			DeleteGO(m_fishingRodHP);
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
}














void PlayFishing::Cast()
{
	m_casting_t +=0.1;
	m_rodFloatPosition = m_float_initPos + (first_velocity_vector * 100 * m_scalar_multiply_in_first_velocity_vector * m_casting_t) + g * m_casting_t * m_casting_t * 1 / 2;
	CalculateCurrent_float_range_and_max_range_rate();
	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
	m_rodFloatMove->SetPosition(m_rodFloatPosition);
	if (m_rodFloatPosition.y <= water_surface_position_y) {

		SetSuccess();
	}
}

void PlayFishing::WaitForFish()
{
	if (m_current_fish_range_and_max_range_rate > m_current_float_range_max_range_rate) {
		m_current_fish_range_and_max_range_rate -= 0.001;
		if (m_current_fish_range_and_max_range_rate - m_current_float_range_max_range_rate<=0) {
			SetSuccess();
		}
	}

	if (m_current_fish_range_and_max_range_rate < m_current_float_range_max_range_rate) {
		m_current_fish_range_and_max_range_rate += 0.001;
		if (m_current_float_range_max_range_rate - m_current_fish_range_and_max_range_rate <= 0) {
			SetSuccess();
		}
	}
	/*float a = m_current_fish_range_and_max_range_rate - m_current_float_range_max_range_rate;
	if (a<=0.001|| a>= -0.001) {
		SetSuccess();
	}*/
}

//void PlayFishing::SetRodFloatModalePosition()
//{
//	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
//	m_rodFloatMove->SetPosition(m_rodFloatPosition);
//}

/// <summary>
/// 水に浮かんでいるように動かす。
/// </summary>
void PlayFishing::float_to_water()
{
	m_floating_t += 0.05;
	m_floating.y = (cos(m_floating_t*0.9)) * 3;//上下に動かす
	m_floating.z = (cos(m_floating_t * 0.7/*周期をずらす*/) * 5);//左右に動かす
	/*m_rodFloatPosition = m_rodFloatPosition + m_floating;*/
}

/// <summary>
/// ウキの距離と最大距離の割合を計算。
/// ウキモデルのポジションからウキの距離と最大距離の割合を求める。
/// </summary>
void PlayFishing::CalculateCurrent_float_range_and_max_range_rate()
{
	m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");

	//割合を求める
	 m_current_float_range_max_range_rate=m_rodFloatMove->m_rodFloatPosition.z / m_rodFloatMove->m_limit_range_with_ship;
}





void PlayFishing::NewGOFishingRodHP()
{
	if (canNewGOFishingRodHP == true) {
		m_fishingRodHP = NewGO<FishingRodHP>(0, "fishingRodHP");

	}
	canNewGOFishingRodHP = false;
}
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


void PlayFishing::SetScalar_multiply_in_first_velocity_vector(float scalar_multiply_in_first_velocity_vector)
{
	m_scalar_multiply_in_first_velocity_vector = scalar_multiply_in_first_velocity_vector;
}







FishData& PlayFishing::GetFishData()
{
	return m_fishData;
}

float PlayFishing::GetFIshScore()
{
	return m_fishData.score;
}

float PlayFishing::GetRange_of_fish_and_ship()
{
	return m_current_fish_range_and_max_range_rate;
}

float PlayFishing::GetRange_of_fish_and_float()
{
	return m_current_float_range_max_range_rate;
}

