#pragma once
class GetRotation : public IGameObject
{
public:
	GetRotation();
	~GetRotation();

public:
	float GetFrameRotationDelta() const;// 回転量を取得

private:
	void Update();

	/// <summary>
	/// スティックの入力量を更新する。
	/// </summary>
	void UpdateStickInputVector();

	/// <summary>
	/// 回転量を計算
	/// </summary>
	void CalculateRotationAmount();

	/// <summary>
	/// 回転方向を更新。
	/// </summary>
	void UpdateRotationDirection();

private:
	//今のフレームで取得したベクトル。
	//外積を計算するためVector3型にしている。
	Vector3 m_currentVector=Vector3::Zero;

	//前のフレームで取得したベクトル。
	Vector3 m_prevVector = { 0.0f,0.0f,0.0f };

	//今のフレームの回転量の変化
	float m_frameRotationDelta = 0.0f;

	enum RotationDirection {
		Nonturn,
		RightTurn,//右回転(時計回り)
		LeftTurn//左回転（反時計回り）
	};
	RotationDirection m_rotationDirection = Nonturn;//回転の方向
};

