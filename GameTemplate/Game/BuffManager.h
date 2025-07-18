#pragma once
/// <summary>
/// バフの種類
/// </summary>
enum class BuffType {
	NoBuff,               // なし
	StealBoostBuff,       // 敵エリア奪取時のポイント加算量を増やす
	PullStrengthBuff,     // 魚を引く力を上げる
	StaminaRegenBuff,     // スタミナ回復量を上げる
	RandumBuff            // ランダムでいずれかのバフを適用
};

/// <summary>
/// バフ効果を管理するクラス
/// </summary>
class BuffManager :public IGameObject
{
public:
	BuffManager();
	~BuffManager();
	/// <summary>
	/// バフ効果を適用する
	/// </summary>
	void ApplyBuffEffect(const std::map<BuffType, float>& buff, BuffType buffType);

	/// <summary>
	/// 指定バフの合計効果を取得
	/// </summary>
	float GetBuffEffect(BuffType buffType) const;

	float GetTotalStealBoostBuff();
	float GetTotalPullStrengthBuff();
	float GetTotalStaminaRegenBuff();

	/// <summary>
    /// 指定バフの累積回数を取得
    /// </summary>
	int GetBuffCount(BuffType buffType);

private:
	void InitSetBuffEffect();

private:
	std::map<BuffType, float> m_buffEffect;   // バフごとの効果値
	std::map<BuffType, int> m_buffCount;      // バフごとの取得回数
};

