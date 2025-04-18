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
class FishManager :public IGameObject
{
public:

	FishManager();
	~FishManager();
	void Update();
	void SelectFishType();
	void NewGOBuri();
	void NewGOTatiuo();
	void GetUI();
	void FishNewGO();
	void SetShouldFishChange();
	bool GetShouldFishChange();
	void SetFishData();//フィッシュデータを設定する。
	FishData& GetFishData();//フィッシュデータを得るための関数。
	float GetScore();
	void Timer();

	bool m_shouldFishChange = false;//魚を変えるべきかどうか。
	int m_randum;

	FishData* p_fishData = &m_fishData;//フィッシュデータのポインタ
	FishData m_fishData;//魚のデータ。

	FishType m_fishType;
	Buri* m_buri;
	Tatiuo* m_tatiuo;
	SpriteRender* m_ui;
};

