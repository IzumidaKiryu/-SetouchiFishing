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

	float m_limit_range_with_ship=2010.1f;
	Vector3 m_position;

	PlayFishing* m_playFishing;
};

