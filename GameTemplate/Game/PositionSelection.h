#pragma once

#include "sound/SoundSource.h"
#include <string>
#include <memory>

/// <summary>
/// エリア識別用の列挙体。
/// </summary>
enum class Area {
	A,
	B,
	C,
	D,
	E,
	F,
	INITIALSTATE,           ///< 初期状態
	ENEMY_SAME_POSITION,    ///< エネミーと同じ場所。
	NoneArea
};

// 前方宣言
class Player;
class GameCamera;
class BackGround;
class SoundSource;
class FishManager;
class PlayFishing;
class TimeLimitUI;
class Enemy;
class StealPositionBar;
class FishSlot;
class GameStartCountdown;
class InGameState;

/// <summary>
/// 位置選択シーンを管理するクラス。
/// </summary>
class PositionSelection : public IGameObject {
public:
	PositionSelection();
	~PositionSelection();

	// 基本処理関数
	void Init();                       ///< 軽い初期化処理
	bool Start();                     ///< オブジェクト依存の初期化処理
	void Update();                    ///< 毎フレームの更新処理
	void Render(RenderContext& rc);   ///< 描画処理

	// 機能関数
	void FindGameObjects();
	void SetFishDisplayPosition();    ///< 魚のUIの場所を設定
	void SetisDisplayingTrue();
	void SetisDisplayingFalse();
	bool GetisDisplaying();
	void ChangeSceneToPlayFishing();  ///< プレイシーンへの切替
	void SetDeactivate();             ///< 関連オブジェクトを非アクティブにする
	void SetActivate();               ///< 関連オブジェクトをアクティブにする
	float GetTime();
	void NotifyCurrentArea();         ///< プレイシーンへエリア通知
	void DecideEnemyTargetAreaIfNotFishing();

	Area FindFishHighScore();         ///< 高スコア魚の検出
	Area FindFishLowScore();

	void UpdatePlayerArea();          ///< プレイヤーの現在エリア更新
	void UpdateSlotFrameVisibility(Area positon);
	void SetCountdownFinished(bool countdownFinished);
	Area GetCurrentArea();



private:
	// UI位置関連
	float setFish = 0.0f;
	Vector3 m_fishDisplayPosition[6];
	float m_fishDisplayPositionXcriteria = -350;
	float m_fishDisplayPositionXinterval = 350.0f;

	// 状態・時間管理
	bool m_is_displaying = false;
	bool m_shouldPartiallyDeactivate = false;
	float m_timelimit = 5;
	int m_int_time = static_cast<int>(m_timelimit);
	float m_float_time = m_timelimit;
	bool m_is_time_up = false;
	bool m_isCountdownFinished = false;

	// エリア管理
	Area m_currentFramePlayerPositionState;
	Area m_currentFrameEnemyPositionState;
	Area m_previousFramePlayerPositionState = Area::INITIALSTATE;
	Area m_previousFrameEnemyPositionState = Area::INITIALSTATE;
	Area m_positionStateArray[6] = {
		Area::A, Area::B, Area::C, Area::D, Area::E, Area::F
	};
	Area m_playercurrentArea;
	Area m_enemyArea = Area::INITIALSTATE;

	// その他
	std::string fishHighScorePosition;
	std::string select_by_with_position;
	char* objectName[6] = {};

	// オブジェクト参照
	Player* m_player = nullptr;
	GameCamera* m_gameCamera = nullptr;
	BackGround* m_backGround = nullptr;
	FontRender m_fontRender;
	PlayFishing* m_playFishing = nullptr;
	SpriteRender* m_fishUI[6] = {};
	StealPositionBar* m_stealPositionBar = nullptr;
	Enemy* m_enemy = nullptr;
	FishSlot* m_fishSlot = nullptr;
	GameStartCountdown* m_gameStartCountdown = nullptr;
	InGameState* m_inGameState = nullptr;

	// 区切り境界（位置決定用）
	const float FRONT_BACK_Z_BORDER = -388.0f;
	const float COLUMN_LEFT_BORDER = -279.3f;
	const float COLUMN_RIGHT_BORDER = 348.0f;
};
