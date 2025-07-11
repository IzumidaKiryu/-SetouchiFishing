#pragma once
#include "Fish.h"
class PlayFishing;
class PositionSelection;
class InGameState;
class Enemy;
class Player;
class StealPositionBar;
class Fish;
class ScoreDisplay : public IGameObject
{
public:

	ScoreDisplay();
	~ScoreDisplay();

	void Update();
	bool Start();
	bool Init();
	void SetScore();
	void SetOnesPlace();
	void SetTensPlace();
	void SetHundredsPlace();
	void SetOnesPlaceUI();
	void SetTensPlaceUI();
	void SetHundredsPlaceUI();
	void ScoreUI();
	void Render(RenderContext& rc);
	//追加
	void WhichFishUI(FishType type);
	SpriteRender m_getFishTypeUI;
	SpriteRender m_UIBackGround;
	FontRender m_scoreFontRender;
	//ここまで
	int m_onesPlace=0;
	int m_tensPlace=0;
	int m_hundredsPlace=0;
	int m_prevTime=0;
	int m_score=0;

	Vector3 m_hundredsPlaceUIPos = { 490.0f - 270.0f + 200.0f,100.0f,0.0f };
	Vector3 m_tensPlaceUIPos = { 410.0f - 270.0f + 200.0f,100.0f,0.0f };
	Vector3 m_onesPlaceUIPos = { 330.0f - 270.0f + 200.00f,100.0f,0.0f };

	PlayFishing* m_playFishing=nullptr;
	SpriteRender m_onesPlaceUI;
	SpriteRender m_tensPlaceUI;
	SpriteRender m_hundredsPlaceUI;
	SpriteRender m_scoreDisplay;
	PositionSelection* m_positionSelection = nullptr;
	InGameState* m_inGameState=nullptr;
	Enemy* m_enemy = nullptr;
	Player* m_player = nullptr;
	StealPositionBar* m_stealPositionBar = nullptr;
};

