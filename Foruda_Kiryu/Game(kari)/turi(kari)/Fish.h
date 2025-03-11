#pragma once
class Fish : public IGameObject
{
//public:

	Fish();
	~Fish();
	//更新処理。
	void Update();
	void SetIndividualValue(float individualValue);//個体値を設定。
	void SetTimeUntilEscape(float timeUntilEscape);//逃げるまでの時間を設定。
	bool TimeCount();//時間のカウント。
	float m_individualValue;//個体値。
	float m_timeUntilEscape;//魚が逃げるまでの時間。
	float m_time;
};

