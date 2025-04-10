#include "stdafx.h"
#include "CastGauge.h"
#include "GaugeCastSuccessful.h"
#include "TensionGauge.h"
#include "FishingGauge.h"

CastGauge::CastGauge()
{
	m_castGaugeOutside.Init("Assets/modelData/castGauge_Outside.DDS", 100, 500);
	m_castGaugeOutside.SetPivot(Vector2(0.0f, 0.5f));
	m_castGaugeOutside.SetPosition(Vector3(500.0f, 0.0f, 0.0f));
	m_castGaugeOutside.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_castGaugeOutside.Update();

	m_castGaugeInside.Init("Assets/modelData/castGauge_inside.DDS", 100, 500);
	m_castGaugeInside.SetPivot(Vector2(0.0f, 0.5f));
	m_castGaugeInside.SetPosition(Vector3(500.0f, 0.0f, 0.0f));
	m_castGaugeInside.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_castGaugeInside.Update();

	m_castGaugeArrow.Init("Assets/modelData/castGauge_arrow.DDS", 110, 10);
	m_castGaugeArrow.SetPivot(Vector2(0.0f, 0.5f));
	m_castGaugeArrow.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });

	m_gaugeCastSuccessful = NewGO<GaugeCastSuccessful>(0, "gaugeCastSuccessful");
	m_gaugeCastSuccessful->Init(10.0f, 10.0f);
}

CastGauge::~CastGauge()
{
	DeleteGO(m_gaugeCastSuccessful);
}

void CastGauge::Update()
{
	SetGaugeSpead();
	UpAndDownManagement();//矢印の動く向きを決める。
	SetArrowPosition();//矢印の場所を決める。
	m_castGaugeArrow.Update();//矢印の描画を更新する。
	HitTest();
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
	m_gaugeSpead = /*(237.0f*2.0f)/10*/5;
}

void CastGauge::HitTest()
{
	if (g_pad[0]->IsTrigger(enButtonA)) {
		if (m_gaugeCastSuccessful->hitTest(m_arrowPosition) == true)
		{
			/*m_fishingGauge=NewGO<FishingGauge>(0, "fishingGauge ");*/
			/*tensionGauge = NewGO<TensionGauge>(0, "tensionGauge");*/
			Success();
		}

		else if (m_gaugeCastSuccessful->hitTest(m_arrowPosition) == false) //失敗したら。
		{
			Failure();
		}
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
	m_playFishing->SetSuccess();
}

void CastGauge::Render(RenderContext& rc)
{
	m_castGaugeInside.Draw(rc);
	m_gaugeCastSuccessful->m_gaugeCastSuccessfulSprite.Draw(rc);
	m_castGaugeArrow.Draw(rc);
	m_castGaugeOutside.Draw(rc);
}
