#pragma once
#include"Character.h"
#include "PositionSelection.h"
#include"Fish.h"

class BackGround;
class PositionSelection;
class InGameState;
class Enemy :public Character
{
public:
	Enemy();
	~Enemy();
	bool Init();
	bool Start() override;
	
	void Update()override;

	void FindGameObjects();

	void InitFishingBaseTimes();

	//ムーブスピードを設定。
	void SetMoveSpeed() override;
	void Render(RenderContext& rc);
	void SetCountdownFinished(bool countdownFinished);
	void SetTargetFishingArea();
	Area GetTargetFishinArea();
	void SetIsFishingInArea(Area fishingArea,bool isFishingInArea);
	bool IsFishingInactive()const;
	void CalculateFishingTime(FishType targetFish);
	void SetTargetFishData(Area targetarea);
	bool IsFishCaught();//魚を釣り上げているか
	void StartFishingTimer();
	void ResetTimer();
	void UpdateFishingElapsedTime();

	//Vector3 position = {200.0f,100.0f,1.0f};


private:
	enum class EnemyState {


	};
	const Vector3 m_fishingAreaPosition[6]//敵の魚を釣る場所。
	{
	 {-502.2f,1.65f,-317.0f},
	 {31.5f,-43.5f,-276.3f},
	 {500.0f,-43.4f,-300.0f},
	 {-430.0f,-43.47f,-510.26f},
	 {41.01f,-43.47f,-544.6f},
	 {625.8f,-43.47f,-570.8f},
	};
	std::map< Area, bool> m_isFishingInArea =//各エリアで釣っているかどうか？ 
	{
		{Area::A,false},
		{ Area::B,false },
	{ Area::C,false },
	{ Area::D,false },
	{ Area::E,false },
	{ Area::F,false },
	};
	bool m_isCountdownFinished = false; //カウントダウンが終わったかどうか。

	PositionSelection* m_positionSelection=nullptr;
	BackGround* m_backGround=nullptr;
	Area m_targetFishingArea= Area::INITIALSTATE;

	float targetFishingTime =0.0f;//狙っている魚を釣るのにかかる時間。
	float fishingElapsedTime = 0.0f;//今釣っている魚の釣り経過時間。
	FishData m_TargetFishData;
	InGameState* m_inGameState;
	std::map<FishType, float> m_fishingBaseTimes;
	Stopwatch m_stopwatch;

};

