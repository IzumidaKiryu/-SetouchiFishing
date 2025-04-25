#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "PositionSelection.h"


Player::Player()
{
	SetAnimationClipsLoad("Assets/animData/Player/Idle.tka",
		"Assets/animData/Player/Walking.tka"
	);

	SetModel("Assets/modelData/Player/Player.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);

}

Player::~Player()
{

}


void Player::SetMoveSpeed()
{
	Vector3 forward = Vector3{ 0.0f,0.0f,1.0f };
	Vector3 right = Vector3{ 1.0f,0.0f,0.0f };

	//左スティックの入力量を取得。
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//左スティックの入力量と120.0fを乗算。
	right *= stickL.x * 250.0f;
	forward *= stickL.y * 250.0f;

	//移動速度にスティックの入力量を加算する。
	moveSpeed += right + forward;
	m_position;
}


//描画処理。
void Player::Render(RenderContext& rc)
{
	//ユニティちゃんを描画する。
	modelRender.Draw(rc);
}
