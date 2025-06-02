#pragma once
#include "sound/SoundSource.h"
#include <string>
#include< memory >

enum class Area {
	A,
	B,
	C,
	D,
	E,
	F,
	INITIALSTATE,//初期状態
	ENEMY_SAME_POSITION,//エネミーと同じ場所。
};

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

class PositionSelection : public IGameObject
{
public:

	
	PositionSelection();
	~PositionSelection();
	void Update();
	bool Start();
	void Init();
	void FindGameObjects();
	bool ShouldChangeState(); // 状態を変更すべきかどうかを決定する純粋仮想関数
	void OnUpdate();//毎フレームの処理はここに書く。




	void Render(RenderContext& rc);
	//void SetStealPositionBarUI();
	void SetFishUI();//魚のUIをセット。
	void SetFishDisplayPosition();//ディスプレイUIの場所を設定。
	void SetisDisplayingTrue();
	void SetisDisplayingFalse();
	void ChangeSceneToPlayFishing();
	bool GetisDisplaying();
	void SetDeactivate();//非アクティブにする。
	void SetActivate();
	void Timer();
	float GetTime();
	void FishChange();//魚を変える。
	void NotifyCurrentArea();
	void SetTotalValue(float score);
	void FindFishHighScore();//スコアが高い魚を探す。
	void UpdatePlayerArea();
	void UpdateSlotFrameVisibility(Area positon);
	void SetCameraPosition();
	void SetFishTimeUntilEscapeUISize();
	SpriteRender& GetFishUI(int num);
	float GerFishTimeRatio(int index);
	void SetCountdownFinished(bool countdownFinished);



	float setFish = 0.0f;
	Vector3 m_fishDisplayPosition[6];//ディスプレイUIのポジション
	float m_fishDisplayPositionXcriteria = -350;//魚を表示するディスプレイの場所の基準（X軸）
	float m_fishDisplayPositionXinterval = 350.0f;
	bool m_is_displaying;//表示するかどうか。
	bool m_shouldPartiallyDeactivate = false;//部分的に非アクティブにするべきか。
	//double m_double_time=0.0f;//時間(double型)
	float m_timelimit = 5;//時間制限
	int m_int_time = m_timelimit;//時間(Int型)
	float m_float_time= m_timelimit;
	float m_totalScore = 0.0f;//スコアの合計。
	bool m_is_time_up;//タイムアップしているかどうか。

	bool m_isCountdownFinished = false; //カウントダウンが終わったかどうか。


	//int m_isSetFishDisplayOutside_to_Green=0;//フレームのUIを緑色にするか。
	Area m_currentFramePlayerPositionState;//今のフレームのポジション
	Area m_currentFrameEnemyPositionState ;//今のフレームのエネミーのポジション。
	Area m_previousFramePlayerPositionState = Area::INITIALSTATE;
	Area m_previousFrameEnemyPositionState = Area::INITIALSTATE;//前のフレームのエネミーのポジション。
	Area m_positionStateArray[6]{
	Area::A,
	Area::B,
	Area::C,
	Area::D,
	Area::E,
	Area::F,
	};
	int a = 0;
	std::string fishHighScorePosition;//出ている魚の中で一番スコアが高い魚がいるポジション。
	std::string select_by_with_position;
	char* objectName[6];
	Area m_currentArea;
	Area m_enemyArea = Area::INITIALSTATE;//初期状態;
	Player* m_player;			//プレイヤー。
	GameCamera* m_gameCamera;			//ゲームカメラ。
	BackGround* m_backGround;
	//SoundSource* gameBGM;		//ゲーム中のBGM。
	FontRender m_fontRender;
	//FishManager* m_fishManager[6];
	PlayFishing* m_playFishing;
	SpriteRender* m_fishUI[6];
	//ModelRender m_rodFloatModel;
	StealPositionBar* m_stealPositionBar;
	Enemy* m_enemy;
	FishSlot* m_fishSlot; // 魚のスロットUIを管理するクラス。
	GameStartCountdown* m_gameStartCountdown; // ゲーム開始カウントダウンを管理するクラス。
	InGameState* m_inGameState;

	//エリアを区切るための定数
	const float FRONT_BACK_Z_BORDER = -388.0f;
	const float COLUMN_LEFT_BORDER = -279.3f;
	const float COLUMN_RIGHT_BORDER = 348.0f;
};
