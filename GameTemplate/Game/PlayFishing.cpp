#include "stdafx.h"
#include "PlayFishing.h"
#include "GameCamera.h"
#include "CastGauge.h"
#include "PositionSelection.h"
#include "FishManager.h"
#include "TensionGauge.h"
#include "FishingRodHP.h"
#include "ScoreDisplay.h"
#include "Player.h"
#include "SceneFightFish.h"
#include "FishModel.h"
#include "RodFloatMove.h"
#include "PlayCastGaugeState.h"
#include "CastState.h"
#include "WaitForFishState.h"
#include "FightFishState.h"
#include "FishingAnimationState.h"
#include "HitUIState.h"
#include "SuccessUIState.h"
#include "FishDetectionRadius.h"
#include "InGameState.h"
#include "BackGround.h"
#include "ScoreManager.h"
#include"Enemy.h"
#include "FishCatchEffectState.h"
#include"StealPositionBar.h"
#include"BuffManager.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"



// コンストラクタ・デストラクタ
PlayFishing::PlayFishing() {
}

PlayFishing::~PlayFishing()
{
	ReturnToPositionSelectCamera();
	DeleteGO(playerVisual);
	DeleteGO(m_fshModel);
	DeleteGO(m_gameCamera);
	DeleteGO(m_tensionGauge);
}

// 初期化（軽いリソースなど）
bool PlayFishing::Init() {
	return true;
}

// Start: 他オブジェクトに依存する初期化を行う
bool PlayFishing::Start()
{
	FindGameObjects();
	SetFishData();
	NewGOGameObjects();
	playerVisual->SetMoveDeActive();
	m_current_fish_range_and_max_range_rate = m_fishData.initPos;
	StatusManager();
	return true;
}

// 毎フレーム処理
void PlayFishing::Update() {
	// float_to_water(); を入れて浮き演出を動かすのも可
	// StatusManager(); は毎フレーム呼ぶものではないので除外
}

// 成功・失敗の切り替え
void PlayFishing::SetSuccess() {
	m_successful_or_failure = success;
	Success();
}

void PlayFishing::SetFailure() {
	m_successful_or_failure = failure;
	Failure();
}

// 魚データの受け取り
void PlayFishing::SetFishData() {
	p_fishData = &(m_fishManager->GetFishData());
	m_fishData = *p_fishData;
}

// 各種セッター
void PlayFishing::SetCurrentFishManagerObjectName(std::string string_objectName) {
	m_currentFishManagerobjectName = string_objectName;
}

void PlayFishing::SetCurrent_range_and_max_range_rate(float range_of_fish_and_ship) {
	m_current_fish_range_and_max_range_rate = range_of_fish_and_ship;
}

void PlayFishing::SetRange_of_fish_and_float(float range_of_fish_and_float) {
	m_current_float_range_max_range_rate = range_of_fish_and_float;
}

void PlayFishing::SetCastStrength(float castStrength) {
	m_castStrength = castStrength;
}

void PlayFishing::SetFishScaleByIndividualFactor() {
	m_fshModel->SetScaleByIndividualFactor(m_fishData.individualFactor);
	m_tensionGauge->SetFishUIScaleByIndividualFactor(m_fishData.individualFactor);
}

// カメラやシーン切り替え
void PlayFishing::ReturnToPositionSelectCamera() {
	m_gameCamera->SetPosition(m_backGround->m_shipPosition + Vector3{ 0.0f,1500.0f,0.0f });
	m_gameCamera->SetTarget(m_backGround->m_shipPosition + Vector3{ 0.0f,0.0f,100.0f });
}

void PlayFishing::ChangeScene() {
	m_positionSelection->SetisDisplayingTrue();
	m_positionSelection->SetActivate();
	DeleteThisClass();
}

void PlayFishing::DeleteThisClass() {
	DeleteGO(this);
}

// ゲッター
FishData& PlayFishing::GetFishData() {
	return m_fishData;
}

float PlayFishing::GetFIshScore() {
	return m_fishData.score;
}

PlayFishingStatus PlayFishing::GetPlayFishingStatus() const
{
	return m_playFishingStatus;
}

// ゲームオブジェクトの検索
void PlayFishing::FindGameObjects() {
	m_inGameState = FindGO<InGameState>("inGameState");
	m_fishManager = FindGO<FishManager>(m_currentFishManagerobjectName.c_str());
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_backGround = FindGO<BackGround>("backGround");
	m_gameCamera = FindGO<GameCamera>("PlayFishing");
	m_scoreManager = FindGO<ScoreManager>("scoreManager");
	m_enemy = FindGO<Enemy>("enemy");
	m_player = FindGO<Player>("player");
	m_stealPositionBar = FindGO<StealPositionBar>("stealPositionBar");
	m_buffManager = FindGO<BuffManager>("buffManager");
}

// NewGOで必要オブジェクトの生成
void PlayFishing::NewGOGameObjects() {
	m_tensionGauge = NewGO<TensionGauge>(0, "tensionGauge");
	m_tensionGauge->Init();

	m_fishDetectionRadius = NewGO<FishDetectionRadius>(0, "fishDetectionRadius");
	m_fishDetectionRadius->Init();

	m_fshModel = NewGO<FishModel>(0, "fishModel");
	m_fshModel->Init();

	playerVisual = NewGO<Player>(0, "player_Playfishing");
	playerVisual->Init();
	playerVisual->m_position = Vector3{ 0.0f,100.0f,250 };
}

// ステートマネージャー
void PlayFishing::StatusManager() {
	switch (m_playFishingStatus) {
	case playCastGauge:
		m_playCastGaugeState = NewGO<PlayCastGaugeState>(0, "playCastGaugeState");
		m_playCastGaugeState->Init();
		break;
	case castAnimasion:
		m_fishingAnimationState = NewGO<FishingAnimationState>(0, "fishingAnimationState");
		m_fishingAnimationState->Init();
		break;
	case cast:
		m_castState = NewGO<CastState>(0, "castState");
		m_castState->Init();
		break;
	case successUI:
		m_successUIState = NewGO<SuccessUIState>(0, "successUIState");
		m_successUIState->Init();
		break;
	case wait_for_fish:
		m_waitForFishState = NewGO<WaitForFishState>(0, "waitForFishState");
		m_waitForFishState->Init();
		break;
	case hitUI:
		m_hitUIState = NewGO<HitUIState>(0, "hitUIState");
		m_hitUIState->Init();
		break;
	case sceneFightFish:
		m_fightFishState = NewGO<FightFishState>(0, "fightFishState");
		m_fightFishState->Init();
		break;
	case fishCatch:
		m_fishCatchEffectState = NewGO<FishCatchEffectState>(0, "fishCatchEffectState");
		m_fishCatchEffectState->WitchFishType(m_fishData.fishType);
		m_fishCatchEffectState->Init();
	
	default:
		break;
	}
}

// 成功時のステート遷移
void PlayFishing::Success() {
	switch (m_playFishingStatus) {
	case playCastGauge:
		DeleteGO(m_playCastGaugeState);
		m_playFishingStatus = castAnimasion;
		StatusManager();
		break;
	case castAnimasion:
		g_soundEngine->ResistWaveFileBank(4, "Assets/sound/castingRod.wav");

		m_sound = NewGO<SoundSource>(4);

		m_sound->Init(4);

		m_sound->Play(false);
		DeleteGO(m_fishingAnimationState);
		m_playFishingStatus = cast;
		StatusManager();
		break;
	case cast:
		g_soundEngine->ResistWaveFileBank(6, "Assets/sound/reelCoiling.wav");

		m_sound = NewGO<SoundSource>(6);

		m_sound->Init(6);

		m_sound->Play(false);
		DeleteGO(m_castState);
		m_playFishingStatus = successUI;
		StatusManager();
		break;
	case successUI:
		g_soundEngine->ResistWaveFileBank(12, "Assets/sound/niceVoice.wav");

		m_sound = NewGO<SoundSource>(12);

		m_sound->Init(12);

		m_sound->Play(false);
		DeleteGO(m_successUIState);
		m_playFishingStatus = wait_for_fish;
		StatusManager();
		break;
	case wait_for_fish:
		DeleteGO(m_waitForFishState);
		m_playFishingStatus = hitUI;
		StatusManager();
		break;
	case hitUI:
		g_soundEngine->ResistWaveFileBank(5, "Assets/sound/fishFaight.wav");

		m_sound = NewGO<SoundSource>(5);

		m_sound->Init(5);

		m_sound->Play(false);
		DeleteGO(m_hitUIState);
		m_playFishingStatus = sceneFightFish;
		StatusManager();
		break;
	case sceneFightFish:

		DeleteGO(m_fightFishState);
		m_playFishingStatus = fishCatch;
		StatusManager();
		//バフをバフマネジェーに渡す。
		m_buffManager->ApplyBuffEffect(m_fishManager->GetBuffEffect(), m_fishManager->GetBuffType());
		break;
		case fishCatch:
			g_soundEngine->ResistWaveFileBank(3, "Assets/sound/fishFinish.wav");

			m_sound = NewGO<SoundSource>(3);

			m_sound->Init(3);

			m_sound->Play(false);
			DeleteGO(m_fishCatchEffectState);
			m_scoreManager->SetScore(m_fishData.score, m_fishData.fishType, CharacterType::Player);
			m_inGameState->NewGOScoreDisplay(m_fishData.fishType);

			break;

	}
}

// 失敗時の処理
void PlayFishing::Failure() {
	switch (m_playFishingStatus) {
	case playCastGauge:
		m_shouldChangeScene = true;
		break;
	case cast:
		m_player->EndCastAnimation();
	case wait_for_fish:
		g_soundEngine->ResistWaveFileBank(11, "Assets/sound/failureVoice.wav");

		m_sound = NewGO<SoundSource>(11);

		m_sound->Init(11);

		m_sound->Play(false);
		m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
		m_rodFloatMove->DeleteThisClass();
		m_rodFloatMove = nullptr;
		m_playCastGaugeState = NewGO<PlayCastGaugeState>(0, "playCastGaugeState");
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
	if (m_shouldChangeScene) {//シーンを変えてもいいなら。

		//魚のロックをoffにする。
		//敵からエリアを奪った場合、魚にロックがかかっていて、逃げないので、ロックをoffにする。
		//別の場所でロックがかかっていても、有効。
		//ロックがかかっていなくても問題はない。
		m_stealPositionBar->SetIsStealLockActive(false);


		//プレイヤーが釣りをしていないと伝える。
		m_player->SetIsFishingInArea(false);

		//魚をチェンジ。
		m_inGameState->ChangeFish(static_cast<int>(m_positionSelection->GetCurrentArea()));

		ChangeScene();
	}
}

// 浮きの演出の上下動
void PlayFishing::float_to_water() {
	m_floating_t += 0.05f;
	m_floating.y = cos(m_floating_t * 0.9f) * 3.0f;
	m_floating.z = cos(m_floating_t * 0.7f) * 5.0f;
	// Update に入れることで毎フレーム浮かせる演出として活用できる
}
