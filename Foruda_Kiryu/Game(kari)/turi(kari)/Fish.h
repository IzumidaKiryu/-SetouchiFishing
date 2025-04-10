#pragma once

struct FishData
{
	float arrowSpeed;
};
class PositionSelection;
class Fish : public IGameObject
{
public:
	Fish();
	~Fish();
	//更新処理。
	void Update();
	void SetIndividualValue(float individualValue);//個体値の設定。
	void SetTimeUntilEscape(float timeUntilEscape);//逃げるまでの時間の設定。
	bool TimeCount();
	//void SetIndividualValue();//個体値を設定
	void ShouldFishChange();//魚を変えるかどうか。
	void ShouldFishChangeTrue();
	void ShouldFishChangeFalse();
	void SetisSelectedTrue();
	void SetisSelectedFalse();
	bool GetShouldFishChange();

	SpriteRender& GetUI();
	bool m_shouldFishChange = false;//魚を変えるべきか？
	bool m_isSelected=false;//選ばれているかどうか。（つられている最中かどうか）
	float m_individualValue;//個体値
	float m_timeUntilEscape;
	float m_time = 0.0f;
	SpriteRender m_ui;
	PositionSelection* m_positionSelection;
};

