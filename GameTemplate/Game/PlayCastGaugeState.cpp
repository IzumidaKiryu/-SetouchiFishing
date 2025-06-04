#include "stdafx.h"
#include "PlayCastGaugeState.h"
#include "CastGauge.h"
#include"PlayFishing.h"
#include"Player.h"

PlayCastGaugeState::PlayCastGaugeState()
{
}

PlayCastGaugeState::~PlayCastGaugeState()
{
	DeleteGO(m_castGauge);
}

bool PlayCastGaugeState::OnInit()
{
	SetCurrentFishRangeAndMaxRangeRate(m_fishData.initPos);

	return true;
}

bool PlayCastGaugeState::OnStart()
{


	m_castGauge = NewGO<CastGauge>(0, "castGauge");
	m_castGauge->Init();


	SetArrowSpead();

	return true;
}

void PlayCastGaugeState::Update()
{
	m_player = FindGO<Player>("player_Playfishing");
	m_playFishing = FindGO<PlayFishing>("playFishing");
	//カメラを管理する。
	CameraManagement();
	//魚の場所を決める。
	SumFishModelPosition(m_current_fish_range_and_max_range_rate);
	//場所を反映させる。
	SetFish();
	if (m_castGauge->GetIsThisClasEnd()) {
		SetSuccess();
	}
}

void PlayCastGaugeState::CameraManagement()
{
	m_cameraPos = m_player->m_position + Vector3{ 0.0f,100.0f,100.0f };
	m_cameraTarget = GetFishModelPosition() + Floating(CameraPattern);

	SetCamera(
		m_cameraPos,
		m_cameraTarget
	);
}

void PlayCastGaugeState::SetArrowSpead()
{
	m_castGauge->SetArrowSpead(m_fishData.arrowSpeed);
}
