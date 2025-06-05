#include "stdafx.h"
#include "FishDetectionRadius.h"
#include "TensionGauge.h"
#include "PlayFishing.h"

FishDetectionRadius::FishDetectionRadius()
{	
}
FishDetectionRadius::~FishDetectionRadius()
{
}

bool FishDetectionRadius::Init()
{
	m_fishDetectionRadiusUI.Init("Assets/modelData/FishDetectionRadiusUI.DDS", 500, 500);
	m_fishDetectionRadiusUI.SetPivot(Vector2(0.5f, 0.5f));
	m_fishDetectionRadiusUI.Update();

	return true;
}

bool FishDetectionRadius::Start()
{
	m_tensionGauge = FindGO<TensionGauge>("tensionGauge");

	m_playFishing = FindGO<PlayFishing>("playFishing");

	m_tensionGauge->FindGOFishDetectionRadius();
	return true;
}

void FishDetectionRadius::Update()
{

	//感知範囲を決める。
	CalculateDetectionRange();

	//位置を決める。
	CalculateDetectionRangePos();

	//UIの更新。
	m_fishDetectionRadiusUI.Update();
}

void FishDetectionRadius::CalculateDetectionRange()
{
	m_playFishing = FindGO<PlayFishing>("playFishing"); 

		//魚の検知半径を設定する。
		m_fishDetectionRadius = m_playFishing->GetFishData().fishDetectionRadius;
		CalculateFishDetectionRadiusUIScale();
}

void FishDetectionRadius::CalculateFishDetectionRadiusUIScale()
{
	//半径なので２倍する。
	m_uiScale.y = m_fishDetectionRadius*2;
	m_uiScale.x = m_fishDetectionRadius * 2;
	m_fishDetectionRadiusUI.SetScale(m_uiScale);
}

float FishDetectionRadius::GetFishDetectionRadius()
{
	return m_fishDetectionRadius;
}

float FishDetectionRadius::GetPos()
{
		return m_fishDetectionRadiusPos;
}

void FishDetectionRadius::DeletThis()
{
	DeleteGO(this);
}

SpriteRender& FishDetectionRadius::GetUI()
{
	// TODO: return ステートメントをここに挿入します
	return m_fishDetectionRadiusUI;
}

void FishDetectionRadius::CalculateDetectionRangePos()
{
	m_fishDetectionRadiusPos= m_playFishing->m_current_fish_range_and_max_range_rate;
	
	SetFishDetectionRadiusUIPosition();
}

void FishDetectionRadius::SetFishDetectionRadiusUIPosition()
{
	//魚のUIの位置を取得する。
	m_fishDetectionRadiusUIPos = m_tensionGauge->GetFishUIPosition();

	m_fishDetectionRadiusUI.SetPosition(m_fishDetectionRadiusUIPos);
}



