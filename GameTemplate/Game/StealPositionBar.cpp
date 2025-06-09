#include "stdafx.h"
#include "StealPositionBar.h"
#include "PositionSelection.h"
#include "Enemy.h"

StealPositionBar::StealPositionBar()
{
}

void StealPositionBar::DisplayUI(RenderContext& rc)
{
	m_stealPositionBarOutsideUI.Draw(rc);
	m_stealPositionGaugeUI.Draw(rc);
	m_stealPositionBarInsideUI.Draw(rc);
		

}

bool StealPositionBar::Init()
{
	m_stealPositionBarOutsideUI.Init("Assets/modelData/landscape_gauge_inside.DDS", 500, 100);
	m_stealPositionBarOutsideUI.SetPivot(Vector2(0.5f, 0.5f));
	m_stealPositionBarOutsideUI.SetPosition(Vector3{ 500.0f, 390.0f, 0.0f });
	m_stealPositionBarOutsideUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_stealPositionBarOutsideUI.Update();

	m_stealPositionBarInsideUI.Init("Assets/modelData/landscape_gauge_outer.DDS", 500, 100);
	m_stealPositionBarInsideUI.SetPivot(Vector2(0.5f, 0.5f));
	m_stealPositionBarInsideUI.SetPosition(Vector3{ 500.0f, 390.0f, 0.0f });
	m_stealPositionBarInsideUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_stealPositionBarInsideUI.Update();

	m_stealPositionGaugeUI.Init("Assets/modelData/cast_successful.DDS", 500.0f, 100);
	m_stealPositionGaugeUI.SetPivot(Vector2(0.0f, 0.5f));
	m_stealPositionGaugeUI.SetPosition(Vector3{ 500.0f - 240.0f, 390.0f, 0.0f });

	return true;
}

bool StealPositionBar::Start()
{
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_enemy = FindGO<Enemy>("enemy");
	return true;
}

void StealPositionBar::Update()
{
	//ゲージを更新
	UpdateStealGauge(m_gaugeDeltaPerFrame);
	//バーの長さを決める。
	SetBarLength();

	if (CanUseGauge()/*ゲージを使える状態か判定*/) {
		if (g_pad[0]->IsTrigger(enButtonB)) {//Bボタンを押したら。
			UseStealGauge();
		}
	}
	

}

void StealPositionBar::SetBarLength()
{
	

	m_barRate = (m_stealPoint / m_stealGaugeThreshold)- GetStockCount();//バーの割合を求める。
	m_bar_Length = m_max_barLength*m_barRate;//マックスの長さに割合を掛けて表示する長さを求める。
	m_stealPositionGaugeUI.SetScale(Vector3{ m_bar_Length, 1.0f, 1.0f });
	m_stealPositionGaugeUI.Update();
}

void StealPositionBar::UpdateStealGauge(float addPoint)
{
	m_stealPoint += addPoint;
}

void StealPositionBar::UseStealGauge()
{
	//敵が釣りをしていと伝える。
	m_enemy->SetIsFishingInArea(false);
	//敵のフィッシングエリアターゲットにスコアが低い魚がいる場所をセット。
	m_enemy->SetTargetFishingArea(m_positionSelection->FindFishLowScore());
}

int StealPositionBar::GetStockCount()
{
	m_stockCount = m_stealPoint / m_stealGaugeThreshold;
	return m_stockCount;
}

bool StealPositionBar::CanUseGauge()
{
	if (GetStockCount() >= 1) {
		//プレイヤーの今いるエリアと敵の今いるエリアが同じなら
		if (m_positionSelection->GetCurrentArea() == Area::ENEMY_SAME_POSITION) {
			return true;
		}
	}
	else {
		return false;
	}
}
