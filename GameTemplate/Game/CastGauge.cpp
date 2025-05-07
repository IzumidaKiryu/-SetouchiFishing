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


	m_castGaugeOutside.Init("Assets/modelData/castGauge_Outside.DDS", 100, 500);
	m_castGaugeOutside.SetPivot(Vector2(0.0f, 0.5f));
	m_castGaugeOutside.SetPosition(Vector3(500.0f, 0.0f, 0.0f));
	m_castGaugeOutside.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_castGaugeOutside.Update();

	m_castGaugeInside.Init("Assets/modelData/new_castgauge.DDS", 100, 500);
	m_castGaugeInside.SetPivot(Vector2(0.0f, 0.5f));
	m_castGaugeInside.SetPosition(Vector3(500.0f, 0.0f, 0.0f));
	m_castGaugeInside.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_castGaugeInside.Update();

	m_castGaugeArrow.Init("Assets/modelData/castGauge_arrow.DDS", 110, 10);
	m_castGaugeArrow.SetPivot(Vector2(0.0f, 0.5f));
	m_castGaugeArrow.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });

	//m_gaugeCastSuccessful = NewGO<GaugeCastSuccessful>(0, "gaugeCastSuccessful");
	//m_gaugeCastSuccessful->Init(10.0f, 10.0f);

	m_positionSelection = FindGO<PositionSelection>("positionSelection");


}


CastGauge::~CastGauge()
{
	//DeleteGO(m_gaugeCastSuccessful);
}

void CastGauge::Update()
{
	SetCamera();
	ChastStaeManager();
}

/// <summary>
/// 矢印の場所を設定
/// </summary>
void CastGauge::SetArrowPosition()
{
	m_castGaugeArrow.SetPosition(Vector3(490.0f, m_arrowPosition, 0.0f));
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
void CastGauge::SetGaugeSpead()
{
	m_gaugeSpead = /*(237.0f*2.0f)/10*/8;
}

/// <summary>
/// 当たり判定を確かめる
/// </summary>
void CastGauge::HitTest()
{
	if (g_pad[0]->IsTrigger(enButtonA)) {
		//if (m_gaugeCastSuccessful->hitTest(m_arrowPosition) == true)//成功したら。
		//{
		//	/*m_fishingGauge=NewGO<FishingGauge>(0, "fishingGauge ");*/
		//	/*tensionGauge = NewGO<TensionGauge>(0, "tensionGauge");*/
		//	Success();
		//}
		//else if (m_gaugeCastSuccessful->hitTest(m_arrowPosition) == false) //失敗したら。
		//{
		//	Failure();
		//}

		//ウキの距離を計算。
		m_castStrength = (m_arrowPosition - m_gaugeLowerLimit) / m_gauge_length;

		//m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");


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

void CastGauge::Failure()
{
	m_playFishing = FindGO<PlayFishing>("playFishing");
	m_playFishing->SetFailure();
}

void CastGauge::Success()
{
	m_playFishing = FindGO<PlayFishing>("playFishing");
	//m_chastState= character_animation;
	m_chastState = chast;
}

void CastGauge::Chast()
{
	
}

void CastGauge::ChastStaeManager()
{
	switch (m_chastState)
	{
	case playing:
		SetGaugeSpead();
		UpAndDownManagement();//矢印の動く向きを決める。
		SetArrowPosition();//矢印の場所を決める。
		m_castGaugeArrow.Update();//矢印の描画を更新する。
		HitTest();
		break;
	case character_animation:

		break;
	case  chast:
		//m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
		IsCastEnd();
		break;
	default:
		break;
	}
}

void CastGauge::SetCameraPlayingSgtate()
{
	m_player = FindGO<Player>("player");
	WaveMotion();
	m_gameCameraTarget = m_player->m_position + Vector3{ 1000.0f,30.0f,0.0f };
	m_gameCameraTarget += m_waveMotion;
	m_gameCameraPos = m_player->m_position + Vector3{ 0.0f,200.0f,-100.0f };
}

void CastGauge::SetCameraChast()
{
	//m_gameCameraTarget=m_rodFloatMove->m_rodFloatPosition;
}

void CastGauge::SetCamera()
{
	m_gameCamera=FindGO<GameCamera>("PlayFishing_GameCamera");
	switch (m_chastState)
	{
	case playing:
		SetCameraPlayingSgtate();
		break;
	case character_animation:
		SetCameraChast();
		break;
	case chast:
		SetCameraChast();
		break;
	default:
		break;
	}
}
/// <summary>
/// 波の動きを表現。
/// </summary>
void CastGauge::WaveMotion()
{
	t += 0.05;
	m_waveMotion.y = (cos(t));//上下に動かす
	m_waveMotion.z = (cos(t * 0.7/*周期をずらす*/) * 0.5);//左右に動かす
}

void CastGauge::IsCastEnd()
{
	//m_rodFloatMove = FindGO<RodFloatMove>("rodFloatMove");
	/*if (m_rodFloatMove->IsCastEnd() == true) {
		m_playFishing = FindGO<PlayFishing>("playFishing");
		m_playFishing->SetSuccess();
	}*/
}

bool CastGauge::GetIsThisClasEnd()
{
	return m_is_thisClassEnd;
}

//void CastGauge::SetRodFloatPositon()
//{
//	t += 0.1;
//	m_rodFloatPosition=(InitPos+first_velocity_vector*30 * t) + g * t * t * 1 / 2;
//}

void CastGauge::Render(RenderContext& rc)
{
	if (m_chastState== playing) {
		m_castGaugeInside.Draw(rc);
	/*	m_gaugeCastSuccessful->m_gaugeCastSuccessfulSprite.Draw(rc);*/
		m_castGaugeArrow.Draw(rc);
		m_castGaugeOutside.Draw(rc);
	}
}
