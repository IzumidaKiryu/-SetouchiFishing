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
	//ムーブスピードを設定。
	void SetMoveSpeed() override;
	void Render(RenderContext& rc);
	void SetEnPosition(EnPosition positionState);
	EnPosition m_positionState;
	//Vector3 position = {200.0f,100.0f,1.0f};

	Vector3 enemyFishingPosition[enPosition_Num]//敵の魚を釣る場所。
	{
	 {-384.6f,27.8f,208.9f},
	 {19.5f,27.8f,252.3f},
	 {384.0f,27.8f,252.0f},
	 {373.3,27.8f,26.44f},
	 {-20.5f,27.8f,-13.3f},
	 {332.8f,27.8f,-8.9f},
	};

	PositionSelection* m_positionSelection;
};

