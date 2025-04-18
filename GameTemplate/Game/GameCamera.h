#pragma once

class Player;
//�Q�[�����̃J�����𐧌䂷��B
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	void SetTarget(Vector3 targetPos);
	/////////////////////////////////////
	//�����o�ϐ�
	/////////////////////////////////////
	Player* m_player;	//�v���C���[�B
	Vector3 m_toCameraPos = { 0.0f, 125.0f, -250.0f };	//�����_���王�_�Ɍ������x�N�g���B
	Vector3 m_fixedPos{ 1.0f,1000.0f,1.0f };
	Vector3 m_targetPos{ 0.0f,0.0f,0.0f };
};
