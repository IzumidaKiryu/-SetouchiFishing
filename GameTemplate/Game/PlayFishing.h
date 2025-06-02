#pragma once
#include "Fish.h"

enum PlayFishingStatus {
	playCastGauge,
	wait_castGauge,
	castAnimasion,
	cast,
	wait_for_fish,
	hitUI,
	sceneFightFish,
	wait_ceneFightFish
};

enum  Successful_or_Failure {
	unfixed,//未確定
	success,//成功
	failure//失敗
};

class CastGauge;
class FishingGauge;
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


class PlayFishing :public IGameObject
{
public:

	PlayFishing();
	~PlayFishing();
	bool Init();
	void Update();
	bool Start();


	void NewGOGameObjects();
	void InitNewGOGameObjects();
	void SetCurrentFishManagerObjectName(std::string string_objectName);
	std::string m_currentFishManagerobjectName;
	void StatusManager();
	void FindGameObjects();
	bool canNewGOFishingRodHP = true;//釣り竿のHPクラスをNewGO可能か。
	void SetSuccess();
	void SetFailure();
	void Success();
	void Failure();
	void SetFishData();
	FishData& GetFishData();
	float GetFIshScore();//スコアディスプレイクラスにスコアを渡す関数。
	void SetCurrent_range_and_max_range_rate(float range_of_fish_and_ship);//魚と船の距離を設定
	void SetRange_of_fish_and_float(float range_of_fish_and_float);//ウキと船の距離を設定
	void SetCastStrength(float scalar_multiply_in_first_velocity_vector);
	void float_to_water();
	void SetFishScaleByIndividualFactor();

	//クラスを削除。
	void DeleteThisClass();

	void ChangeScene();

	void ReturnToPositionSelectCamera();


	float m_current_fish_range_and_max_range_rate;//今の魚の距離と最大の魚の距離の割合（それぞれのクラスで船と魚の最大距離とこの割合を掛けて場所を表現する。）
	float m_current_float_range_max_range_rate;//今のウキの距離と最大のウキの距離の割合。
	float m_floating_t;
	float m_casting_t;


	Vector3 m_floating;
	Vector3 m_gameCameraTarget;


	float m_castStrength;//キャストの強さ（ウキのとび具合が変わる）

	Vector3 m_rodFloatModelPos;
	Vector3 m_fishModelPos;

	Vector3 m_cameraPos{0.0f,0.0f,0.0f};
	Vector3 m_cameraTarget{0.0f,0.0f,0.0f};

	bool m_shouldChangeScene = false;



	PlayFishingStatus m_playFishingStatus = playCastGauge;
	Successful_or_Failure m_successful_or_failure = unfixed;

	FishData m_fishData;//魚のデータ。
	FishData* p_fishData = &m_fishData;//フィッシュデータのポインタ


	CastGauge* m_castGauge;
	GameCamera* m_gameCamera;			//�Q�[���J�����B
	PlayFishingBackGround* m_playFishingBackGround;
	PositionSelection* m_positionSelection;
	FishManager* m_fishManager;
	FishingGauge* m_fishingGauge = nullptr;
	TensionGauge* m_tensionGauge = nullptr;
	FishingRodHP* m_fishingRodHP = nullptr;
	ScoreDisplay* m_scoreDisplay = nullptr;
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
	ScoreManager* m_scoreManager=nullptr;

};
