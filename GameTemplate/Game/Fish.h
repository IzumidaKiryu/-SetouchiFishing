#pragma once

struct FishData
{
	float timeUntilEscape=0.5;//魚が逃げるまでの時間
	float arrowSpeed = 5.0f;
	float score = 0.0f;//個体値
	float initPos=1;

	//上を向いている時下向きに変える確率。(0～100の範囲の整数値)。
	//一定の間隔の時間で向きを変えるかどうか抽選される。その時に変える確率。
	//なので100と書いてもずっと上を向くわけではない。
	int upwardBias=50;
	//下を向いている時上向きに変える確率。(0～100の範囲の整数値)。
	//一定の間隔の時間で向きを変えるかどうか抽選される。その時に変える確率。
	//なので100と書いてもずっと下を向くわけではない。
	int downwardBias=50;
};
class PositionSelection;
class Fish : public IGameObject
{
public:
	Fish();
	~Fish();
	//更新処理。
	void Update();
	bool Start();
	void SetScore();//フィッシュデータのスコアを設定する。
	void SetTimeUntilEscape(float timeUntilEscape);//逃げるまでの時間の設定。
	void SetArrowSpeed(float spead);
	void SetBaseScore(float baseScore);//基準になるスコア。
	void SetInitPos(float initpos);
	void SetUpWardBias(float bias);
	void SetDownwardBias(float bias);
	
	void SetParameter(float timeUntilEscape, 
		float spead,
		float baseScore,
		float initpos,
		float upwardBias,
		float downwardBias,
	);


	bool TimeCount();
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
	PositionSelection* m_positionSelection;
	FishData m_fishData;


};

