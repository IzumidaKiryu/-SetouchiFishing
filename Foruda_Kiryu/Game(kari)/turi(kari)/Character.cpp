#include "stdafx.h"
#include "Character.h"
Character::Character()
{
	////�A�j���[�V�����N���b�v�����[�h����B
	//animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	//animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	//animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	//animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	
	////���j�e�B�����̃��f����ǂݍ��ށB
	//modelRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);

	//�L�����R��������������B
	characterController.Init(25.0f, 75.0f, position);
}

Character::~Character()
{

}

//�X�V�����B
void Character::Update()
{
	//�ړ������B
	Move();

	//��]�����B
	Rotation();

	//�X�e�[�g�Ǘ��B
	ManageState();

	//�A�j���[�V�����̍Đ��B
	PlayAnimation();

	//�G�`������̍X�V�����B
	modelRender.Update();
}

void Character::SetModel(const char* filePath, AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis)
{
	//���j�e�B�����̃��f����ǂݍ��ށB
	modelRender.Init(filePath, animationClips, numAnimationClips, enModelUpAxis);
}

void Character::SetAnimationClipsLoad(const char* animationClip_Idle, const char* animationClip_Walk)
{
	animationClips[enAnimationClip_Idle].Load(animationClip_Idle);
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);

	animationClips[enAnimationClip_Walk].Load(animationClip_Walk);
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
}

void Character::SetMoveSpeed()
{
	//�h���N���X�Œ�`����B
}

void Character::Move()
{
	//xz�̈ړ����x��0.0f�ɂ���B
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	
	SetMoveSpeed();
	



	//�n�ʂɕt���Ă�����B
	if (characterController.IsOnGround())
	{
		//�d�͂𖳂����B
		moveSpeed.y = 0.0f;
	}
	//�n�ʂɕt���Ă��Ȃ�������B
	else
	{
		//�d�͂𔭐�������B
		moveSpeed.y -= 2.5f;
	}

	//�L�����N�^�[�R���g���[���[���g���č��W���ړ�������B
	position = characterController.Execute(moveSpeed, 1.0f / 60.0f);

	//�G�`������ɍ��W��������B
	modelRender.SetPosition(position);
}

void Character::Rotation()
{
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		//�L�����N�^�[�̕�����ς���B
		rotation.SetRotationYFromDirectionXZ(moveSpeed);
		//�G�`������ɉ�]��������B
		modelRender.SetRotation(rotation);
	}
}

//�X�e�[�g�Ǘ��B
void Character::ManageState()
{
	//�n�ʂɕt���Ă��Ȃ�������B
	if (characterController.IsOnGround() == false)
	{
		//������ManageState�̏������I��点��B
		return;
	}

	//�n�ʂɕt���Ă�����B
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		//�X�e�[�g������ɂ���B
		playerState = enAnimationClip_Walk;
	}
	//x��z�̈ړ����x������������(�X�e�B�b�N�̓��͂�����������)�B
	else
	{
		//�X�e�[�g��0(�ҋ@)�ɂ���B
		playerState = enAnimationClip_Idle;
	}
}




//�A�j���[�V�����̍Đ��B
void Character::PlayAnimation()
{
	//switch���B
	switch (playerState) {
		//�v���C���[�X�e�[�g��0(�ҋ@)��������B
	case enAnimationClip_Idle:
		//�W�����v�A�j���[�V�������Đ�����B
		modelRender.PlayAnimation(enAnimationClip_Idle);
		break;

	case enAnimationClip_Walk:
		//�v���C���[�X�e�[�g��2(����)��������B
		modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	}
}
	////�`�揈���B
	//void Character::Render(RenderContext & rc)
	//{
	//	//���j�e�B������`�悷��B
	//	modelRender.Draw(rc);
	//}

