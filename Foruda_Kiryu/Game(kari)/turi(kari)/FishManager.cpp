#include "stdafx.h"
#include "FishManager.h"
#include "Buri.h"
#include "Tatiuo.h"

FishManager::FishManager()
{
	srand(time(NULL));
	SelectFishType();
	FishNewGO();
}

FishManager::~FishManager()
{

}

void FishManager::Update()
{
}

/// <summary>
/// ¶¬‚·‚é‹›‚Ìí—Ş‚ğŒˆ‚ß‚é
/// </summary>
void FishManager::SelectFishType()
{
	int randum=rand()%100;
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
/// UI‚ğæ“¾‚·‚éB
/// </summary>
void FishManager::GetUI()
{
	switch (m_fishType)
	{
	case TAI:
		break;
	case BURI:
		m_ui = &(m_buri->m_ui);
		break;
	case TATIUO:
		m_ui = &(m_tatiuo->m_ui);
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
/// ‹›‚ğ¶¬‚·‚é
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
/// ‹›‚ğ•Ï‚¦‚é‚©‚Ç‚¤‚©”»’f‚·‚é•Ï”‚ğİ’è‚·‚éB
/// </summary>
void FishManager::SetShouldFishChange()
{
	switch (m_fishType)
	{
	case TAI:
		break;
	case BURI:
		m_shouldFishChange = m_buri->m_shouldFishChange;
		break;
	case TATIUO:
		m_shouldFishChange = m_tatiuo->m_shouldFishChange;
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
