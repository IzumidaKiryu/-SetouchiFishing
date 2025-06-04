#include "stdafx.h"
#include "CastGauge.h"
#include "GaugeCastSuccessful.h"
#include "TensionGauge.h"
#include "FishingGauge.h"
#include "PositionSelection.h"
#include "PlayFishing.h"
#include"GameCamera.h"
#include"RodFloatMove.h"
#include"Player.h"
#include"RodFloatMove.h"
#include"SceneFightFish.h"
#include"PlayCastGaugeState.h"



CastGauge::CastGauge()
{



}


CastGauge::~CastGauge()
{
}

bool CastGauge::Init()
{
	m_castGaugeOutside.Init("Assets/modelData/castGauge_Outside.DDS", 100, 500);
	m_castGaugeOutside.SetPivot(Vector2(0.0f, 0.5f));
	m_castGaugeOutside.SetPosition(m_initGaugePos);
	m_castGaugeOutside.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_castGaugeOutside.Update();

	m_castGaugeInside.Init("Assets/modelData/new_castgauge.DDS", 100, 500);
	m_castGaugeInside.SetPivot(Vector2(0.0f, 0.5f));
	m_castGaugeInside.SetPosition(m_initGaugePos);
	m_castGaugeInside.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_castGaugeInside.Update();

	m_Arrow.Init("Assets/modelData/castGauge_arrow.DDS", 110, 10);
	m_Arrow.SetPivot(Vector2(0.0f, 0.5f));
	m_Arrow.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });


	return true;
}

bool CastGauge::Start()
{

	m_positionSelection = FindGO<PositionSelection>("positionSelection");


	return true;
}

void CastGauge::Update()
{
	UpAndDownManagement();
	SetArrowPosition();//矢印の場所を決める。
	m_Arrow.Update();//矢印の描画を更新する。
	HitTest();
}

/// <summary>
/// 矢印の場所を設定
/// </summary>
void CastGauge::SetArrowPosition()
{
	m_Arrow.SetPosition(m_initGaugePos+Vector3(-10.0f, m_arrowPosition, 0.0f));
}

/// <summary>
/// 矢印を上に動かすか下に動かすか決める。
/// </summary>
void CastGauge::UpAndDownManagement()
{
	if (upState == false) {
		DownwardOperation();
	}
	if (upState == true) {
		UpwardOperation();
	}
}
/// <summary>
/// 矢印を上に移動。
/// </summary>
void CastGauge::UpwardOperation()
{
	m_arrowPosition += m_gaugeSpead;
	if (m_arrowPosition >= m_gaugeUpperLimit) {
		m_arrowPosition = (-m_arrowPosition + m_gaugeUpperLimit) + m_gaugeUpperLimit;//上限を通り過ぎたらその分戻る処理。
		upState = false;
	}
}

/// <summary>
/// 矢印を下に移動
/// </summary>
void CastGauge::DownwardOperation()
{
	m_arrowPosition -= m_gaugeSpead;
	if (m_arrowPosition <= m_gaugeLowerLimit) {
		m_arrowPosition = (-m_arrowPosition + m_gaugeLowerLimit) + m_gaugeLowerLimit;//下限を通り過ぎたらその分戻る処理。
		upState = true;
	}
}


/// <summary>
/// 矢印のスピードを設定
/// </summary>

void CastGauge::SetArrowSpead(float spead)
{
	m_gaugeSpead = spead;
}

/// <summary>
/// 当たり判定を確かめる
/// </summary>
void CastGauge::HitTest()
{
	if (g_pad[0]->IsTrigger(enButtonA)) {

		//ウキの距離を計算。
		m_castStrength = (m_arrowPosition - m_gaugeLowerLimit) / m_gauge_length;

		m_playFishing = FindGO<PlayFishing>("playFishing");
		m_is_thisClassEnd = true;
		//プレイフィッシングクラスにキャストの強さを渡す。
		m_playFishing->SetCastStrength(m_castStrength);

		m_playFishing->SetSuccess();//プレイフィッシングクラスのステートを進める。
		//
		m_chastState = chast;


		is_ended = true;
	}
}


bool CastGauge::GetIsThisClasEnd()
{
	return m_is_thisClassEnd;
}

void CastGauge::Render(RenderContext& rc)
{
	if (m_chastState == playing) {
		m_castGaugeInside.Draw(rc);
		/*	m_gaugeCastSuccessful->m_gaugeCastSuccessfulSprite.Draw(rc);*/
		m_Arrow.Draw(rc);
		m_castGaugeOutside.Draw(rc);
	}
}
