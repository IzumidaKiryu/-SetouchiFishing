#include "stdafx.h"
#include "PlayCastGaugeState.h"
#include "CastGauge.h"
#include"PlayFishing.h"
#include"Player.h"

PlayCastGaugeState::PlayCastGaugeState()
{
	m_castGauge = NewGO<CastGauge>(0, "castGauge");
	SetCurrentFishRangeAndMaxRangeRate(m_fishData.initPos);
	SetArrowSpead();
}

PlayCastGaugeState::~PlayCastGaugeState()
{
	DeleteGO(m_castGauge);
}

void PlayCastGaugeState::Update()
{
	m_player = FindGO<Player>("player_Playfishing");
	m_playFishing = FindGO<PlayFishing>("playFishing");
	//カメラを管理する。
	CameraManagement();
	//魚の場所を決める。
	SumFishModelPosition(m_sum_current_fish_range_and_max_range_rate);
	//場所を反映させる。
	SetFish();
	if (m_castGauge->GetIsThisClasEnd()) {
		SetSuccess();
	}
}

void PlayCastGaugeState::CameraManagement()
{
	m_cameraPos = m_player->m_position + Vector3{ 0.0f,100.0f,100.0f } + Floating(CameraPattern);
	m_cameraTarget = GetFishModelPosition();

	SetCamera(
		m_cameraPos,
		m_cameraTarget
	);
}

void PlayCastGaugeState::SetArrowSpead()
{
	m_castGauge->SetArrowSpead(m_fishData.arrowSpeed);
}
