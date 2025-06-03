#include "stdafx.h"
#include "Enemy.h"
#include "PositionSelection.h"
#include"BackGround.h"


Enemy::Enemy()
{
}

Enemy::~Enemy()
{

}

bool Enemy::Init()
{
	m_backGround = FindGO<BackGround>("backGround");


	SetAnimationClipsLoad("Assets/animData/Enemy/EnamyIdle.tka",
		"Assets/animData/Enemy/EnamyWalking.tka",
		"Assets/animData/Player/FishingCast.tka"
	);
	//ユニティちゃんのモデルを読み込む。
	SetModel("Assets/modelData/Enemy/Enemy.tkm", animationClips, enAnimationClip_Num, enModelUpAxisZ, true, false);

	return true;
}

bool Enemy::Start()
{

	Character::Start();
	FindGameObjects();
	return true;
}

void Enemy::FindGameObjects()
{
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_backGround = FindGO<BackGround>("backGround");

}

void Enemy::SetMoveSpeed()
{



	if (m_isCountdownFinished == true)//カウントダウンが終わったらムーブスピードを設定する。
	{
		m_positionSelection = FindGO<PositionSelection>("positionSelection");

		//ムーブスピードを設定する。
		m_positionSelection->FindFishHighScore();
		/*if (m_position.x <= enemyFishingPosition[m_positionSelection->enemy_position].x - 10.0f || m_position.y <= enemyFishingPosition[m_positionSelection->enemy_position].y) {*/

		Vector3 range_of_enemy_and_position = enemyFishingPosition[static_cast<int>(m_positionSelection->GetEnemyArea())] - m_position;//敵ポジションと選んでいるポジションの距離。
		if (range_of_enemy_and_position.Length() >= 10.0f) {
			moveSpeed += range_of_enemy_and_position/*(enemyFishingPosition[m_positionSelection->enemy_position] - m_position)*/;
			moveSpeed.Normalize();
			moveSpeed *= 700.0f;
		}
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

void Enemy::SetCountdownFinished(bool countdownFinished)
{
	m_isCountdownFinished = countdownFinished;
}
