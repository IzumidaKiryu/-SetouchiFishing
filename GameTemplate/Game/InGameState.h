#pragma once
#include "GameStateBase.h"
class GameCamera;
class BackGround;
class PositionSelection;
class Enemy;
class Player;
class GameStartCountdown;
class InGameState :public GameStateBase
{
public:
	InGameState();
	bool Start()override;
	void OnUpdate();
	bool ShouldChangeState(); // 状態を変更すべきかどうかを決定する純粋仮想関数
	void OnEnter();
	void OnExit();
	void Render(RenderContext& rc)override;

	GameStartCountdown* m_gameStartCountdown;
	Player* m_player;
	GameCamera* m_gameCamera;
	PositionSelection* m_positionSelection;//場所を選ぶ画面のクラス。
	BackGround* m_backGround;
	Enemy* m_enemy;


};

