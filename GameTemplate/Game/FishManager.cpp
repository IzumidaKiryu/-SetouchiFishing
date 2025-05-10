#include "stdafx.h"
#include "FishManager.h"
#include "Buri.h"
#include "Tatiuo.h"
#include "PositionSelection.h"
#include "Jakoten.h"
#include "Hirame.h"
#include "Tai.h"
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
	int randum = rd() % 100;
	m_randum = randum;
	if (0 <= randum && randum <= 20) {
		m_fishType = BURI;
	}
	if (21 <= randum && randum <=30 ) {
		m_fishType = TATIUO;
	}
	if (31 <= randum && randum <= 50){
		m_fishType = JAKOTENN;
	}
	if (51 <= randum && randum <= 90) {
		m_fishType = HIRAME;
	}
	if (91 <= randum && randum <= 100) {

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

void FishManager::NewGOJakoten()
{
	m_jakoten = NewGO<Jakoten>(0, "jakoten");
}

void FishManager::NewGOHirame()
{
	m_hirame=NewGO<Hirame>(0, "hirame");
}

void FishManager::NewGOTai()
{
	m_tai = NewGO<Tai>(0,"tai");
}


/// <summary>
/// UIを取得する。
/// </summary>
void FishManager::GetUI()
{
	switch (m_fishType)
	{
	case TAI:
		m_ui = &(m_tai->GetUI());
		break;
	case BURI:
		m_ui = &(m_buri->GetUI());
		break;
	case TATIUO:
		m_ui = &(m_tatiuo->GetUI());
		break;
	case HIRAME:
		m_ui = &(m_hirame->GetUI());
		break;
	case JAKOTENN:
		m_ui = &(m_jakoten->GetUI());
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
		NewGOTai();
		break;
	case BURI:
		NewGOBuri();
		break;
	case TATIUO:
		NewGOTatiuo();
		break;
	case HIRAME:
		NewGOHirame();
		break;
	case JAKOTENN:
		NewGOJakoten();
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
		m_shouldFishChange = m_tai->GetShouldFishChange();
		break;
	case BURI:
		m_shouldFishChange = m_buri->GetShouldFishChange();
		break;
	case TATIUO:
		m_shouldFishChange = m_tatiuo->GetShouldFishChange();
		break;
	case HIRAME:
		m_shouldFishChange = m_hirame->GetShouldFishChange();
		break;
	case JAKOTENN:
		m_shouldFishChange = m_jakoten->GetShouldFishChange();
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
		p_fishData = &(m_tai->GetFishData());
		break;
	case BURI:
		p_fishData = &(m_buri->GetFishData());
		break;
	case TATIUO:
		p_fishData = &(m_tatiuo->GetFishData());
		break;
	case HIRAME:
		p_fishData = &(m_hirame->GetFishData());
		break;
	case JAKOTENN:
		p_fishData = &(m_jakoten->GetFishData());
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
		m_tai->TimeCount();
		break;
	case BURI:
		m_buri->TimeCount();
		break;
	case TATIUO:
		m_tatiuo->TimeCount();
		break;
	case HIRAME:
		m_hirame->TimeCount();
		break;
	case JAKOTENN:
		m_jakoten->TimeCount();
		break;
	case SINJU:
		break;
	default:
		break;
	}
}

