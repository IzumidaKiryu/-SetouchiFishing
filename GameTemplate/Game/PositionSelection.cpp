#include "stdafx.h"
#include "PositionSelection.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "FishManager.h"
#include "PlayFishing.h"
#include "TimeLimitUI.h"
#include "Enemy.h"
#include "StealPositionBar.h"
#include "FishSlot.h"
#include "GameStartCountdown.h"
#include "InGameState.h"
#include <ctime>
#include <string>
#include <memory>

/// <summary>
/// コンストラクタ。乱数の初期化。
/// </summary>
PositionSelection::PositionSelection() {
	srand(static_cast<unsigned>(time(nullptr)));
}

/// <summary>
/// デストラクタ。生成したオブジェクトを削除。
/// </summary>
PositionSelection::~PositionSelection() {
	DeleteGO(m_stealPositionBar);
	DeleteGO(m_player);
	DeleteGO(m_playFishing);
	DeleteGO(m_fishSlot);
}

/// <summary>
/// 初期化処理。BGMやUIの設定。
/// </summary>
void PositionSelection::Init() {
	m_stealPositionBar = NewGO<StealPositionBar>(0, "stealPositionBar");
	m_stealPositionBar->Init();
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/gamebgm.wav");
	SetFishDisplayPosition();
	m_fishSlot = NewGO<FishSlot>(0, "fishSlot");
	m_fishSlot->ThiscClassInit();
	SetCountdownFinished(true);
	m_enemy->SetCountdownFinished(true);

	m_PressAtoSelect.Init("Assets/modelData/PromptUI/PressAtoSelect.DDS", 300.0f, 300.0f);
	m_PressAtoSelect.SetPivot(Vector2{ 0.0f,0.0f });
	m_PressAtoSelect.SetPosition(Vector3{ 450.0f,-500.0f,0.0f });
	m_PressAtoSelect.Update();

}

/// <summary>
/// Start。ゲームオブジェクトの取得。
/// </summary>
bool PositionSelection::Start() {

	FindGameObjects();

	return true;
}

/// <summary>
/// 毎フレーム更新処理。
/// </summary>
void PositionSelection::Update() {
	if (!m_isCountdownFinished) return;

	UpdatePlayerArea();
	if (!m_shouldPartiallyDeactivate && g_pad[0]->IsTrigger(enButtonA))
	{
		m_player->SetIsFishingInArea(true,m_playercurrentArea);
		ChangeSceneToPlayFishing();
		m_gameCamera->Activate();
	}
	else {
		m_gameCamera->Deactivate();
	}
}

/// <summary>
/// UIの描画処理。
/// </summary>
void PositionSelection::Render(RenderContext& rc) {
	if (!m_isCountdownFinished) return;

	m_stealPositionBar->DisplayUI(rc);
	if (!m_shouldPartiallyDeactivate) {
		m_fishSlot->ShowUI(rc);
		m_PressAtoSelect.Draw(rc);
	}
}

/// <summary>
/// 必要なゲームオブジェクトをFindGOで取得。
/// </summary>
void PositionSelection::FindGameObjects() {
	m_player = FindGO<Player>("player");
	m_enemy = FindGO<Enemy>("enemy");
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_backGround = FindGO<BackGround>("backGround");
	m_inGameState = FindGO<InGameState>("inGameState");
}

/// <summary>
/// 魚のUIの表示位置を設定。
/// </summary>
void PositionSelection::SetFishDisplayPosition() {
	for (int i = 0; i < 6; i++) {
		if (i < 3) {
			m_fishDisplayPosition[i] = { m_fishDisplayPositionXcriteria + m_fishDisplayPositionXinterval * i, 230.0f, 0.0f };
		}
		else {
			m_fishDisplayPosition[i] = { m_fishDisplayPositionXcriteria + m_fishDisplayPositionXinterval * (i - 3), -300.0f, 0.0f };
		}
	}
}

void PositionSelection::SetisDisplayingTrue() { m_is_displaying = true; }
void PositionSelection::SetisDisplayingFalse() { m_is_displaying = false; }
bool PositionSelection::GetisDisplaying() { return m_is_displaying; }

/// <summary>
/// 関連オブジェクトを非アクティブにする。
/// </summary>
void PositionSelection::SetDeactivate() {
	m_player->Deactivate();
	m_enemy->Deactivate();
	m_gameCamera->Deactivate();
	m_shouldPartiallyDeactivate = true;
}

/// <summary>
/// 関連オブジェクトをアクティブにする。
/// </summary>
void PositionSelection::SetActivate() {
	m_player->Activate();
	m_enemy->Activate();
	m_gameCamera->Activate();
	m_shouldPartiallyDeactivate = false;
}

/// <summary>
/// 経過時間を取得。
/// </summary>
float PositionSelection::GetTime() { return m_float_time; }

/// <summary>
/// プレイフィッシングシーンへ遷移。
/// </summary>
void PositionSelection::ChangeSceneToPlayFishing() {
	if (m_playercurrentArea == Area::ENEMY_SAME_POSITION) return;

	SetisDisplayingFalse();
	m_playFishing = NewGO<PlayFishing>(0, "playFishing");
	NotifyCurrentArea();
	m_playFishing->Init();
	SetDeactivate();
}

/// <summary>
/// 現在のエリア名をプレイフィッシングに通知。
/// </summary>
void PositionSelection::NotifyCurrentArea() {
	m_playFishing->SetCurrentFishManagerObjectName(m_inGameState->GetAreaName(static_cast<int>(m_playercurrentArea)));
}
/// <summary>
/// 敵が釣っていないときだけ、敵のターゲットエリアを決める
/// </summary>
void PositionSelection::DecideEnemyTargetAreaIfNotFishing()
{


}

/// <summary>
/// スコアの高い魚のいるエリアを探索する。
/// </summary>
Area PositionSelection::FindFishHighScore() {
	Area bestArea = Area::A;
	float maxScore = -1.0f;
	for (int i = 0; i < 6; ++i) {
		float score = m_inGameState->GetFishScore(i);
		if (score > maxScore) {
			maxScore = score;
			bestArea = m_positionStateArray[i];
		}
	}
	//m_enemyArea = bestArea;
	return bestArea;
}

Area PositionSelection::FindFishLowScore()
{
	Area worstArea = Area::A;
	float minScore = FLT_MAX;  // 最大の float 値で初期化

	for (int i = 0; i < 6; ++i) {
		float score = m_inGameState->GetFishScore(i);
		if (score < minScore) {
			minScore = score;
			worstArea = m_positionStateArray[i];
		}
	}

	return worstArea;
}

/// <summary>
/// プレイヤーの位置に応じてエリアを更新。
/// 敵と同じ位置なら特殊状態に。
/// </summary>
void PositionSelection::UpdatePlayerArea() {
	const Vector3& playerPos = m_player->m_position;
	bool isFrontRow = playerPos.z >= FRONT_BACK_Z_BORDER;

	if (isFrontRow) {
		if (playerPos.x < COLUMN_LEFT_BORDER)
			m_playercurrentArea = Area::A;
		else if (playerPos.x <= COLUMN_RIGHT_BORDER)
			m_playercurrentArea = Area::B;
		else
			m_playercurrentArea = Area::C;
	}
	else {
		if (playerPos.x < COLUMN_LEFT_BORDER)
			m_playercurrentArea = Area::D;
		else if (playerPos.x <= COLUMN_RIGHT_BORDER)
			m_playercurrentArea = Area::E;
		else
			m_playercurrentArea = Area::F;
	}

	if (m_playercurrentArea == m_enemy->GetTargetFishinArea())
		m_playercurrentArea = Area::ENEMY_SAME_POSITION;

	UpdateSlotFrameVisibility(m_playercurrentArea);
}

/// <summary>
/// スロットUIの枠の色変更などを行う。
/// </summary>
void PositionSelection::UpdateSlotFrameVisibility(Area position) {
	m_fishSlot->UpdateSlotFrameVisibility(static_cast<int>(position), static_cast<int>(m_enemy->GetTargetFishinArea()));
}


/// <summary>
/// カウントダウン終了フラグを設定。
/// </summary>
void PositionSelection::SetCountdownFinished(bool countdownFinished) {
	m_isCountdownFinished = countdownFinished;
}

Area PositionSelection::GetCurrentArea()
{
	return m_playercurrentArea;
}
