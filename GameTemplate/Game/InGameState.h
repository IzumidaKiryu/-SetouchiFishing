#pragma once
#include "GameStateBase.h"
#include "sound/SoundSource.h"
#include"Fish.h"
class GameCamera;
class BackGround;
class PositionSelection;
class Enemy;
class Player;
class GameStartCountdown;
class TimeLimitUI;
class FishManager;
class ScoreManager;
class FishSlot;
class StealPositionBar;
class BuffManager;
class PlayFishing;
class ScoreDisplay;
class InGameState :public GameStateBase
{
public:
	InGameState();
	bool Start()override;
	bool Init();
	void OnUpdate();
	bool ShouldChangeState(); // 状態を変更すべきかどうかを決定する純粋仮想関数
	void OnEnter();
	void OnExit();
	void Render(RenderContext& rc)override;

	void Timer();
	float GetTime();

	void SetHasCountdownClassFinished(bool flag);
	void SetHasCountdownClassJustFinished(bool flag);
	void ChangeFish();
	void ChangeFish(int Areaindex);
	void CreateInitialFish();
	float GerFishTimeRatio(int index);
	void SetFishUI(int num);
	SpriteRender& GetFishUI(int index);
	float GetFishScore(int index);

	void SetScore(float score);

	void DeleteGameObjects();
	void OnCountdownFinished();
	std::string GetAreaName(int index);
	FishData GetFishData(int index);

	void NewGOScoreDisplay(FishType fishType);



private:
	
	GameStartCountdown* m_gameStartCountdown=nullptr;
	Player* m_player = nullptr;
	GameCamera* m_gameCamera = nullptr;
	PositionSelection* m_positionSelection = nullptr;//場所を選ぶ画面のクラス。
	BackGround* m_backGround = nullptr;
	Enemy* m_enemy = nullptr;
	Stopwatch m_stopwatch;
	FishManager* m_fishManager[6];
	SpriteRender* m_fishUI[6];
	ScoreManager* m_scoreManager = nullptr;
	FishSlot* m_fishSlot = nullptr;
	StealPositionBar* m_stealPositionBar = nullptr;
	BuffManager* m_buffManager = nullptr;
	PlayFishing* m_playFishing = nullptr;
	ScoreDisplay* m_scoreDisplay = nullptr;
	SoundSource* m_sound = nullptr;



	float m_timelimit = 300;//時間制限
	float m_time = m_timelimit;//時間
	float m_totalScore = 0.0f;//スコアの合計。
	TimeLimitUI* m_timeLimitUI=nullptr;
	bool m_isCountdownFinished=false;//カウントダウンが終わったか（このクラスのカウントダウン）


	bool m_hasCountdownClassFinished=false;//ゲームスタートカウントダウンクラスが終わったか。
	bool m_hasCountdownClassJustFinished=false;//ゲームスタートカウンダウンクラスが終わった瞬間か。
	std::string AreaName[6] = {
"A",
"B",
"C",
"D",
"E",
"F"
	}
	;


};

