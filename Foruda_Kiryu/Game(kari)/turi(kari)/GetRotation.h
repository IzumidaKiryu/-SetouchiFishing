#pragma once
class GetRotation : public IGameObject
{
public:
	GetRotation();
	~GetRotation();
	void Update();
	void SetVectorA();
	float CalculatingRotationQuantity();//��]�ʂ��v�Z
	void GetRotationDirection();//��]�������擾

	Vector2 stickL;
	Vector3 nowVector;//���̃t���[���Ŏ擾�����x�N�g���B
	Vector3 befreVector={0.0f,0.0f,0.0f};//�O�̃t���[���Ŏ擾�����x�N�g���B
	float rotationQuantity=0.0f;//��]��
	float nowFrameRotationQuantity = 0.0f;//���̃t���[���ł̉�]�ʁB�i��]�ʂ��}�C�i�X�̎���0�j

	enum RotationDirection {
		Nonturn,
		RightTurn,//�E��](���v���)
		LeftTurn//����]�i�����v���j
	};
	RotationDirection rotationDirection= Nonturn;//��]�̕���
};

