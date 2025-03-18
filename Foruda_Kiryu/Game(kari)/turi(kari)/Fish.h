#pragma once
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
	float m_individualValue;//個体値
	float m_timeUntilEscape;
	float m_time = 0.0f;
	SpriteRender m_ui;
};

