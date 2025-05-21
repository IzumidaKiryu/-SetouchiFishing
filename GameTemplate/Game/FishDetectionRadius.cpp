#include "stdafx.h"
#include "FishDetectionRadius.h"
#include "TensionGauge.h"
#include "PlayFishing.h"

FishDetectionRadius::FishDetectionRadius()
{
	m_fishDetectionRadiusUI.Init("Assets/modelData/FishDetectionRadiusUI.DDS",100, 700);
	m_playFishing = FindGO<PlayFishing>("playFishing");
	SetFishDetectionRadius();
	m_fishDetectionRadiusUI.SetPivot(Vector2(0.5f, 0.5f));
	SetFishDetectionRadiusUIScale();
	SetFishDetectionRadiusUIPosition();
	m_fishDetectionRadiusUI.Update();
}
FishDetectionRadius::~FishDetectionRadius()
{
}

void FishDetectionRadius::Update()
{
	SetFishDetectionRadiusUIPosition();
	m_fishDetectionRadiusUI.Update();
}

void FishDetectionRadius::SetFishDetectionRadius()
{
	//魚の検知範囲を設定する。
	m_fishDetectionRadius = m_playFishing->m_fishData.fishDetectionRadius;
	SetFishDetectionRadiusUIScale();
}

void FishDetectionRadius::Render(RenderContext& rc)
{

	//m_fishDetectionRadiusUI.Draw(rc);
}

void FishDetectionRadius::SetFishDetectionRadiusUIScale()
{
	m_uiScale.y *= m_fishDetectionRadius;
	m_fishDetectionRadiusUI.SetScale(m_uiScale);
}

void FishDetectionRadius::SetFishDetectionRadiusUIPosition()
{
	m_tensionGauge = FindGO<TensionGauge>("tensionGauge");
	m_fishDetectionRadiusUIPosition = m_tensionGauge->GetFishUIPosition();
	m_fishDetectionRadiusUIPosition.y = 0.0f;
	m_fishDetectionRadiusUI.SetPosition(m_fishDetectionRadiusUIPosition);
}
