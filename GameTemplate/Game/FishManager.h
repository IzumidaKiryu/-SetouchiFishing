#pragma once
#include "Fish.h"
class PositionSelection;
enum FishType {
	TAI,
	BURI,
	TATIUO,
	HIRAME,
	JAKOTENN,
	SINJU,
};

class Buri;
class Tatiuo;
class Jakoten;
class Hirame;
class Tai;
class FishManager :public IGameObject
{
public:

	FishManager();
	~FishManager();
	void Update();
	void SelectFishType();
	void NewGOBuri();
	void NewGOTatiuo();
	void NewGOJakoten();
	void NewGOHirame();
	void NewGOTai();
	void SetUI();
	void FishNewGO();
	void SetShouldFishChange();
	bool GetShouldFishChange();
	void SetFishData();//フィッシュデータを設定する。
	void UIPopIn();
	FishData& GetFishData();//フィッシュデータを得るための関数。
	float GetScore();
	void Timer();
	void DeleteFish();
	void SetTimeRatio();
	float GetTimeRatio();

	Vector3 m_uiScale{1.0f,1.0f,1.0f};
	float m_uiPopIn_t=0;
	bool m_shouldFishChange = false;//魚を変えるべきかどうか。
	int m_randum;
	const double e = 2.718281828459045;
	float m_timeRatio=0;

	FishData* p_fishData = &m_fishData;//フィッシュデータのポインタ
	FishData m_fishData;//魚のデータ。

	FishType m_fishType;
	Buri* m_buri;
	Tatiuo* m_tatiuo;
	SpriteRender* m_ui;
	Jakoten* m_jakoten;
	Hirame* m_hirame;
	Tai* m_tai;
};

