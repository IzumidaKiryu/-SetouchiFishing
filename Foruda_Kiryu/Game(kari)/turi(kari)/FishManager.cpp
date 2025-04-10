#include "stdafx.h"
#include "FishManager.h"
#include "Buri.h"
#include "Tatiuo.h"
#include <random>

FishManager::FishManager()
{
	SelectFishType();
	FishNewGO();
	GetUI();
}

FishManager::~FishManager()
{

}

void FishManager::Update()
{
}

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

