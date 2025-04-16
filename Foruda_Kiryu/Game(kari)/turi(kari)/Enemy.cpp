#include "stdafx.h"
#include "Enemy.h"
#include "PositionSelection.h"

Enemy::Enemy()
{
	SetAnimationClipsLoad("Assets/animData/idle.tka",
		"Assets/animData/walk.tka"
	);
	//ユニティちゃんのモデルを読み込む。
	SetModel("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);
}

Enemy::~Enemy()
{

}

void Enemy::SetMoveSpeed()
{
	//Vector3 forward = Vector3{ 0.0f,0.0f,1.0f };
	//Vector3 right = Vector3{ 1.0f,0.0f,0.0f };

	////左スティックの入力量を取得。
	//Vector3 stickL;
	////stickL.x = g_pad[0]->GetLStickXF();
	////stickL.y = g_pad[0]->GetLStickYF();

	////左スティックの入力量と120.0fを乗算。
	//right *= stickL.x * 120.0f;
	//forward *= stickL.y * 120.0f;
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_positionSelection->FindFishHighScore();
	if (position.x <= enemyFishingPosition[m_positionSelection->enemy_position].x-10.0f|| position.y <= enemyFishingPosition[m_positionSelection->enemy_position].y) {
		moveSpeed += (enemyFishingPosition[m_positionSelection->enemy_position] - position);
		moveSpeed.Normalize();
		moveSpeed*=700.0f;
	}
}

//描画処理。
void Enemy::Render(RenderContext& rc)
{
	//ユニティちゃんを描画する。
	modelRender.Draw(rc);
}

void Enemy::SetEnPosition(EnPosition positionState)
{
	m_positionState = positionState;
}
