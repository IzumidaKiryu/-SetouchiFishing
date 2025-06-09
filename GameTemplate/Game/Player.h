#pragma once
#include"Character.h";
//プレイヤークラス。
class BackGround;
class Player : public Character
{
public:
	Player();
	~Player();
	//更新処理。
	/*void Update();*/
	
	bool Init();
	bool Start()override;
	//ムーブスピードを設定。
	void SetMoveSpeed() override;
	void SetMoveDeActive();
	void SetMoveActive();
	bool m_is_moveActive=true;

private:
	void Render(RenderContext& rc);
	BackGround* m_backGround;
};
