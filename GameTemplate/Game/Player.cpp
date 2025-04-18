#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "PositionSelection.h"


Player::Player()
{
	SetAnimationClipsLoad("Assets/animData/idle.tka",
		"Assets/animData/walk.tka"
	);

	SetModel("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);

}

Player::~Player()
{

}


void Player::SetMoveSpeed()
{
	Vector3 forward = Vector3{ 0.0f,0.0f,1.0f };
	Vector3 right = Vector3{ 1.0f,0.0f,0.0f };

	//���X�e�B�b�N�̓��͗ʂ��擾�B
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//���X�e�B�b�N�̓��͗ʂ�120.0f����Z�B
	right *= stickL.x * 250.0f;
	forward *= stickL.y * 250.0f;

	//�ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z����B
	moveSpeed += right + forward;
	m_position;
}


//�`�揈���B
void Player::Render(RenderContext& rc)
{
	//���j�e�B������`�悷��B
	modelRender.Draw(rc);
}
