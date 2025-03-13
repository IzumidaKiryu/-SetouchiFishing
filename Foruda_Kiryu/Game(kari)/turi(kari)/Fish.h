#pragma once
class Fish : public IGameObject
{
public:

	Fish();
	~Fish();
	//更新処理。
	void Update();
	void SetIndividualValue(float individualValue);
	void SetTimeUntilEscape(float timeUntilEscape);
	bool TimeCount();
	//個体値を設定

	float IndividualValue;//個体値
	float m_time = 0.0f;
	float m_timeUntilEscape;
	float m_individualValue;

};

