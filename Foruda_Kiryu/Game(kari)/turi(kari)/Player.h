#pragma once
#include"Character.h";
//�v���C���[�N���X�B
class Player : public Character
{
public:
	Player();
	~Player();
	//�X�V�����B
	/*void Update();*/
	//���[�u�X�s�[�h��ݒ�B
	void SetMoveSpeed() override;
	//�ړ������B
	//void Move();
	////��]�����B
	//void Rotation();
	////�X�e�[�g�Ǘ��B
	//void ManageState();
	////�A�j���[�V�����̍Đ��B
	//void PlayAnimation();

	//�����o�ϐ��B
	//enum EnAnimationClip {		//�A�j���[�V�����B
	//	enAnimationClip_Idle,
	//	enAnimationClip_Walk,
	//	enAnimationClip_Jump,
	//	enAnimationClip_Num,
	//};
/*	AnimationClip animationClips[enAnimationClip_Num];*/		//�A�j���[�V�����N���b�v�B
	//CharacterController characterController;  //�L�����N�^�[�R���g���[���[�B
	//Vector3 moveSpeed;		//�ړ����x�B
	//Quaternion rotation;  //�N�H�[�^�j�I���B
	//int playerState = 0;	//�v���C���[�̃X�e�[�g(���)��\���ϐ��B
	//int starCount = 0;	//�W�߂����̐����J�E���g����B
	void Render(RenderContext& rc);
};
