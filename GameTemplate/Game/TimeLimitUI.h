#pragma once
class TimeLimitUI : public IGameObject
{
public:
	TimeLimitUI();
	~TimeLimitUI();
	bool Init();
	bool Start();
	void Update();
	void DisplayTimeLimitUI(int time);
	void SetTime(int time);
	void SetOnesPlace();
	void SetTensPlace();
	void SetHundredsPlace();
	void SetOnesPlaceUI();
	void SetTensPlaceUI();
	void SetHundredsPlaceUI();
	SpriteRender& GetClockUI();
	SpriteRender& GetOnesPlacUI();
	SpriteRender& GetTensPlacUI();
	SpriteRender& GetHundredsPlacUI();

	int m_time;
	int m_prevTime;
	int m_onesPlace;
	int m_tensPlace;
	int m_hundredsPlace;
	Vector3 m_clockUIPos = { -570.0f,300.0f,0.0f };
	Vector3 m_hundredsPlaceUIPos = { -490.0f,300.0f,0.0f };
	Vector3 m_tensPlaceUIPos = { -410.0f,300.0f,0.0f };
	Vector3 m_onesPlaceUIPos = { -330.0f,300.0f,0.0f };
	SpriteRender m_onesPlaceUI;
	SpriteRender m_tensPlaceUI;
	SpriteRender m_hundredsPlaceUI;
	SpriteRender m_clockUI;
	FontRender m_timeFont;

};

