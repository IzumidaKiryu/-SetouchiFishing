#pragma once
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

	Vector3 m_position;
};

