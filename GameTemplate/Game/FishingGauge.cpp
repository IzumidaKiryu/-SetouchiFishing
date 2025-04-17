#include "stdafx.h"
#include "FishingGauge.h"
#include "TensionGauge.h"
#include"Playfishing.h"


FishingGauge::FishingGauge()
{

	m_fishingGaugeFrame.Init("Assets/modelData/fishingGaugeFrame.DDS", 100, 500);
	m_fishingGaugeFrame.SetPivot(Vector2(0.0f, 0.5f));
	m_fishingGaugeFrame.SetPosition(Vector3(-500.0f, 0.0f, 0.0f));
	m_fishingGaugeFrame.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_fishingGaugeFrame.Update();

	m_fishingGauge.Init("Assets/modelData/fishingGauge.DDS", 100, 500);
	m_fishingGauge.SetPivot(Vector2(0.0f, 0.5f));
	m_fishingGauge.SetPosition(Vector3(-500.0f, 0.0f, 0.0f));
	m_fishingGauge.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_fishingGauge.Update();

	m_fishingGaugeBar.Init("Assets/modelData/fishingGaugeBar.DDS", 110, 10);
	m_fishingGaugeBar.SetPivot(Vector2(0.0f, 0.5f));
	m_fishingGaugeBar.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });

	/*m_gaugeBarSuccessful = NewGO<GaugeCastSuccessful>(0, "gaugeCastSuccessful");
	m_gaugeBarSuccessful->Init(10.0f, 10.0f);*/
}

FishingGauge::~FishingGauge()
{

}

void FishingGauge::Update()
{
	SetBarSpead();
	UpAndDownManagement();//バーの動く向きを決める。
	SetBarPosition();//バーの場所を決める。
	m_fishingGaugeBar.Update();//バーの描画を更新する。
	HitTest();

}

/// <summary>
/// 矢印の場所を設定
/// </summary>
void FishingGauge::SetBarPosition()
{
	m_fishingGaugeBar.SetPosition(Vector3(-490.0f, m_barPosition, 0.0f));
}

/// <summary>
/// 矢印を上に動かすか下に動かすか決める。
/// </summary>
void FishingGauge::UpAndDownManagement()
{
	/*if (upState == false) {*/
	DownwardOperation();
	//}
	//if (upState == true) {
	//	UpwardOperation();
	//}
}
/// <summary>
/// 矢印を上に移動。
/// </summary>
void FishingGauge::UpwardOperation()
{
	m_barPosition += m_barSpead;
	if (m_barPosition >= m_barUpperLimit) {
		m_barPosition = (m_barPosition - m_barUpperLimit) + m_barLowerLimit;//上限を通り過ぎたらその分戻る処理。
		upState = false;
	}
}

/// <summary>
/// 矢印を下に移動
/// </summary>
void FishingGauge::DownwardOperation()
{
	m_barPosition -= m_barSpead;
	if (m_barPosition <= m_barLowerLimit) {
		m_barPosition = (m_barPosition - m_barLowerLimit) + m_barUpperLimit;//下限を通り過ぎたらその分戻る処理。
		upState = true;
	}
}

/// <summary>
/// 矢印のスピードを設定
/// </summary>
void FishingGauge::SetBarSpead()
{
	m_barSpead = /*(237.0f*2.0f)/10*/9;
}

/// <summary>
/// ボタンを押したときの処理。
/// </summary>
void FishingGauge::HitTest()
{
	if (g_pad[0]->IsTrigger(enButtonA)) {
		Attack();
		m_playFishing = FindGO<PlayFishing>("playFishing");
		m_playFishing->SetSuccess();
		/*m_playFishing->StatusManager();*/
	/*	DeleteGO(this);*/
	}

}

void FishingGauge::Render(RenderContext& rc)
{
	m_fishingGauge.Draw(rc);
	//m_gaugeCastSuccessful->m_gaugeCastSuccessfulSprite.Draw(rc);
	m_fishingGaugeBar.Draw(rc);
	m_fishingGaugeFrame.Draw(rc);
}

void FishingGauge::Attack()
{
	m_attack = 1 - ((-m_barPosition + 237.0f) / 474.0f * 0.5f);
}
