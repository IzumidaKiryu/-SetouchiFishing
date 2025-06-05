#include "stdafx.h"
#include "FishManager.h"
#include "Buri.h"
#include "Tatiuo.h"
#include "PositionSelection.h"
#include "Jakoten.h"
#include "Hirame.h"
#include "Tai.h"
#include"Fish.h"
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
	SelectFishType();                // ランダムに種類決定
	m_fish = CreateFish(m_fishType); // 生成
	m_fish->Init();

	m_ui = &m_fish->GetUI();         // UI取得
	m_fishData = m_fish->GetFishData();
}

bool FishManager::Start()
{

	return true;
}

void FishManager::Update()
{
	m_shouldFishChange = m_fish->GetShouldFishChange();
	m_fish->TimeCount();
	m_timeRatio = m_fish->GetTimeRatio();
	UIPopIn();
}

/// <summary>
/// 生成する魚の種類を決める
/// </summary>
void FishManager::SelectFishType()
{
	std::random_device rd;
	int randum = rd() % 100;
	m_randum = randum;
	if (0 <= randum && randum <= 20) {
		m_fishType = FishType::BURI;
	}
	if (21 <= randum && randum <=30 ) {
		m_fishType = FishType:: TATIUO;
	}
	if (31 <= randum && randum <= 50){
		m_fishType = FishType::JAKOTENN;
	}
	if (51 <= randum && randum <= 90) {
		m_fishType = FishType::HIRAME;
	}
	if (91 <= randum && randum <= 100) {

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
	m_ui->SetScale(m_uiScale* scale);
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

