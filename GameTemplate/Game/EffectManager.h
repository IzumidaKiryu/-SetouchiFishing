#pragma once
enum class EffectType {

};
class EffectManager:IGameObject
{
public:
	EffectManager() = default;
	~EffectManager() = default;

	/// <summary>
    /// エフェクトの初期化
    /// </summary>
	bool Init();

private:

	void Update();


	bool Start();

	/// <summary>
	/// エフェクトの更新
	/// </summary>
	void UpdateEffects();

private:
	std::map<Effect, std::shared_ptr<Effect>> m_effects; //エフェクトのマップ。キーはエフェクト名、値はエフェクトオブジェクトへのポインタ。
};

