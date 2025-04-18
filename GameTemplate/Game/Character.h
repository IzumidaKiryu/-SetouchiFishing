#pragma once
class Character : public IGameObject
{
public:
	Character();
	~Character();
	//�X�V�����B
	void Update();
	//���f���̐ݒ�B
	void SetModel(const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis);
	void SetAnimationClipsLoad(
		const char* animationClip_Idle,
		const char* animationClip_Walk
	);
	//���[�u�X�s�[�h��ݒ�B
	void virtual SetMoveSpeed();
	//�ړ������B
	void  Move();
	//��]�����B
	void Rotation();
	//�X�e�[�g�Ǘ��B
	void ManageState();
	//�A�j���[�V�����̍Đ��B
	void PlayAnimation();
	//void Render(RenderContext& rc);

	//�����o�ϐ��B
	ModelRender modelRender;	//���f�������_�\�B
	Vector3 m_position;			//���W�B
	enum EnAnimationClip {		//�A�j���[�V�����B
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		//enAnimationClip_Jump,
		enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];		//�A�j���[�V�����N���b�v�B
	CharacterController characterController;  //�L�����N�^�[�R���g���[���[�B
	Vector3 moveSpeed;		//�ړ����x�B
	Quaternion rotation;  //�N�H�[�^�j�I���B
	int playerState = 0;	//�v���C���[�̃X�e�[�g(���)��\���ϐ��B

};

