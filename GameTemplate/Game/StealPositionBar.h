#pragma once
#include"PositionSelection.h"
class PositionSelection;
class Enemy;
class BuffManager;
class Player; // 前方宣言

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
	void UpdateStealGauge();

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

	/// <summary>
/// スティールロックの有効／無効を設定する。
/// true を渡すと現在の釣り対象の魚が固定される。
/// 	falseにしたい場合は第二引数を入れない。
/// </summary>
/// <param name="isActive">スティールロックを有効にするかどうか。</param>
	void SetIsStealLockActive(bool isActive, Area area= Area::A);

	/// <summary>
	/// スティールロックが現在有効かどうかを取得する。
	/// 有効な間は、釣り対象の魚が変化しない。
	/// </summary>
	/// <returns>スティールロックが有効なら true、無効なら false。</returns>
	bool GetIsStealLockActive(Area area);

	/// <summary>
/// いずれかのエリアでスティールロックが有効かどうかを判定する。
/// 少なくとも1つのエリアでロックが有効であれば true を返す。
/// </summary>
/// <returns>
/// bool - true: どれかのエリアでロックが有効、false: 全エリアでロック無効
/// </returns>
	bool IsAnyStealLockActive();

	void SetStockCounUI();

	SpriteRender m_stealPositionBarInsideUI;
	SpriteRender m_stealPositionBarOutsideUI;
	SpriteRender m_stealPositionGaugeUI;
	SpriteRender m_takeOver;
	SpriteRender m_takeOver_gray;
	SpriteRender m_clossUI;
	FontRender m_stockCountUI;
	SoundSource* m_sound=nullptr;
	
	float m_stealPoint = 0.0f;
	float m_bar_Length = 0.0f;
	int m_stockCount=0;//たまっているバーの本数。
	float m_barRate=0.0f;//バーの割合。
	bool m_isCharged=false;//バーがチャージされているか？。
	const float m_gaugeDeltaPerFrame = 0.02f;/// 1フレームあたりにゲージへ加算される基本の増加量。
	/// <summary>
/// スティールバーを使用して敵の釣りエリアを奪ったときに、
/// 対象の魚が変わらないように一時的にロックするフラグ。
/// プレイヤーが魚を釣り上げるか、釣りに失敗すると解除される。
/// </summary>
	std::map<int, bool> m_isStealLockActive;

	/// <summary>
	/// m_isStealLockActiveを初期化。
	/// </summary>
	void InitisStealLockActive();

	/// スティールゲージがこの値を超えると、ストックが1つ増加するしきい値。
	/// ゲージはこの値を上限として蓄積され、超過分は次の蓄積に持ち越される。
	const float m_stealGaugeThreshold = 100;
	const float m_max_barLength = 0.95f;//バーの最大の長さ。

	PositionSelection* m_positionSelection=nullptr;
	Enemy* m_enemy=nullptr;
	BuffManager* m_buffManager=nullptr;
	Player* m_player = nullptr; // 追加
};

