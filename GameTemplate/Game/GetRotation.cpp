#include "stdafx.h"
#include "GetRotation.h"


GetRotation::GetRotation()
{
}

GetRotation::~GetRotation()
{

}

void GetRotation::Update()
{
	nowFrameRotationQuantity = 0.0f;

	SetVectorA();
	if (befreVector.x != 0 || befreVector.y != 0 || befreVector.z != 0) {//���͂���������B
		CalculatingRotationQuantity();//��]�̌v�Z������B
	}
	befreVector = nowVector;
	befreVector.Normalize();
}

void GetRotation::SetVectorA()
{
	//L�X�e�B�b�N�̓��͂��擾�B
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//nowVector�ɃZ�b�g����B
	nowVector.x = stickL.x;
	nowVector.y = stickL.y;
	nowVector.z = 0.0f;

	//���K������
	nowVector.Normalize();

}

float GetRotation::CalculatingRotationQuantity()
{
	GetRotationDirection();//��]�̌������擾�B
	if (int(nowVector.x * 100) != int(befreVector.x * 100) || int(nowVector.y * 100) != int(befreVector.y * 100)) {//�擾�����x�N�g�����O�Ɠ����x�N�g���̎��͌v�Z���Ȃ��B

		float t = Dot(nowVector, befreVector);
		t = min(1.0f, t);
		t = max(-1.0f, t);
		if (rotationDirection == RightTurn) {//�E��]�̎��͉�]�ʂɃv���X����B
			rotationQuantity += acos(t) / 20;//�Ȃ������ς�1�ȏ�-1�ȉ��ɂȂ邩�灀2�������B
			nowFrameRotationQuantity = acos(t) / 20;
		}
		if (rotationDirection == LeftTurn) {//����]�Ȃ�}�C�i�X����B
			rotationQuantity -= acos(t) / 20;
		}
	}
	return 0.0f;
}

void GetRotation::GetRotationDirection()
{
	if (Cross(nowVector, befreVector).z < 0)//
	{
		rotationDirection = LeftTurn;//����]
	}
	if (Cross(nowVector, befreVector).z > 0)
	{
		rotationDirection = RightTurn;//�E��]
	}
}
