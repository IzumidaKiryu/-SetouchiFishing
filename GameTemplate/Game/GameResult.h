#pragma once
class GameResult :public IGameObject
{
public:
	enum FishName {
		Hamachi,
		Tachiuo,
		Tai,
		Hirame,
		Pearl,
		Jakoten,
		num
	};
	GameResult();
	~GameResult();
	bool Start();
	void Update();
	void SetFastPos();//�e�z��̏�����
	void Render(RenderContext& rc);
	void Easing(FishName name, Vector3 fastPos, Vector3 endPos);

	Vector3 m_fastPos[num] = {//�C�[�W���O�O�̍��W�B
		{ -350.0f,220.0f,0.0f } ,
		{ -350.0f,130.0f,0.0f },
		{ -350.0f,40.0f,0.0f },
		{ -350.0f,-50.0f,0.0f },
		{ -350.0f,-140.0f,0.0f },
		{ -350.0f,-230.0f,0.0f }
	};

	Vector3 m_endPos[num]{//�C�[�W���O��̍��W�B
		{ -600.0f,220.0f,0.0f },
		{ -600.0f,130.0f,0.0f },
		{ -600.0f,40.0f,0.0f },
		{ -600.0f,-50.0f,0.0f },
		{ -600.0f,-140.0f,0.0f },
		{ -600.0f,-230.0f,0.0f }
	};

	Vector3 m_vec[num];//�eUI�̃|�W�V�����B
	float m_t[num];			//�⊮���B

	SpriteRender m_fishUI[6];//���W�������̕\���p�X�v���C�g�����_�[�B
	SpriteRender m_back;//���U���g��ʂ̔w�i�p�X�v���C�g�����_�[�B

	int nowFishName = FishName::Hamachi;//�C�[�W���O�����鋛��UI(�����ݒ�̓n�}�`)�B
};
