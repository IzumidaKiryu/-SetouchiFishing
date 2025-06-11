#pragma once
class TimeLimitUI : public IGameObject
{
public:
	TimeLimitUI();
	~TimeLimitUI();
	bool Init();
	bool Start();
	void Update();
	void SetTime(int time);
	FontRender& GetTimeFont();

private:
	int m_time;
	const Vector3 m_clockUIPos = { -570.0f,300.0f,0.0f };
	const Vector3 m_hundredsPlaceUIPos = { -490.0f,300.0f,0.0f };
	const Vector3 m_tensPlaceUIPos = { -410.0f,300.0f,0.0f };
	const Vector3 m_onesPlaceUIPos = { -330.0f,300.0f,0.0f };
	FontRender m_timeFont;


};

