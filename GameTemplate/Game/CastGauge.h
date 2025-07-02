#pragma once

class FishingGauge;
class PositionSelection;
class PlayFishing;
class GameCamera;
class RodFloatMove;
class Player;
class SceneFightFish;
class PlayCastGaugeState;

/// <summary>
/// キャストゲージUIを管理するクラス。
/// 矢印の上下移動とキャスト入力の判定を行う。
/// </summary>
class CastGauge : public IGameObject
{
public:
	CastGauge();
	~CastGauge();

	bool Init();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// 矢印のスピードを設定（外部から指定）
	/// </summary>
	void SetArrowSpead(float spead);

	/// <summary>
	/// キャスト入力が完了しているかどうかを取得。
	/// </summary>
	bool GetIsCastInputComplete() const;

private:
	// UI制御系

	/// <summary>
	/// 矢印の位置を更新
	/// </summary>
	void UpdateArrowPosition();

	/// <summary>
	/// 矢印の上下管理
	/// </summary>
	void UpAndDownManagement();

	/// <summary>
	/// 矢印の上移動処理
	/// </summary>
	void UpwardOperation();

	/// <summary>
	/// 矢印の下移動処理
	/// </summary>
	void DownwardOperation();

	/// <summary>
	/// キャスト入力処理
	/// </summary>
	void HandleCastInput();

	// ゲージ動作設定
	float m_arrowPosition = -237.0f;        // 矢印の初期位置
	bool upState = true;                    // 上昇中フラグ
	float m_gaugeUpperLimit = 237.0f;       // 上限
	float m_gaugeLowerLimit = -237.0f;      // 下限
	float m_gauge_length = 474.0f;          // ゲージ全長（= 上限 + |下限|）
	float m_gaugeSpead = 0.0f;              // 矢印の移動速度

	float m_castStrength = 0.0f;            // キャスト強度（0.0 ~ 1.0）
	bool m_isCastInputComplete = false;     // キャスト入力完了フラグ

	// UI描画用
	SpriteRender m_castGaugeOutside;
	SpriteRender m_castGaugeInside;
	SpriteRender m_Arrow;

	// 参照クラス
	PlayFishing* m_playFishing = nullptr;
};