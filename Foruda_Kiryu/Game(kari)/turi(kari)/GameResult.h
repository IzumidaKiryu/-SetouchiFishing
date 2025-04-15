#pragma once
class GameResult:public IGameObject
{
public:
	enum fishName {
		Buri,
		Tachiuo,
		Tai,
		Hirame,
		Sinzyu,
		Zyako,
	};
	GameResult();
	~GameResult();
	bool start();
	void Update();
	void Render(RenderContext&rc);
	void Eaging(fishName name,Vector3 fastPos,Vector3 endPos);
	
	Vector3 fastPos;//�C�[�W���O�O�̍��W�B
	Vector3 endPos;//�C�[�W���O��̍��W�B
	Vector3 m_vec = Vector3::Zero;
	int m_t = 0.0f;//�⊮���B

	SpriteRender m_fishUI[6];//���W�������̕\���p�X�v���C�g�����_�[�B
	SpriteRender m_back;
};

