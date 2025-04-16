#include "stdafx.h"
#include "Enemy.h"
#include "PositionSelection.h"

Enemy::Enemy()
{
	SetAnimationClipsLoad("Assets/animData/idle.tka",
		"Assets/animData/walk.tka"
	);
	//���j�e�B�����̃��f����ǂݍ��ށB
	SetModel("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);
}

Enemy::~Enemy()
{

}

void Enemy::SetMoveSpeed()
{
	//Vector3 forward = Vector3{ 0.0f,0.0f,1.0f };
	//Vector3 right = Vector3{ 1.0f,0.0f,0.0f };

	////���X�e�B�b�N�̓��͗ʂ��擾�B
	//Vector3 stickL;
	////stickL.x = g_pad[0]->GetLStickXF();
	////stickL.y = g_pad[0]->GetLStickYF();

	////���X�e�B�b�N�̓��͗ʂ�120.0f����Z�B
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

//�`�揈���B
void Enemy::Render(RenderContext& rc)
{
	//���j�e�B������`�悷��B
	modelRender.Draw(rc);
}

void Enemy::SetEnPosition(EnPosition positionState)
{
	m_positionState = positionState;
}
