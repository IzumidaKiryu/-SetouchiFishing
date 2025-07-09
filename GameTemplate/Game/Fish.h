#pragma once
#include "BuffManager.h"

/// <summary>
/// 魚の種類
/// </summary>
enum class FishType {
	TAI,
	BURI,
	TATIUO,
	HIRAME,
	JAKOTENN,
	SINJU,
};

/// <summary>
/// 魚のレア度
/// </summary>
enum class FishRarity {
	Common,      // 通常
	Rare,        // レア
	SuperRare    // スーパーレア
};

/// <summary>
/// 魚のパラメータ構造体
/// </summary>
struct FishData {
	FishType fishType;
	float timeUntilEscape = 0.5f; //魚が逃げるまでの時間
	float arrowSpeed = 5.0f; //矢印のスピード
	float score = -10.0f; //スコア
	float individualFactor = 0.0f; //個体補正係数
	float initPos = 1.0f; //初期ポジション
	int upwardBias = 50; //上方向へのバイアス（0～100）
	int downwardBias = 50; //下方向へのバイアス（0～100）
	float fishDetectionRadius = 0.0f; //ウキの検知範囲（0～1）
	float escapeForce = 1.0f; //逃げる力
	std::map<BuffType, float> buffEffect; //バフ効果
	BuffType buffType; //バフの種類
	FishRarity rarity; //レア度
};

class PositionSelection;
class InGameState;

/// <summary>
/// 魚の基本クラス。各魚はこのクラスを継承して独自の動作を持つ。
/// </summary>
class Fish : public IGameObject {
public:
	Fish();
	~Fish();

	void Update();

	virtual bool Init() final;

	/// <summary>
	/// 派生クラスで実装される初期化処理
	/// </summary>
	virtual bool OnInit() = 0;

	bool Start();

	/// <summary>
	/// 魚が逃げるまでの時間を確認し、条件を満たせば変更フラグを立てる
	/// </summary>
	void UpdateEscapeTimer();

	/// <summary>
	/// 魚を変更する必要があるかどうかを取得
	/// </summary>
	bool GetShouldFishChange();

	/// <summary>
	/// 魚が逃げるまでの時間の割合（経過比率）を取得
	/// </summary>
	float GetTimeRatio();

	/// <summary>
	/// 魚のデータ構造体を参照返却
	/// </summary>
	FishData& GetFishData();

	/// <summary>
	/// UIスプライトを参照返却
	/// </summary>
	SpriteRender& GetUI();

protected:
	/// <summary>
	/// 個体値（0.804～1.2）をランダムに設定
	/// </summary>
	void SetRandomIndividualFactor();

	/// <summary>
	/// 魚の種類を設定
	/// </summary>
	void SetFishType(FishType fishtype);

	/// <summary>
	/// 個体値を反映したスコアを設定
	/// </summary>
	void SetScore();

	/// <summary>
	/// 関連するゲームオブジェクトを取得
	/// </summary>
	void FindGameObjects();

	/// <summary>
	/// 魚が逃げるまでの時間を設定
	/// </summary>
	void SetTimeUntilEscape(float timeUntilEscape);

	/// <summary>
	/// 矢印の移動速度を設定
	/// </summary>
	void SetArrowSpeed(float spead);

	/// <summary>
	/// 基本スコアを設定（個体値による倍率前）
	/// </summary>
	void SetBaseScore(float baseScore);

	/// <summary>
	/// 初期位置を設定
	/// </summary>
	void SetInitPos(float initpos);

	/// <summary>
	/// 上方向バイアスを設定（0～100に制限）
	/// </summary>
	void SetUpWardBias(float bias);

	/// <summary>
	/// 下方向バイアスを設定（0～100に制限）
	/// </summary>
	void SetDownwardBias(float bias);

	/// <summary>
	/// ウキを検知する半径（0～0.5）を設定
	/// </summary>
	void SetFishDetectionRadius(float fishDetectionRadius);

	/// <summary>
	/// 逃げる力を設定
	/// </summary>
	void SetEscapeForce(float escapeForce);

	/// <summary>
	/// UI用のスプライトを初期化
	/// </summary>
	virtual void SetUI(std::string filePath, Vector3 scale = Vector3::One) final;

	/// <summary>
	/// バフ効果とタイプを設定（個体補正含む）
	/// </summary>
	void SetBuff(BuffType bufftype, float buffValue);

	protected:
	bool m_shouldFishChange = false; ///< 魚を変更する必要があるかどうか
	bool m_isSelected = false; ///< 選択中の魚かどうか
	float m_baseScore = 0.0f; ///< 基本スコア
	float m_initialTime = 0.0f; ///< 初期化時の時刻
	float m_nowTime = 0.0f; ///< 現在時刻
	float m_timeRatio = 0.0f; ///< 経過比率（逃げるまでの時間）

	SpriteRender m_ui;
	PositionSelection* m_positionSelection = nullptr;
	InGameState* m_inGameState = nullptr;
	FishData m_fishData;
};
