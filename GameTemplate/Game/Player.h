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

	void SetRodPosition(const Vector3& pos);
    void PlayYokodoriAnimation();

private:
	void Render(RenderContext& rc);
	BackGround* m_backGround=nullptr;
	Vector3 m_rodPosition = Vector3{-110.0f, 20.0f, -180.0f};
	//Vector3 m_rodPosition = Vector3{ 0.0f, 0.0f, 0.0f };
	
	
};
