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
	if (befreVector.x != 0 || befreVector.y != 0 || befreVector.z != 0) {//入力があったら。
		CalculatingRotationQuantity();//回転の計算をする。
	}
	befreVector = nowVector;
	befreVector.Normalize();
}

void GetRotation::SetVectorA()
{
	//Lスティックの入力を取得。
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();
	
	//nowVectorにセットする。
	nowVector.x = stickL.x;
	nowVector.y = stickL.y;
	nowVector.z = 0.0f;

	//正規化する
	nowVector.Normalize();

}

float GetRotation::CalculatingRotationQuantity()
{
	GetRotationDirection();//回転の向きを取得。
	if (nowVector.x != befreVector.x || nowVector.y != befreVector.y) {//取得したベクトルが前と同じベクトルの時は計算しない。

		if (rotationDirection == RightTurn) {//右回転の時は回転量にプラスする。
			rotationQuantity += acos(Dot(nowVector, befreVector) / 2) / 100;//なぜか内積が1以上-1以下になるから÷2をした。
		}
		if (rotationDirection == LeftTurn) {//左回転ならマイナスする。
			rotationQuantity -= acos(Dot(nowVector, befreVector) / 2) / 100;
		}
	}
	return 0.0f;
}

void GetRotation::GetRotationDirection()
{
	if (Cross(nowVector, befreVector).z < 0)//
	{
		rotationDirection = LeftTurn;//左回転
	}
	if (Cross(nowVector, befreVector).z > 0)
	{
		rotationDirection = RightTurn;//右回転
	}
}
