#pragma once
class Fish : public IGameObject
{
public:

	Fish();
	~Fish();
	//更新処理。
	void Update();
	void SetIndividualValue(float individualValue);//個体値を設定。
	void SetTimeUntilEscape(float timeUntilEscape);//逃げるまでの時間を設定。
	float m_individualValue;//個体値。
	float m_timeUntilEscape;//魚が逃げるまでの時間（0になると逃げる）。
};

