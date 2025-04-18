#include "stdafx.h"
#include "FishManager.h"
#include "Buri.h"
#include "Tatiuo.h"
#include "PositionSelection.h"
#include <random>

FishManager::FishManager()
{
	SelectFishType();
	FishNewGO();
	SetFishData();
	GetUI();
}

FishManager::~FishManager()
{
}

void FishManager::Update()
{
	SetShouldFishChange();
	Timer();
}

/// <summary>
/// 生成する魚の種類を決める
/// </summary>
void FishManager::SelectFishType()
{
	std::random_device rd;
	int randum= rd() % 100;
	m_randum = randum;
	if (0 <= randum&& randum <= 49) {
		m_fishType = BURI;
	}
	if (50 <= randum&& randum <= 100) {
		m_fishType = TATIUO;
	}
}

void FishManager::NewGOBuri()
{
	m_buri = NewGO<Buri>(0, "buri");
}

void FishManager::NewGOTatiuo()
{
	m_tatiuo = NewGO<Tatiuo>(0, "tatiuo");
}

/// <summary>
/// UIを取得する。
/// </summary>
void FishManager::GetUI()
{
	switch (m_fishType)
	{
	case TAI:
		break;
	case BURI:
		m_ui = &(m_buri->GetUI());
		break;
	case TATIUO:
		m_ui = &(m_tatiuo->GetUI());
		break;
	case HIRAME:
		break;
	case JAKOTENN:
		break;
	case SINJU:
		break;
	default:
		break;
	}
}

/// <summary>
/// 魚を生成する
/// </summary>
void FishManager::FishNewGO()
{
	switch (m_fishType)
	{
	case TAI:
		break;
	case BURI:
		NewGOBuri();
		break;
	case TATIUO:
		NewGOTatiuo();
		break;
	case HIRAME:
		break;
	case JAKOTENN:
		break;
	case SINJU:
		break;
	default:
		break;
	}
}

/// <summary>
/// 魚を変えるかどうか判断する変数を設定する。
/// </summary>
void FishManager::SetShouldFishChange()
{
	switch (m_fishType)
	{
	case TAI:
		break;
	case BURI:
		m_shouldFishChange = m_buri->GetShouldFishChange();
		break;
	case TATIUO:
		m_shouldFishChange = m_tatiuo->GetShouldFishChange();
		break;
	case HIRAME:
		break;
	case JAKOTENN:
		break;
	case SINJU:
		break;
	default:
		break;
	}
}

bool FishManager::GetShouldFishChange()
{
	return m_shouldFishChange;
}

void FishManager::SetFishData()
{
	switch (m_fishType)
	{
	case TAI:
		break;
	case BURI:
		p_fishData = &(m_buri->GetFishData());
		break;
	case TATIUO:
		p_fishData = &(m_tatiuo->GetFishData());
		break;
	case HIRAME:
		break;
	case JAKOTENN:
		break;
	case SINJU:
		break;
	default:
		break;
	}
	m_fishData = *p_fishData;
}

FishData& FishManager::GetFishData()
{
	/*FishData &a=*p_fishData;*/
	return *p_fishData;
}

float FishManager::GetScore()
{
	return m_fishData.score;
}

void FishManager::Timer()
{
	switch (m_fishType)
	{
	case TAI:
		break;
	case BURI:
		m_buri->TimeCount();
		break;
	case TATIUO:
		m_tatiuo->TimeCount();
		break;
	case HIRAME:
		break;
	case JAKOTENN:
		break;
	case SINJU:
		break;
	default:
		break;
	}
}

