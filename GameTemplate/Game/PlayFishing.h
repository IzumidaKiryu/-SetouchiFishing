#pragma once
#include "Fish.h"

enum PlayFishingStatus {
	castGauge,
	wait_castGauge,
	castAnimasion,
	cast,
	wait_for_fish,
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


class PlayFishing :public IGameObject
{
public:

	PlayFishing();
	~PlayFishing();
	void Init();
	void Update();


	
	
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
	void SetScalar_multiply_in_first_velocity_vector(float scalar_multiply_in_first_velocity_vector);
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


	float m_current_fish_range_and_max_range_rate;//今の魚の距離と最大の魚の距離の割合（それぞれのクラスで船と魚の最大距離とこの割合を掛けて場所を表現する。）
	float m_current_float_range_max_range_rate;//今のウキの距離と最大のウキの距離の割合。
	float m_floating_t;
	float m_casting_t;
	Vector3 m_floating;
	Vector3 m_gameCameraTarget;


	//キャストメソッド用変数
	Vector3 g{ 0.0f,-30.0f,0.0f };//重力。
	Vector3 m_float_initPos{ 0.0f,500.0f,10.0f };
	Vector3 m_rodFloatPosition = m_float_initPos;
	float water_surface_position_y=0;//うみのy軸での場所。
	float m_scalar_multiply_in_first_velocity_vector;//初速度に掛けるスカラー
	float first_velocity_vector_z = 2;//初速ベクトルｚの値（ｙとｚの比率）。
	Vector3 first_velocity_vector{ 0.0f,1.0f,first_velocity_vector_z };//初速ベクトル（ｙは必ず1にしておく）。
	float m_z_axis_value_drop_float;//ウキを落とすｚ軸の値。


	PlayFishingStatus m_playFishingStatus = castGauge;
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

};
