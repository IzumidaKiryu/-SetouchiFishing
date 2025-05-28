#pragma once
#include"Character.h";
//プレイヤークラス。
class Player : public Character
{
public:
	Player();
	~Player();
	//更新処理。
	/*void Update();*/
	//ムーブスピードを設定。
	void SetMoveSpeed() override;
	void SetMoveDeActive();
	void SetMoveActive();
	bool m_is_moveActive=true;

	void Render(RenderContext& rc);
};
