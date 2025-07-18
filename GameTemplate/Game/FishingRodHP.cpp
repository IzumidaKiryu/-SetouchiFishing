#include "stdafx.h"
#include "FishingRodHP.h"
#include "TensionGauge.h"
#include "PlayFishing.h"
#include "PositionSelection.h"
#include "SceneFightFish.h"
#include "FightFishState.h"
#include "BuffManager.h"

namespace {
	// HP減少係数（魚の向きが上の場合）
	static constexpr float ROD_HP_DECAY_UPWARD_MULTIPLIER = 16000.0f;

	// HP減少係数（魚の向きが下の場合）
	static constexpr float ROD_HP_DECAY_DOWNWARD_MULTIPLIER = 20.0f;

	// 回復計算に使う定数
	static constexpr float RECOVERY_BONUS = 0.5f;
	static constexpr float RECOVERY_EXPONENT = 1.5f;

	// 力倍率の計算式に使う指数とスケーリング係数
	static constexpr float POWER_EXPONENT = 0.4f;
	static constexpr float POWER_SCALING = 15.0f;

	// プレイヤーアイコン切り替えの閾値
	static constexpr float PLAYER_ICON_THRESHOLD_LOW = 0.2f;
	static constexpr float PLAYER_ICON_THRESHOLD_HIGH = 0.8f;

	// 最大HPと回復基礎量
	static constexpr float MAX_HP = 200.0f;
	static constexpr float BASE_RECOVERY = 1.0f;

	// スタミナゲージの色を補間する際の中間基準値。
	// HP割合がこの値（0.5）を上回ると、中～高HP用の色で補間され、
	// 下回ると、低～中HP用の色で補間される。
	static constexpr float STAMINA_COLOR_INTERPOLATION_THRESHOLD = 0.5f;

	// UI各要素の座標とスケール
	static const Vector3 ROD_HP_GAUGE_POSITION = { -450.0f, -300.0f, 0.0f };
	static const Vector3 ROD_HP_GAUGE_SCALE = { 1.5f, 1.0f, 1.0f };
	static const Vector3 ROD_HP_BAR_POSITION = { -430.0f, -300.0f, 0.0f };
	static const Vector3 STAMINA_POSITION = { -200.0f, -300.0f, 0.0f };
	static const Vector3 REEL_CHANCE_UI_POSITION = { 430.0f, -100.0f, 0.0f };
	static const Vector3 ROTATE_LSTICK_POSITION = { -800.0f, -400.0f, 0.0f };
	static const Vector3 PLAYER_ICON_POSITION = { 0.0f, -300.0f, 0.0f };

	// UIサイズ（横幅, 縦幅）
	static constexpr float GAUGE_WIDTH = 510.0f;
	static constexpr float GAUGE_HEIGHT = 110.0f;

	static constexpr float BAR_WIDTH = 365.0f;
	static constexpr float BAR_HEIGHT = 85.0f;

	static constexpr float STAMINA_WIDTH = 300.0f;
	static constexpr float STAMINA_HEIGHT = 150.0f;

	static constexpr float CHANCE_UI_WIDTH = 200.0f;
	static constexpr float CHANCE_UI_HEIGHT = 200.0f;

	static constexpr float PLAYER_ICON_WIDTH = 150.0f;
	static constexpr float PLAYER_ICON_HEIGHT = 150.0f;

	static constexpr float ROTATE_LSTICK_UI_WIDTH = 200.0f;
	static constexpr float ROTATE_LSTICK_UI_HEIGHT = 200.0f;

	//UIピボット
	static const Vector2 ROD_HP_GAUGE_INSIDE_PIVOT = Vector2(0.0f,0.5f);
	static const Vector2 ROD_HP_GAUGE_OUTSIDE_PIVOT = Vector2(0.0f, 0.5f);
	static const Vector2 ROD_HP_BAR_PIVOT = Vector2(0.0f, 0.5f);


}

FishingRodHP::FishingRodHP()
{
	m_Hp = MAX_HP; // 初期HPを最大値で設定
	SetUI();       // UI要素の初期化
}

FishingRodHP::~FishingRodHP() = default;

void FishingRodHP::Update()
{
	UpdateFishingRodHP(); // HPの加減算処理

	// HPゲージの更新
	float m_rotationPower = m_fightFishState->GetRotationPower();
	m_RodHPBar.SetScale(Vector3{ m_Hp * 2 / MAX_HP, 1.0f, 1.0f });
	m_RodHPBar.Update();

	CalculatePowerMultiplier(); // 力倍率の更新
	m_previousFrameHP = m_Hp;

	UpdateStaminaGaugeColor(); // 色の更新
}

bool FishingRodHP::Start()
{
	// 必要な外部オブジェクトを検索
	m_fightFishState = FindGO<FightFishState>("fightFishState");
	m_positionSelection = FindGO<PositionSelection>("m_PositionSelection");
	m_buffManager = FindGO<BuffManager>("buffManager");
	m_playFishing = FindGO<PlayFishing>("playFishing");

	return true;
}

float FishingRodHP::CalculateRecoveryAmount()
{
	// HP割合に基づいて回復倍率を計算（低HP時ほど回復量が少ない）
	float recoveryMultiplier = std::pow((m_Hp / MAX_HP), RECOVERY_EXPONENT) + RECOVERY_BONUS;
	return recoveryMultiplier;
}

void FishingRodHP::Recover()
{
	float m_rotationPower = m_fightFishState->GetRotationPower();

	// 回転していない場合、HPを回復
	if (m_rotationPower <= 0.0f) {
		m_Hp += BASE_RECOVERY * CalculateRecoveryAmount() * (1 + m_buffManager->GetTotalStaminaRegenBuff());
	}
}

void FishingRodHP::UpdateFishingRodHP()
{
	// 魚が上を向いている → 多くのダメージ
	if (m_fightFishState->GetFishFacing() == Upward) {
		m_Hp -= m_fightFishState->GetRotationPower() * ROD_HP_DECAY_UPWARD_MULTIPLIER * m_playFishing->GetFishData().escapeForce;
	}

	// 魚が下を向いている → 少量のダメージ
	if (m_fightFishState->GetFishFacing() == Downward) {
		m_Hp -= m_fightFishState->GetRotationPower() * ROD_HP_DECAY_DOWNWARD_MULTIPLIER;
	}

	// 下限チェック
	if (m_Hp < 0) {
		m_Hp = 0.0f;
	}

	Recover(); // 回復処理

	// 上限チェック
	if (m_Hp > MAX_HP) {
		m_Hp = MAX_HP;
	}
}

void FishingRodHP::SetUI()
{
	// HPゲージ内部
	m_RodHPGaugeInside.Init("Assets/modelData/landscape_gauge_inside.DDS", GAUGE_WIDTH, GAUGE_HEIGHT);
	m_RodHPGaugeInside.SetPivot(ROD_HP_GAUGE_INSIDE_PIVOT);
	m_RodHPGaugeInside.SetPosition(ROD_HP_GAUGE_POSITION);
	m_RodHPGaugeInside.SetScale(ROD_HP_GAUGE_SCALE);
	m_RodHPGaugeInside.Update();

	// HPゲージ外部
	m_RodHPGaugeOutside.Init("Assets/modelData/landscape_gauge_outer.DDS", GAUGE_WIDTH, GAUGE_HEIGHT);
	m_RodHPGaugeOutside.SetPivot(ROD_HP_GAUGE_OUTSIDE_PIVOT);
	m_RodHPGaugeOutside.SetPosition(ROD_HP_GAUGE_POSITION);
	m_RodHPGaugeOutside.SetScale(ROD_HP_GAUGE_SCALE);
	m_RodHPGaugeOutside.Update();

	// HPバー
	m_RodHPBar.Init("Assets/sprite/staminaGauge.DDS", BAR_WIDTH, BAR_HEIGHT);
	m_RodHPBar.SetPivot(ROD_HP_BAR_PIVOT);
	m_RodHPBar.SetPosition(ROD_HP_BAR_POSITION);
	m_RodHPBar.SetScale(ROD_HP_GAUGE_SCALE);
	m_RodHPBar.Update();

	// スタミナアイコン
	m_stamina.Init("Assets/modelData/Stamina/stamina.DDS", STAMINA_WIDTH, STAMINA_HEIGHT);
	m_stamina.SetPivot(Vector2::Zero);
	m_stamina.SetPosition(STAMINA_POSITION);
	m_stamina.Update();

	// チャンスUI
	m_reelChanceUI.Init("Assets/modelData/PromptUI/ReelChance.DDS", CHANCE_UI_WIDTH, CHANCE_UI_HEIGHT);
	m_reelChanceUI.SetPosition(REEL_CHANCE_UI_POSITION);
	m_reelChanceUI.SetPivot(Vector2::Zero);
	m_reelChanceUI.Update();

	// 回転操作UI
	m_rotateLStickUI.Init("Assets/modelData/PromptUI/RotateLStick.DDS", ROTATE_LSTICK_UI_WIDTH, ROTATE_LSTICK_UI_HEIGHT);
	m_rotateLStickUI.SetPivot(Vector2::Zero);
	m_rotateLStickUI.SetPosition(ROTATE_LSTICK_POSITION);
	m_rotateLStickUI.Update();

	// プレイヤーアイコン（通常・元気・疲労）
	m_playerIcon.Init("Assets/modelData/PlayerIcon/PlayerUI.DDS", PLAYER_ICON_WIDTH, PLAYER_ICON_HEIGHT);
	m_playerIcon.SetPosition(PLAYER_ICON_POSITION);
	m_playerIcon.SetPivot(Vector2::Zero);
	m_playerIcon.Update();

	m_playerIconFine.Init("Assets/modelData/PlayerIcon/PlayerUIFine.DDS", PLAYER_ICON_WIDTH, PLAYER_ICON_HEIGHT);
	m_playerIconFine.SetPosition(PLAYER_ICON_POSITION);
	m_playerIconFine.SetPivot(Vector2::Zero);
	m_playerIconFine.Update();

	m_playerIconTired.Init("Assets/modelData/PlayerIcon/PlayerUITired.DDS", PLAYER_ICON_WIDTH, PLAYER_ICON_HEIGHT);
	m_playerIconTired.SetPivot(Vector2::Zero);
	m_playerIconTired.SetPosition(PLAYER_ICON_POSITION);
	m_playerIconTired.Update();

}

void FishingRodHP::Render(RenderContext& rc)
{
	// 各種UIを描画
	m_RodHPGaugeInside.Draw(rc);
	m_RodHPBar.Draw(rc);
	m_RodHPGaugeOutside.Draw(rc);
	m_stamina.Draw(rc);
	m_rotateLStickUI.Draw(rc);

	if (m_fightFishState->GetFishFacing() == Downward) {
		m_reelChanceUI.Draw(rc);
	}

	// HP割合に応じてプレイヤーアイコン切り替え
	if (m_Hp / MAX_HP < PLAYER_ICON_THRESHOLD_LOW) {
		m_playerIconTired.Draw(rc);
	}
	else if (m_Hp / MAX_HP <= PLAYER_ICON_THRESHOLD_HIGH) {
		m_playerIcon.Draw(rc);
	}
	else {
		m_playerIconFine.Draw(rc);
	}
}

void FishingRodHP::SetIsFishingEnded(bool isFishingEnded)
{
	m_isFishingEnded = isFishingEnded;
}

void FishingRodHP::CalculatePowerMultiplier()
{
	// HPに基づいて魚の引きの強さを調整
	m_powerMultiplier = std::pow((m_Hp / MAX_HP), POWER_EXPONENT);
	m_powerMultiplier *= POWER_SCALING;
}

float FishingRodHP::GetPowerMultiplier()
{
	return m_powerMultiplier;
}

void FishingRodHP::UpdateStaminaGaugeColor()
{
	// HPの割合（0.0 ～ 1.0）を計算
	const float hpRatio = m_Hp / MAX_HP;

	// ゲージ色を HP に応じて線形補間する
	if (hpRatio > STAMINA_COLOR_INTERPOLATION_THRESHOLD) {
		// 0.5 ～ 1.0 の範囲 → 中間色から高HP色へ補間
		const float t = (hpRatio - STAMINA_COLOR_INTERPOLATION_THRESHOLD) / STAMINA_COLOR_INTERPOLATION_THRESHOLD;
		staminaGaugeColor.Lerp(t,m_midStaminaGaugeColor, m_highStaminaGaugeColor);
	}
	else {
		// 0.0 ～ 0.5 の範囲 → 低HP色から中間色へ補間
		const float t = hpRatio / STAMINA_COLOR_INTERPOLATION_THRESHOLD;
		staminaGaugeColor.Lerp(t,m_lowStaminaGaugeColor, m_midStaminaGaugeColor);
	}

	// 色をUIに反映
	m_RodHPBar.SetMulColor(staminaGaugeColor);
}
