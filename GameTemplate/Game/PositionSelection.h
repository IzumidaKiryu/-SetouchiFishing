#pragma once
#include "sound/SoundSource.h"
#include <string>

enum Position {
	POSITION_A,
	POSITION_B,
	POSITION_C,
	POSITION_D,
	POSITION_E,
	POSITION_F,
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

class PositionSelection : public IGameObject
{
public:


	PositionSelection();
	~PositionSelection();
	void Update();
	void Render(RenderContext& rc);
	void SetDisplayiUI();
	void SetStealPositionBarUI();
	void SetFishUI();//魚のUIをセット。
	void SetFishDisplayPosition();//ディスプレイUIの場所を設定。
	void SetisDisplayingTrue();
	void SetisDisplayingFalse();
	void ChangeSceneToPlayFishing();
	bool GetisDisplaying();
	void SetDeactivate();//非アクティブにする。
	void SetActivate();
	void Timer();
	int GetTime();
	void SetFishUIPosition();
	void FishChange();//魚を変える。
	void SelectPosition();
	void SetTotalValue(float score);
	void FindFishHighScore();//スコアが高い魚を探す。
	void IsWith_any_Position();
	void SetFishDisplayOutside_to_Green(Position positon);

	float setFish = 0.0f;
	Vector3 m_fishDisplayPosition[6];//ディスプレイUIのポジション
	float m_fishDisplayPositionXcriteria = -350;//魚を表示するディスプレイの場所の基準（X軸）
	float m_fishDisplayPositionXinterval = 350.0f;
	bool m_is_displaying;//表示するかどうか。
	bool m_shouldPartiallyDeactivate = false;//部分的に非アクティブにするべきか。
	//double m_double_time=0.0f;//時間(double型)
	float m_timelimit = 240;//時間制限
	int m_int_time = m_timelimit;//時間(Int型)
	float m_totalScore = 0.0f;//スコアの合計。
	bool m_is_time_up;//タイムアップしているかどうか。
	float m_stealPositionPoint = 0.0f;//敵からからポジションを奪うためのポイント。

	//int m_isSetFishDisplayOutside_to_Green=0;//フレームのUIを緑色にするか。
	Position m_currentFramePlayerPositionState;//今のフレームのポジション
	Position m_previousFramePlayerPositionState = INITIALSTATE;
	Position m_positionStateArray[6]{
	POSITION_A,
	POSITION_B,
	POSITION_C,
	POSITION_D,
	POSITION_E,
	POSITION_F,
	};
	int a = 0;
	std::string fishHighScorePosition;//出ている魚の中で一番スコアが高い魚がいるポジション。
	std::string PositionName[6] = {
		"positionA",
		"positionB",
		"positionC",
		"positionD",
		"positionE",
		"positionF"
	}
	;
	std::string select_by_with_position;
	char* objectName[6];
	Position position_with_now;
	Position enemy_position = INITIALSTATE;//初期状態;
	Player* m_player;			//プレイヤー。
	GameCamera* gameCamera;			//ゲームカメラ。
	BackGround* backGround;
	//SoundSource* gameBGM;		//ゲーム中のBGM。
	FontRender m_fontRender;
	SpriteRender m_fishDisplayInside[6];
	SpriteRender m_fishDisplayOutside[6];
	FishManager* m_fishManager[6];
	PlayFishing* m_playFishing;
	SpriteRender* m_fishUI[6];
	SpriteRender m_stealPositionBarInsideUI;
	SpriteRender m_stealPositionBarOutsideUI;
	SpriteRender m_stealPositionGaugeUI;
	TimeLimitUI* m_timeLimitUI;
	//ModelRender m_rodFloatModel;

	Stopwatch m_stopwatch;
	Enemy* m_enemy;

};

