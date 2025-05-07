#pragma once
class PlayFishing;
class FishModel :public IGameObject
{
public:

	FishModel();
	~FishModel();
	void Update();
	ModelRender m_fishModel;
	void Render(RenderContext& rc);
	void SetPosition(Vector3 position);
	void SetInitPositon();
	void SetPosition();
	void SetSumPosition(Vector3 position);
	float ChangePosition_Z(float current_fish_range_and_max_range_rate);//魚の距離の割合いを、魚のｚポジションに変える。
	float GetCurrentFishRangeAndMaxRangeRate(float position_z);
	Vector3 GetPosistion();

	float m_limit_range_with_ship=2010.1f;
	Vector3 m_position;

	PlayFishing* m_playFishing;
};

