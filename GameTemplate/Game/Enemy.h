#pragma once
#include"Character.h"
#include "PositionSelection.h"
#include"Fish.h"

class BackGround;
class PositionSelection;
class InGameState;
class ScoreManager;
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
	void SetTargetFishingArea(Area targetFishingArea);
	Area GetTargetFishinArea();
	bool IsFishingInactive()const;
	void SetTargetFishData(Area targetarea);
	/// <summary>
	/// 渡されたエリアで釣り中かどうかを返す。
	/// </summary>
	/// <param name="area"></param>
	/// <returns></returns>
	bool GetIsFishingInArea(Area area);

	/// <summary>
	/// 釣りを終えた後の処理をする。
	/// プレイヤーの釣りの回数と敵の回数が同じになるようにプレイヤーの釣りが終わったら。
	/// 敵も終わるようにする。
	/// プレイヤーが釣りに成功した瞬間と釣りに失敗した瞬間に呼び出す。
	/// </summary>
	void EndFishing();

	void SetEnemyScore();

	//Vector3 position = {200.0f,100.0f,1.0f};


private:

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
	InGameState* m_inGameState;
	ScoreManager* m_scoreManager;

	std::map<FishType, float> m_fishingBaseTimes;
};

