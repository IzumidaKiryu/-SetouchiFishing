#pragma once

struct FishData
{
	float arrowSpeed=0.0f;
	float score=0.0f;//個体値
};
class PositionSelection;
class Fish : public IGameObject
{
public:
	Fish();
	~Fish();
	//更新処理。
	void Update();
	void SetScore();//フィッシュデータのindividualValueを設定する。
	void SetTimeUntilEscape(float timeUntilEscape);//逃げでの時間の設定。
	bool TimeCount();
	//void SetIndividualValue();//個体値を設定
	void ShouldFishChange();//魚を変えるかどうか。
	void ShouldFishChangeTrue();
	void ShouldFishChangeFalse();
	void SetisSelectedTrue();
	void SetisSelectedFalse();
	bool GetShouldFishChange();
	void SetBaseScore(float baseScore);//基準になるスコア。
	FishData& GetFishData();

	SpriteRender& GetUI();
	bool m_shouldFishChange = false;//魚を変えるべきか？
	bool m_isSelected=false;//選ばれているかどうか。（つられている最中かどうか）
	float m_baseScore ;//基準になるスコア。
	float m_timeUntilEscape;
	float m_time = 0.0f;
	SpriteRender m_ui;
	PositionSelection* m_positionSelection;
	FishData m_fishData;

};

