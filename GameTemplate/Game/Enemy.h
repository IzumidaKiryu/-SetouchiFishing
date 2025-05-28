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

class PositionSelection;
class Enemy :public Character
{
public:
	Enemy();
	~Enemy();
	bool Start() override;
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
	 {-556.6f,16.0f,-89.9f},
	 {10.5f,6.5f,25.3f},
	 {606.0f,6.5f,-10.0f},
	 {-516.3,6.5f,-329.44f},
	 {-3.4f,6.5f,24.3f},
	 {539.8f,6.5f,399.9f},
	};

	bool m_isCountdownFinished = false; //カウントダウンが終わったかどうか。
	PositionSelection* m_positionSelection;
};

