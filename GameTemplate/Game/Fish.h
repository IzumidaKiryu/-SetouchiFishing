#pragma once
#include "BuffManager.h"

enum class FishType {
	TAI,
	BURI,
	TATIUO,
	HIRAME,
	JAKOTENN,
	SINJU,
};

enum class FishRarity {
	Common,      // 通常
	Rare,        // レア
	SuperRare    // スーパーレア
};

struct FishData
{
	FishType fishType;
	float timeUntilEscape=0.5;//魚が逃げるまでの時間
	float arrowSpeed = 5.0f;
	//個体値
	float score = -10.0f;

	// 個体ごとのスコアやサイズに影響を与える補正係数（例：1.0 なら標準、1.2 なら20%増）
	float individualFactor = 0.0f;

	//初期ポジション。
	float initPos=1;

	//上を向いている時下向きに変える確率。(0～100の範囲の整数値)。
	//一定の間隔の時間で向きを変えるかどうか抽選される。その時に変える確率。
	//なので100と書いてもずっと上を向くわけではない。
	int upwardBias=50;

	//下を向いている時上向きに変える確率。(0～100の範囲の整数値)。
	//一定の間隔の時間で向きを変えるかどうか抽選される。その時に変える確率。
	//なので100と書いてもずっと下を向くわけではない。
	int downwardBias=50;

	//ウキを感知する範囲(0～1)
	float fishDetectionRadius=0;

	//逃げる力。
	float escapeForce = 1.0f;

	//釣ったときにかかるバフ。
	std::map<BuffType,float> buffEffect;

	BuffType buffType;

	FishRarity rarity;
};
class PositionSelection;
class InGameState;
class Fish : public IGameObject
{
public:
	Fish();
	~Fish();
	//更新処理。
	void Update();
	virtual bool Init()final;
	virtual bool OnInit()=0;
	bool Start();
	/// <summary>
	/// 個体ごとのばらつきを持たせるために、
	/// individualFactor にランダムな値（0.804～1.2の範囲）を設定します。
	/// ベース値 0.8 に 0.004～0.4 のランダムな補正を加算しています。
	/// </summary>
	void SetRandomIndividualFactor();
	void SetFishType(FishType fishtype);
	void SetScore();//フィッシュデータのスコアを設定する。
	void FindGameObjects();
	void SetTimeUntilEscape(float timeUntilEscape);//逃げるまでの時間の設定。
	void SetArrowSpeed(float spead);
	void SetBaseScore(float baseScore);//基準になるスコア。
	void SetInitPos(float initpos);
	void SetUpWardBias(float bias);
	void SetDownwardBias(float bias);
	void SetFishDetectionRadius(float fishDetectionRadius);
	void SetEscapeForce(float escapeForce);
	virtual void SetUI(std::string filePath, Vector3 scale=Vector3::One)final;

	void SetParameter(float timeUntilEscape, 
		float spead,
		float baseScore,
		float initpos,
		float upwardBias,
		float downwardBias,
		float fishDetectionRadius=0.2f,
		float escapeForce = 0.005f
	);

	void SetBuff(BuffType bufftype, float buffValue);
	void UpdateEscapeTimer();
	//void SetIndividualValue();//個体値を設定
	//void ShouldFishChange();//魚を変えるかどうか。
	void ShouldFishChangeTrue();
	void ShouldFishChangeFalse();
	void SetisSelectedTrue();
	void SetisSelectedFalse();
	bool GetShouldFishChange();

	
	float GetTimeRatio();




	virtual void Effect();//釣った後の効果。
	FishData& GetFishData();

	SpriteRender& GetUI();

	bool m_shouldFishChange = false;//魚を変えるべきか？
	bool m_isSelected = false;//選ばれているかどうか。（つられている最中かどうか）
	float m_baseScore;//基準になるスコア。
	//float m_time = 0.0f;
	float m_initialTime = 0.0f;//このクラスが作られたときの時間。
	float m_nowTime;
	float m_timeRatio = 0.0f;
	SpriteRender m_ui;
	PositionSelection* m_positionSelection=nullptr;
	InGameState* m_inGameState = nullptr;
	FishData m_fishData;


};

