#pragma once
#include"Character.h"

enum EnPosition {
	enPosA,
	enPosB,
	enPosC,
	enPosD,
	enPosE,
	enPosF,
	enPosition_Num,//この型の個数
};
class BackGround;
class PositionSelection;
class Enemy :public Character
{
public:
	Enemy();
	~Enemy();
	bool Init();
	bool Start() override;
	void SetInitPos();

	void FindGameObjects();
	//ムーブスピードを設定。
	void SetMoveSpeed() override;
	void Render(RenderContext& rc);
	void SetEnPosition(EnPosition positionState);
	void SetCountdownFinished(bool countdownFinished);
	
	EnPosition m_positionState;
	//Vector3 position = {200.0f,100.0f,1.0f};

	Vector3 enemyFishingPosition[enPosition_Num]//敵の魚を釣る場所。
	{
	 {-502.2f,1.65f,-317.0f},
	 {31.5f,-43.5f,-276.3f},
	 {500.0f,-43.4f,-300.0f},
	 {-430.0f,-43.47f,-510.26f},
	 {41.01f,-43.47f,-544.6f},
	 {625.8f,-43.47f,-570.8f},
	};

	bool m_isCountdownFinished = false; //カウントダウンが終わったかどうか。
	PositionSelection* m_positionSelection;
	BackGround* m_backGround;
	Alea
};

