#pragma once
class PositionSelection;
class Enemy;
class StealPositionBar :public IGameObject
{
public:
	StealPositionBar();
	void DisplayUI(RenderContext& rc);
	bool Init();
	bool Start();
	void Update();
	void SetBarLength();
	/// <summary>
	/// ポイントを更新。
	/// </summary>
	/// <param name="addPoint"></param>
	void UpdateStealGauge(float addPoint);

	/// <summary>
	/// ゲージを1つ消費して、敵のエリアを奪う処理を実行する。
	/// </summary>
	void UseStealGauge();

	/// <summary>
	/// たまった本数をかえす。
	/// </summary>
	/// <returns>たまっている本数</returns>
	int GetStockCount();

	/// <summary>
	/// 現在のゲージが使用可能な状態かを判定する。
	/// ゲージストックが1以上ある場合に true を返す。
	/// </summary>
	bool CanUseGauge();

	SpriteRender m_stealPositionBarInsideUI;
	SpriteRender m_stealPositionBarOutsideUI;
	SpriteRender m_stealPositionGaugeUI;

	float m_stealPoint=0.0f;
	float m_bar_Length=0.0f;
	int m_stockCount;//たまっているバーの本数。
	float m_barRate;//バーの割合。
	bool m_isCharged;//バーがチャージされているか？
	const float m_gaugeDeltaPerFrame = 1;/// 1フレームあたりにゲージへ加算される基本の増加量。
	/// スティールゲージがこの値を超えると、ストックが1つ増加するしきい値。
/// ゲージはこの値を上限として蓄積され、超過分は次の蓄積に持ち越される。
	const float m_stealGaugeThreshold=100;
	const float m_max_barLength=0.95;//バーの最大の長さ。


	PositionSelection* m_positionSelection;
	Enemy* m_enemy;
};

