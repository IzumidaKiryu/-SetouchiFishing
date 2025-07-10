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
	void SetBaseUiScale();
	void SelectFishType();
	Fish* CreateFish(FishType type);

	bool GetShouldFishChange();
	/// <summary>
	/// フィッシュデータを取得する。
	/// </summary>
	/// <returns></returns>
	FishData& GetFishData();
	float GetScore();
	float GetTimeRatio();
	SpriteRender* GetUI();
	std::map<BuffType, float> GetBuffEffect()const;
	BuffType GetBuffType()const;

private:
	void UIPopIn();

	Vector3 m_baseUiScale=Vector3::One;
	float m_uiPopIn_t=0;
	bool m_shouldFishChange = false;//魚を変えるべきかどうか。
	int m_randum = 0;
	const double e = 2.718281828459045;
	float m_timeRatio=0;

	FishData m_fishData;

	FishType m_fishType;
	SpriteRender* m_ui=nullptr;

	Fish* m_fish=nullptr;

	std::map<BuffType, float> buffEffect;

};

