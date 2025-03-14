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
	//GetRotationDirection();//��]�̌������擾�B
	//nowVector.x=int(nowVector.x * 100) / 100;
	//nowVector.y=int(nowVector.y * 100) / 100;
	//befreVector.x=int(befreVector.x *100) / 100;
	//befreVector.y=int(befreVector.y * 100) / 100;

	if (int(nowVector.x*1000) != int(befreVector.x*1000) || int(nowVector.y*1000) != int(befreVector.y*1000)) {//�擾�����x�N�g�����O�Ɠ����x�N�g���̎��͌v�Z���Ȃ��B//���̌��͐؂�̂Ă���B

		if (rotationDirection == RightTurn) {//�E��]�̎��͉�]�ʂɃv���X����B
			rotationQuantity += acos(Dot(nowVector, befreVector) / 2);//�Ȃ������ς�1�ȏ�-1�ȉ��ɂȂ邩�灀2�������B
		}
		if (rotationDirection == LeftTurn) {//����]�Ȃ�}�C�i�X����B
			rotationQuantity -= acos(Dot(nowVector, befreVector) / 2);
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
