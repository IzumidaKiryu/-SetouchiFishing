#include "stdafx.h"
#include "FishManager.h"
#include "Buri.h"
#include "Tatiuo.h"
#include "PositionSelection.h"
#include "Jakoten.h"
#include "Hirame.h"
#include "Tai.h"
#include"Fish.h"
#include"Pearl.h"
#include <random>

FishManager::FishManager()
{
}

FishManager::~FishManager()
{
	m_ui = nullptr; // 先に無効化

	if (m_fish) {
		DeleteGO(m_fish);
		m_fish = nullptr;
	}
}

void FishManager::Init()
{
	// ランダムに種類決定
	SelectFishType();           

	// 生成
	m_fish = CreateFish(m_fishType); 
	m_fish->Init();

	// UI取得
	m_ui = &m_fish->GetUI();
	m_fishData = m_fish->GetFishData();

	//UIの基準サイズをセット。
	SetBaseUiScale();

}

bool FishManager::Start()
{

	return true;
}

void FishManager::Update()
{
	// 魚の変更判定を取得。
	m_shouldFishChange = m_fish->GetShouldFishChange();

	//魚が逃げるまでの時間を更新。
	m_fish->UpdateEscapeTimer();

	//時間の割合を取得。
	m_timeRatio = m_fish->GetTimeRatio();

	UIPopIn();
}

void FishManager::SetBaseUiScale()
{
	m_baseUiScale = m_ui->GetScale();
}

/// <summary>
/// 生成する魚の種類を決める
/// </summary>
void FishManager::SelectFishType()
{
	std::random_device rd;
	int randum = rd() % 100;
	m_randum = randum;

	if (0 <= randum && randum <= 26) { // 27%
		m_fishType = FishType::SINJU;
	}
	else if (27 <= randum && randum <= 53) { // 27%
		m_fishType = FishType::HIRAME;
	}
	else if (54 <= randum && randum <= 80) { // 27%
		m_fishType = FishType::JAKOTENN;
	}
	else if (81 <= randum && randum <= 87) { // 7%
		m_fishType = FishType::TATIUO;
	}
	else if (88 <= randum && randum <= 94) { // 7%
		m_fishType = FishType::BURI;
	}
	else if (95 <= randum && randum <= 99) { // 5%
		m_fishType = FishType::TAI;
	}
}

Fish* FishManager::CreateFish(FishType type)
{
	switch (type)
	{
	case FishType::TAI:     return NewGO<Tai>(0, "tai");
	case FishType::BURI:    return NewGO<Buri>(0, "buri");
	case FishType::TATIUO:  return NewGO<Tatiuo>(0, "tatiuo");
	case FishType::HIRAME:  return NewGO<Hirame>(0, "hirame");
	case FishType::JAKOTENN:return NewGO<Jakoten>(0, "jakoten");
	case FishType::SINJU:return NewGO<Pearl>(0, "jakoten");
	default:      return nullptr;
	}
}




bool FishManager::GetShouldFishChange()
{
	return m_shouldFishChange;
}


void FishManager::UIPopIn()
{
	m_uiPopIn_t+=0.1;
	float scale=0.0f;
	scale=(pow(e, -( m_uiPopIn_t-1)) * sin((m_uiPopIn_t-1)))+1;
	if (scale < 0) {
		scale = 0;
	}
	m_ui->SetScale(m_baseUiScale* scale);
	m_ui->Update();

}

FishData& FishManager::GetFishData()
{
	/*FishData &a=*p_fishData;*/
	return m_fishData;
}

float FishManager::GetScore()
{
	return m_fishData.score;
}


float FishManager::GetTimeRatio()
{
	return m_timeRatio;
}

SpriteRender* FishManager::GetUI()
{
	return m_ui;
}


std::map<BuffType, float>  FishManager::GetBuffEffect()const
{
	return  m_fishData.buffEffect;
}

BuffType FishManager::GetBuffType()const
{
	return m_fishData.buffType;
}

