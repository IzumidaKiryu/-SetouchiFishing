#include "stdafx.h"
#include "CastGauge.h"
#include "PlayFishing.h"

// キャストゲージのUI設定用定数
namespace {
	constexpr float CAST_GAUGE_WIDTH = 100.0f;				// キャストゲージの幅
	constexpr float CAST_GAUGE_HEIGHT = 500.0f;				// キャストゲージの高さ
	const Vector2 CASTGAUGE_PIVOT(0.0f, 0.5f);     	// キャストゲージの基準位置
	const Vector3 CASTGAUGE_POSITION(-500.0f, 0.0f, 0.0f); // キャストゲージの表示位置

	constexpr float ARROW_WIDTH = 110.0f;   					// 矢印の幅
	constexpr float ARROW_HEIGHT = 10.0f;   					// 矢印の高さ
	const Vector2 ARROW_PIVOT(0.0f, 0.5f);				// 矢印の基準位置
}

CastGauge::CastGauge() = default;
CastGauge::~CastGauge() = default;

bool CastGauge::Init() {
	m_castGaugeOutside.Init("Assets/modelData/castGauge_Outside.DDS", CAST_GAUGE_WIDTH, CAST_GAUGE_HEIGHT);
	m_castGaugeOutside.SetPivot(CASTGAUGE_PIVOT);
	m_castGaugeOutside.SetPosition(CASTGAUGE_POSITION);
	m_castGaugeOutside.Update();

	m_castGaugeInside.Init("Assets/modelData/new_castgauge.DDS", CAST_GAUGE_WIDTH, CAST_GAUGE_HEIGHT);
	m_castGaugeInside.SetPivot(CASTGAUGE_PIVOT);
	m_castGaugeInside.SetPosition(CASTGAUGE_POSITION);
	m_castGaugeInside.Update();

	m_Arrow.Init("Assets/modelData/castGauge_arrow.DDS", ARROW_WIDTH, ARROW_HEIGHT);
	m_Arrow.SetPivot(ARROW_PIVOT);

	return true;
}

bool CastGauge::Start() {
	m_playFishing = FindGO<PlayFishing>("playFishing");
	return true;
}

void CastGauge::Update() {
	UpAndDownManagement();		// ゲージの上下制御
	UpdateArrowPosition();		// 矢印の位置更新
	m_Arrow.Update();
	HandleCastInput();		// Aボタンの入力処理
}

void CastGauge::UpdateArrowPosition() {
	m_Arrow.SetPosition(CASTGAUGE_POSITION + Vector3(-10.0f, m_arrowPosition, 0.0f));
}

void CastGauge::UpAndDownManagement() {
	if (upState)
		UpwardOperation();
	else
		DownwardOperation();
}

void CastGauge::UpwardOperation() {
	m_arrowPosition += m_gaugeSpead;
	if (m_arrowPosition >= m_gaugeUpperLimit) {
		// 上限を超えたら反転して戻る
		m_arrowPosition = (-m_arrowPosition + m_gaugeUpperLimit) + m_gaugeUpperLimit;
		upState = false;
	}
}

void CastGauge::DownwardOperation() {
	m_arrowPosition -= m_gaugeSpead;
	if (m_arrowPosition <= m_gaugeLowerLimit) {
		// 下限を超えたら反転して戻る
		m_arrowPosition = (-m_arrowPosition + m_gaugeLowerLimit) + m_gaugeLowerLimit;
		upState = true;
	}
}

void CastGauge::SetArrowSpead(float spead) {
	m_gaugeSpead = spead;
}

void CastGauge::HandleCastInput() {
	if (g_pad[0]->IsTrigger(enButtonA)) {
		// 強さを0.0〜1.0の範囲で計算
		m_castStrength = (m_arrowPosition - m_gaugeLowerLimit) / m_gauge_length;
		m_isCastInputComplete = true;

		// フィッシングクラスに通知
		m_playFishing->SetCastStrength(m_castStrength);
		m_playFishing->SetSuccess();
	}
}

bool CastGauge::GetIsCastInputComplete() const {
	return m_isCastInputComplete;
}

void CastGauge::Render(RenderContext& rc) {
	m_castGaugeInside.Draw(rc);
	m_Arrow.Draw(rc);
	m_castGaugeOutside.Draw(rc);
}
