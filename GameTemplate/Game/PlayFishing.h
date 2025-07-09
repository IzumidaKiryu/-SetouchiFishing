#pragma once
#include "Fish.h"
#include "sound/SoundSource.h"

// ==============================
// ステートと成功/失敗状態
// ==============================
enum PlayFishingStatus {
	playCastGauge,
	wait_castGauge,
	castAnimasion,
	cast,
	successUI,
	wait_for_fish,
	hitUI,
	sceneFightFish,
	wait_ceneFightFish,
	fishCatch
};

enum Successful_or_Failure {
	unfixed,  // 未確定
	success,  // 成功
	failure   // 失敗
};

// ==============================
// 前日設定
// ==============================
class CastGauge;
class GameCamera;
class PlayFishingBackGround;
class PositionSelection;
class FishManager;
class TensionGauge;
class FishingRodHP;
class ScoreDisplay;
class Player;
class SceneFightFish;
class FishModel;
class RodFloatMove;
class PlayCastGaugeState;
class CastState;
class WaitForFishState;
class FightFishState;
class FishingAnimationState;
class HitUIState;
class FishDetectionRadius;
class InGameState;
class BackGround;
class ScoreManager;
class Enemy;
class StealPositionBar;
class BuffManager;
class FishCatchEffectState;

class PlayFishing : public IGameObject
{
public:
	PlayFishing();
	~PlayFishing();

	bool Init();
	bool Start();
	void Update();

	// ==============================
	// 外部から呼ばれるインターフェース
	// ==============================
	void SetSuccess();
	void SetFailure();
	void SetFishData();
	void SetCurrentFishManagerObjectName(std::string string_objectName);
	void SetCurrent_range_and_max_range_rate(float range_of_fish_and_ship);
	void SetRange_of_fish_and_float(float range_of_fish_and_float);
	void SetCastStrength(float scalar_multiply_in_first_velocity_vector);
	void SetFishScaleByIndividualFactor();
	void ReturnToPositionSelectCamera();
	void ChangeScene();
	void DeleteThisClass();

	FishData& GetFishData();
	float GetFIshScore();

	PlayFishingStatus GetPlayFishingStatus()const;

	bool canNewGOFishingRodHP = true; // RodHPのNewGOを許可するか

	// ==============================
	// 内部ロジック管理
	// ==============================
	void Success();
	void Failure();

	// パラメータ/ビジュアル
	float m_current_fish_range_and_max_range_rate = 0.0f;
	float m_current_float_range_max_range_rate = 0.0f;
	float m_castStrength = 0.0f;

	Vector3 m_floating=Vector3::Zero;
	Vector3 m_gameCameraTarget = Vector3::Zero;
	Vector3 m_rodFloatModelPos = Vector3::Zero;
	Vector3 m_cameraPos{ 0.0f,0.0f,0.0f };
	Vector3 m_cameraTarget{ 0.0f,0.0f,0.0f };
	Vector3 m_fishModelPos = Vector3::Zero;

	PlayFishingStatus m_playFishingStatus = playCastGauge;

	

private:
	void FindGameObjects();
	void NewGOGameObjects();
	// void InitNewGOGameObjects(); // 未使用
	void StatusManager();
	void float_to_water(); // 潮に浮かぶ動き

	FishData m_fishData;
	Successful_or_Failure m_successful_or_failure = unfixed;
	FishData* p_fishData = &m_fishData;
	std::string m_currentFishManagerobjectName;
	SoundSource* m_sound=nullptr;
	float m_floating_t = 0.0f;
	float m_casting_t = 0.0f;
	bool m_shouldChangeScene = false;

	// ==============================
	// 関係クラス管理
	// ==============================
	GameCamera* m_gameCamera = nullptr;
	// PlayFishingBackGround* m_playFishingBackGround = nullptr; // 未使用
	PositionSelection* m_positionSelection = nullptr;
	FishManager* m_fishManager = nullptr;
	TensionGauge* m_tensionGauge = nullptr;
	FishingRodHP* m_fishingRodHP = nullptr;
	ScoreDisplay* m_scoreDisplay = nullptr;
	/// <summary>
	/// 表示用のプレイヤー
	/// データの管理はこっちではしない。
	/// </summary>
	Player* playerVisual = nullptr;
	/// <summary>
	/// モデルは表示しない。
	/// データはこっちで管理する。
	/// ポジション選択シーンでのプレイヤーと同じオブジェクト。
	/// </summary>
	Player* m_player = nullptr;
	SceneFightFish* m_sceneFightFish = nullptr;
	FishModel* m_fshModel = nullptr;
	RodFloatMove* m_rodFloatMove = nullptr;
	PlayCastGaugeState* m_playCastGaugeState = nullptr;
	CastState* m_castState = nullptr;
	WaitForFishState* m_waitForFishState = nullptr;
	FightFishState* m_fightFishState = nullptr;
	FishingAnimationState* m_fishingAnimationState = nullptr;
	HitUIState* m_hitUIState = nullptr;
	FishDetectionRadius* m_fishDetectionRadius = nullptr;
	InGameState* m_inGameState = nullptr;
	BackGround* m_backGround = nullptr;
	ScoreManager* m_scoreManager = nullptr;
	Enemy* m_enemy = nullptr;
	StealPositionBar* m_stealPositionBar = nullptr;
	BuffManager* m_buffManager=nullptr;
	FishCatchEffectState* m_fishCatchEffectState = nullptr;
};
