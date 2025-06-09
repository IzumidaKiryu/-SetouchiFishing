#pragma once
#include "Fish.h"
class PositionSelection;


class Buri;
class Tatiuo;
class Jakoten;
class Hirame;
class Tai;
class Fish;
class FishManager :public IGameObject
{
public:

	FishManager();
	~FishManager();
	void Init();
	bool Start() override;
	void Update();
	void SelectFishType();
	Fish* CreateFish(FishType type);

	bool GetShouldFishChange();

	FishData& GetFishData();//フィッシュデータを得るための関数。
	float GetScore();
	float GetTimeRatio();
	SpriteRender* GetUI();

private:
	void UIPopIn();

	Vector3 m_uiScale{1.0f,1.0f,1.0f};
	float m_uiPopIn_t=0;
	bool m_shouldFishChange = false;//魚を変えるべきかどうか。
	int m_randum;
	const double e = 2.718281828459045;
	float m_timeRatio=0;

	FishData m_fishData;//フィッシュデータのポインタ

	FishType m_fishType;
	SpriteRender* m_ui=nullptr;

	Fish* m_fish=nullptr;
	//Buri* m_buri;
	//Tatiuo* m_tatiuo;
	//Jakoten* m_jakoten;
	//Hirame* m_hirame;
	//Tai* m_tai;
};

