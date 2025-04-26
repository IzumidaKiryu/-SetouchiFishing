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
	void SetFishData();//�t�B�b�V���f�[�^��ݒ肷��B
	FishData& GetFishData();//�t�B�b�V���f�[�^�𓾂邽�߂̊֐��B
	float GetScore();
	void Timer();

	bool m_shouldFishChange = false;//����ς���ׂ����ǂ����B
	int m_randum;

	FishData* p_fishData = &m_fishData;//�t�B�b�V���f�[�^�̃|�C���^
	FishData m_fishData;//���̃f�[�^�B

	FishType m_fishType;
	Buri* m_buri;
	Tatiuo* m_tatiuo;
	SpriteRender* m_ui;
};

