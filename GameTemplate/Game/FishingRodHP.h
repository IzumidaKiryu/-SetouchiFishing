#pragma once

// 前方宣言
class TensionGauge;
class PlayFishing;
class PositionSelection;
class SceneFightFish;
class FightFishState;
class BuffManager;

/// <summary>
/// 釣り竿のHP（耐久値）と関連UIを管理するクラス。
/// 魚の動きやプレイヤーの操作に応じてHPを増減し、視覚的に表示する。
/// </summary>
class FishingRodHP : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	FishingRodHP();

	/// <summary>
	/// デストラクタ。
	/// </summary>
	~FishingRodHP();

	/// <summary>
	/// 初期化時の処理。
	/// </summary>
	bool Start();

	/// <summary>
	/// 毎フレームの更新処理。
	/// </summary>
	void Update();

	/// <summary>
	/// UIの描画処理。
	/// </summary>
	void Render(RenderContext& rc);

	/// <summary>
    /// 釣り終了フラグを設定。
    /// </summary>
	void SetIsFishingEnded(bool isFishingEnded);

	/// <summary>
    /// 現在のスタミナ倍率を取得。
    /// </summary>
	float GetPowerMultiplier();

private:

	/// <summary>
	/// 釣り竿のHPの更新処理（ダメージや回復）。
	/// </summary>
	void UpdateFishingRodHP();

	/// <summary>
	/// HPの回復処理。
	/// </summary>
	void Recover();

	/// <summary>
	/// HPの回復量を計算。
	/// </summary>
	float CalculateRecoveryAmount();

	/// <summary>
	/// プレイヤーのスタミナ倍率を計算。
	/// </summary>
	void CalculatePowerMultiplier();

	/// <summary>
	/// ゲージの色を現在のHPに応じて更新。
	/// </summary>
	void UpdateStaminaGaugeColor();

	/// <summary>
	/// UIの初期化処理。
	/// </summary>
	void SetUI();


private:

	// HP関連
	float m_Hp;                                 // 現在のHP
	float m_previousFrameHP = 0.0f;             // 前フレーム時点のHP
	float m_powerMultiplier = 0.0f;             // プレイヤーの力の倍率
	bool m_isFishingEnded = false;      // 釣り終了フラグ

	// スタミナゲージの色設定
	Vector3 staminaGaugeColor = Vector3(0.0f, 0.0f, 0.0f);
	const Vector3 m_highStaminaGaugeColor = Vector3(0.0f, 1.0f, 0.0f);   // 高HP時の色（緑）
	const Vector3 m_midStaminaGaugeColor = Vector3(1.0f, 1.0f, 0.0f);   // 中HP時の色（黄）
	const Vector3 m_lowStaminaGaugeColor = Vector3(1.0f, 0.1f, 0.0f);   // 低HP時の色（赤）

	// UIパーツ
	SpriteRender m_RodHPGaugeInside;
	SpriteRender m_RodHPGaugeOutside;
	SpriteRender m_RodHPBar;
	SpriteRender m_stamina;

	SpriteRender m_reelChanceUI;
	SpriteRender m_rotateLStickUI;

	SpriteRender m_playerIcon;
	SpriteRender m_playerIconFine;
	SpriteRender m_playerIconTired;

	// 外部参照
	PlayFishing* m_playFishing = nullptr;
	TensionGauge* m_tensionGauge = nullptr;
	PositionSelection* m_positionSelection = nullptr;
	FightFishState* m_fightFishState = nullptr;
	BuffManager* m_buffManager = nullptr;
};
