#pragma once
class GetRotation : public IGameObject
{
public:
	GetRotation();
	~GetRotation();
	void Update();
	void SetVectorA();
	float CalculatingRotationQuantity();//回転量を計算
	void GetRotationDirection();//回転方向を取得

	Vector2 stickL;
	Vector3 nowVector;//今のフレームで取得したベクトル。
	Vector3 befreVector={0.0f,0.0f,0.0f};//前のフレームで取得したベクトル。
	float rotationQuantity=0.0f;//回転量
	float nowFrameRotationQuantity = 0.0f;//今のフレームでの回転量。（回転量がマイナスの時は0）

	enum RotationDirection {
		Nonturn,
		RightTurn,//右回転(時計回り)
		LeftTurn//左回転（反時計回り）
	};
	RotationDirection rotationDirection= Nonturn;//回転の方向
};

