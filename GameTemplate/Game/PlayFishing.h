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
class FishingGauge;
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



class PlayFishing :public IGameObject
{
public:

	PlayFishing();
	~PlayFishing();
	void Init();
	void Update();
	bool Start();



	void SetFishManagerObjectName(std::string string_objectName);
	void FindeFishManager();//フィッシュマネージャーを探して魚の情報を取得する。　
	char* m_objectName;
	void StatusManager();
	void NewGOFishingRodHP();
	bool canNewGOFishingRodHP = true;//釣り竿のHPクラスをNewGO可能か。
	void SetSuccess();
	void SetFailure();
	void Success();
	void Failure();
	void SetPlayFishingStatus_FishingGsauge();//プレイフィッシングステートをフィッシングゲージにする。
	void SetFishData();
	FishData& GetFishData();
	float GetFIshScore();//スコアディスプレイクラスにスコアを渡す関数。
	void SetCurrent_range_and_max_range_rate(float range_of_fish_and_ship);//魚と船の距離を設定
	float GetRange_of_fish_and_ship();
	void SetRange_of_fish_and_float(float range_of_fish_and_float);//ウキと船の距離を設定
	float GetRange_of_fish_and_float();
	void SetCastStrength(float scalar_multiply_in_first_velocity_vector);
	void Cast();
	void WaitForFish();
	//void SetRodFloatModalePosition();
	void float_to_water();
	void CalculateCurrent_float_range_and_max_range_rate();//ウキとの距離の割合を計算する

	//クラスを削除。
	void DeleteThisClass();

	//クラスを作成。
	void NewGOCastGauge();
	void NewGOFishingGauge();
	void NewGOSceneFightFish();
	void ChangeScene();


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
	GameCamera* gameCamera;			//�Q�[���J�����B
	PlayFishingBackGround* m_playFishingBackGround;
	PositionSelection* m_positionSelection;
	FishManager* m_fishManager;
	FishingGauge* m_fishingGauge;
	TensionGauge* m_tensionGauge;
	FishingRodHP* m_fishingRodHP;
	ScoreDisplay* m_scoreDisplay;
	Player* m_player;
	SceneFightFish* m_sceneFightFish;
	FishModel* m_fshModel;
	RodFloatMove* m_rodFloatMove;
	PlayCastGaugeState* m_playCastGaugeState;
	CastState* m_castState;
	WaitForFishState* m_waitForFishState;
	FightFishState* m_fightFishState;
	FishingAnimationState* m_fishingAnimationState;
	HitUIState* m_hitUIState;
	FishDetectionRadius* m_fishDetectionRadius;

};
