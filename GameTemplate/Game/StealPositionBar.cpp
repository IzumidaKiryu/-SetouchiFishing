#include "stdafx.h"
#include "StealPositionBar.h"
#include "PositionSelection.h"
#include "Enemy.h"
#include "BuffManager.h"

StealPositionBar::StealPositionBar()
{
	InitisStealLockActive();
}

void StealPositionBar::DisplayUI(RenderContext& rc)
{
	m_stealPositionBarOutsideUI.Draw(rc);
	m_stealPositionGaugeUI.Draw(rc);
	m_stealPositionBarInsideUI.Draw(rc);
	if (CanUseGauge()) {
		m_takeOver.Draw(rc);
	}
	else {
		m_takeOver_gray.Draw(rc);
	}
	m_stockCountUI.Draw(rc);

	m_clossUI.Draw(rc);
}

bool StealPositionBar::Init()
{
	m_stealPositionBarOutsideUI.Init("Assets/modelData/landscape_gauge_inside.DDS", 510, 110);
	m_stealPositionBarOutsideUI.SetPivot(Vector2(0.5f, 0.5f));
	m_stealPositionBarOutsideUI.SetPosition(Vector3{ 400.0f, 390.0f, 0.0f });
	m_stealPositionBarOutsideUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_stealPositionBarOutsideUI.Update();

	m_stealPositionBarInsideUI.Init("Assets/modelData/landscape_gauge_outer.DDS", 510, 110);
	m_stealPositionBarInsideUI.SetPivot(Vector2(0.5f, 0.5f));
	m_stealPositionBarInsideUI.SetPosition(Vector3{ 400.0f, 390.0f, 0.0f });
	m_stealPositionBarInsideUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_stealPositionBarInsideUI.Update();

	m_stealPositionGaugeUI.Init("Assets/modelData/takeOver/takeOverGauge.DDS", 500.0f, 100);
	m_stealPositionGaugeUI.SetPivot(Vector2(0.0f, 0.5f));
	m_stealPositionGaugeUI.SetPosition(Vector3{ 160.0f, 390.0f, 0.0f });

	m_takeOver_gray.Init("Assets/modelData/takeOver/takeOver_gray.DDS", 200.0f, 100);
	m_takeOver_gray.SetPivot(Vector2(0.0f, 0.5f));
	m_takeOver_gray.SetPosition(Vector3{ -50.0f, 390.0f, 0.0f });
	m_takeOver_gray.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_takeOver_gray.Update();

	m_takeOver.Init("Assets/modelData/takeOver/takeOver.DDS", 200.0f, 100);
	m_takeOver.SetPivot(Vector2(0.0f, 0.5f));
	m_takeOver.SetPosition(Vector3{ -50.0f, 390.0f, 0.0f });
	m_takeOver.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_takeOver.Update();

	m_clossUI.Init("Assets/modelData/takeOver/Cross.DDS", 30.0f, 30.0f);
	m_clossUI.SetPivot(Vector2(0.0f, 0.5f));
	m_clossUI.SetPosition(Vector3{ 650.0f, 370.0f, 0.0f });
	m_clossUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_clossUI.Update();


	return true;
}

bool StealPositionBar::Start()
{
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_enemy = FindGO<Enemy>("enemy");
	m_buffManager = FindGO<BuffManager>("buffManager");
	return true;
}

void StealPositionBar::Update()
{
	//ゲージを更新
	UpdateStealGauge();
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

void StealPositionBar::UpdateStealGauge()
{
	m_stealPoint += m_gaugeDeltaPerFrame*(1+m_buffManager->GetTotalStealBoostBuff());
	SetStockCounUI();
}

void StealPositionBar::UseStealGauge()
{
	//ポイントを減らす。
	m_stealPoint -= m_stealGaugeThreshold;
	//魚が逃げないように魚をロックする。
	SetIsStealLockActive(true, m_enemy->GetTargetFishinArea());

	//敵が釣りをしていないと伝える。
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
		else {
			return false;
		}

	}
	else {
		return false;
	}
}

void StealPositionBar::SetIsStealLockActive(bool isActive, Area area)
{
	for (int i=0; i < 6; i++) {
		//指定されたエリアの真偽値をセット。
		if (static_cast<Area>(i) == area) {
			m_isStealLockActive[static_cast<int>(area)] = isActive;
		}
		//指定されたもの以外すべてfalseにする。
		else {
			m_isStealLockActive[i] = false;
		}
	}
}

bool StealPositionBar::GetIsStealLockActive(Area area)
{
	return m_isStealLockActive[static_cast<int>(area)];
}

bool StealPositionBar::IsAnyStealLockActive()
{
	for (int i = 0; i < 6; ++i) {
		if (m_isStealLockActive[i]) {
			return true;
		}
	}
	return false;
}

void StealPositionBar::SetStockCounUI()
{
		wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%d", int(m_stockCount));

	//表示するテキストを設定。
	m_stockCountUI.SetText(wcsbuf);
	//フォントの位置を設定。
	m_stockCountUI.SetPosition(Vector3(800.0f, 530.0f, 0.0f));
	//フォントの大きさを設定。
	m_stockCountUI.SetScale(3.0f);
	//フォントの色を設定。
	m_stockCountUI.SetColor({ 1.0f,0.3f,0.0f,1.0f });
}

void StealPositionBar::InitisStealLockActive()
{
	m_isStealLockActive[static_cast<int>(Area::A)] = false;
	m_isStealLockActive[static_cast<int>(Area::B)] = false;
	m_isStealLockActive[static_cast<int>(Area::C)] = false;
	m_isStealLockActive[static_cast<int>(Area::D)] = false;
	m_isStealLockActive[static_cast<int>(Area::E)] = false;
	m_isStealLockActive[static_cast<int>(Area::F)] = false;

}