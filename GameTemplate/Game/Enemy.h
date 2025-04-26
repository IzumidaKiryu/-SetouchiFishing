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
	 {-448.0f,81.34f,101.0f},
	 {0.0f,81.34f,86.0f},
	 {452.0f,81.34f,86.0f},
	 {-448.0f,81.34f,-168.0f},
	 {0.0f,81.34f,-168.0f},
	 {452.0f,81.34f,-168.0f},
	};

	PositionSelection* m_positionSelection;
};

