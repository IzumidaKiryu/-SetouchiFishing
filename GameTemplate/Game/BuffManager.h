#pragma once
enum class BuffType {
	NoBuff,
	StealBoostBuff,//敵のエリアを奪うためのポイントが増える量を増やすバフ。
	PullStrengthBuff,//魚を引く力を上げるバフ。
	StaminaRegenBuff,//スタミナの回復量を上げるバフ。
	RandumBuff//三つのバフの中からランダムに適用される。
};
class BuffManager :public IGameObject
{
public:
	BuffManager();
	~BuffManager();
	void ApplyBuffEffect(const std::map<BuffType, float>& buff,BuffType bufftype);
	float GetBuffEffect(BuffType buffType)const;
	float GetTotalStealBoostBuff();
	float GetTotalPullStrengthBuff();
	float GetTotalStaminaRegenBuff();
	int GetBuffCount(BuffType buffType);
private:
	std::map<BuffType, float> m_buffEffect;
	std::map<BuffType, int> m_buffCount;
	void InitSetBuffEffect();
};

