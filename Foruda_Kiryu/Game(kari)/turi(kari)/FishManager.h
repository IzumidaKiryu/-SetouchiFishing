#pragma once
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

	bool m_shouldFishChange = false;
	FishType m_fishType;
	Buri* m_buri;
	Tatiuo* m_tatiuo;
	SpriteRender* m_ui;
};

