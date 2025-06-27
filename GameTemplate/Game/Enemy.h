#pragma once
#include"Character.h"
#include "PositionSelection.h"
#include"Fish.h"

class BackGround;
class PositionSelection;
class InGameState;
class ScoreManager;
class PlayFishing;
class Player;
class StealPositionBar;
class Enemy :public Character
{
public:
	Enemy();
	~Enemy();
	bool Init();
	bool Start() override;
	
	void Update()override;

	void FindGameObjects();

	void FindStealPositionBarObjects();

	void InitFishingBaseTimes();

	//ムーブスピードを設定。
	void SetMoveSpeed() override;
	void Render(RenderContext& rc);
	void SetCountdownFinished(bool countdownFinished);

	/// <summary>
/// 敵が釣るエリアを決める。
/// </summary>
	void SetTargetFishingArea(Area targetFishingArea);

	/// <summary>
	/// 釣りを中断して、別のエリアに移動する。
	/// </summary>
	void InterruptAndRelocateFishing(Area targetFishingArea);

	/// <summary>
	/// 釣りを開始する。
	/// </summary>
	/// <param name="currentTime"></param>
	void StartFishing(float currentTime);
	Area GetTargetFishinArea();
	bool IsFishingInactive()const;
	void SetTargetFishData(Area targetarea);

	/// <summary>
	/// 釣りが終わる時間を設定する。
	/// </summary>
	/// <param name="currentTime"></param>
	void SetFishingEndTime(float currentTime);



	/// <summary>
	/// 釣りが終わったかどうか。
	/// </summary>
	/// <returns></returns>
	bool IsEndCurrentFishing()const;


	/// <summary>
	/// 渡されたエリアで釣り中かどうかを返す。
	/// </summary>
	/// <param name="area"></param>
	/// <returns></returns>
	bool GetIsFishingInArea(Area area);

	/// <summary>
	/// 釣りを終えた後の処理をする。
	/// </summary>
	void EndFishing();

	/// <summary>
	/// 釣りが成功するか、失敗するかを決める。
	/// </summary>
	/// <returns>成功ならtrue</returns>
	bool DecideFishingResult(FishRarity raritu);

	/// <summary>
	/// 
	/// </summary>
	void ResetCarryOverFishingTime();
	//Vector3 position = {200.0f,100.0f,1.0f};

	/// <summary>
	/// テイクオーバゲージが使われたときの処理。
	/// </summary>
	void OnTakeOverGaugeUsed();


private:

	/// <summary>
	/// 各レアリティーの釣り上げる確率を設定。
	/// </summary>
	void SetInitRarityProbability();

	float m_fishingEndTime = 0.0f; //釣りが終わる時間。
	float m_fishingStartTime = 0.0f; //釣りを開始した時間。
	/// <summary>
	/// 途中で釣りを中断した場合、次の釣りに持ち越す時間。
	/// </summary>
	float m_carryOverFishingTime=0.0f;
	float m_extendedFishingTimeByTakeOver = 0.0f; //テイクオーバーゲージが使われたときに、釣り時間が延長される時間。
	bool hasDecidedInitialTargetFishingArea=false;

	const std::array<Vector3,6> m_fishingAreaPosition//敵の魚を釣る場所。
	{
	 Vector3( - 502.2f,1.65f,-317.0f),
	 Vector3(31.5f,-43.5f,-276.3f),
	 Vector3(500.0f,-43.4f,-300.0f),
	 Vector3(-430.0f,-43.47f,-510.26f),
	 Vector3(41.01f,-43.47f,-544.6f),
	 Vector3(625.8f,-43.47f,-570.8f),
	};
	bool m_isCountdownFinished = false; //ゲームスタートカウントダウンが終わったかどうか。

	PositionSelection* m_positionSelection=nullptr;
	BackGround* m_backGround=nullptr;
	Area m_targetFishingArea= Area::INITIALSTATE;

	FishData m_targetFishData;
	InGameState* m_inGameState=nullptr;
	ScoreManager* m_scoreManager=nullptr;
	Player* m_player = nullptr;
	StealPositionBar* m_stealPositionBar = nullptr;

	std::map<FishRarity, float> m_fishingBaseTimes;
	/// <summary>
	/// 各魚を釣り上げる確率（整数）
	/// </summary>
	std::map<FishRarity,int> m_rarityProbability;
};

