#include "stdafx.h"
#include "GetRotation.h"


GetRotation::GetRotation()
{
}

GetRotation::~GetRotation()
{
}

float GetRotation::GetFrameRotationDelta() const
{
	return m_frameRotationDelta;
}

void GetRotation::Update()
{
	//フレームの回転量をリセット
	m_frameRotationDelta = 0.0f;

	//スティックの入力量を更新する。
	UpdateStickInputVector();

	//入力があったら。
	if (m_prevVector.x != 0 || m_prevVector.y != 0 || m_prevVector.z != 0) {
		//回転の計算をする。
		CalculateRotationAmount();
	}

	//前のフレームのベクトルを更新する。
	m_prevVector = m_currentVector;

	//前のフレームのベクトルを正規化する。
	m_prevVector.Normalize();
}

void GetRotation::UpdateStickInputVector()
{
	//Lスティックの入力を取得するための変数。
	Vector2 leftStickInput = Vector2::Zero;

	//Lスティックの入力を取得。
	leftStickInput.x = g_pad[0]->GetLStickXF();
	leftStickInput.y = g_pad[0]->GetLStickYF();

	//currentVectorにセットする。
	m_currentVector.x = leftStickInput.x;
	m_currentVector.y = leftStickInput.y;
	m_currentVector.z = 0.0f;

	//正規化する
	m_currentVector.Normalize();
}

void GetRotation::CalculateRotationAmount()
{
	UpdateRotationDirection();//回転の向きを取得。
	//取得したベクトルが前と同じベクトルの時は計算しない。
	if (int(m_currentVector.x * 100) != int(m_prevVector.x * 100) || int(m_currentVector.y * 100) != int(m_prevVector.y * 100)) {

		float t = Dot(m_currentVector, m_prevVector);
		t = min(1.0f, t);
		t = max(-1.0f, t);
		if (m_rotationDirection == RightTurn) {//右回転の時は回転量にプラスする。
			m_frameRotationDelta = acos(t) / 20;
		}
	}
}

void GetRotation::UpdateRotationDirection()
{
	if (Cross(m_currentVector, m_prevVector).z < 0)
	{
		m_rotationDirection = LeftTurn;//左回転
	}
	if (Cross(m_currentVector, m_prevVector).z > 0)
	{
		m_rotationDirection = RightTurn;//右回転
	}
}
