#include "stdafx.h"
#include "PlayCastGaugeState.h"
#include "CastGauge.h"
#include"PlayFishing.h"
#include"Player.h"

PlayCastGaugeState::PlayCastGaugeState()
{
	m_castGauge = NewGO<CastGauge>(0,"castGauge");
	SetCurrentFishRangeAndMaxRangeRate(m_fishData.initPos);
}

PlayCastGaugeState::~PlayCastGaugeState()
{
	DeleteGO(m_castGauge);
}

void PlayCastGaugeState::Update()
{
	m_player=FindGO<Player>("player_Playfishing");
	m_playFishing = FindGO<PlayFishing>("playFishing");


	SetCamera(
		m_player->m_position + Vector3{0.0f,100.0f,100.0f},
		GetFishModelPosition() + m_playFishing->m_floating
	);


	//魚の場所を決める。
	SumFishModelPosition(m_sum_current_fish_range_and_max_range_rate);
	//場所を反映させる。
	SetFish();
	if (m_castGauge->GetIsThisClasEnd()) {
		SetSuccess();
	}
}
