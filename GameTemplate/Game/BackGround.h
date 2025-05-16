#pragma once
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	void Update();
	void Float();
	void BackGroundDeactive();
	void BackGroundActive();

	void Render(RenderContext& rc);
	float t;
	Vector3 m_shipPosition{ 0.0f,-100.0f,-200.0f };
	Vector3 m_seaPosition{ 100.0f,-100.0f,120.0f };
	Vector3 m_floating;
	ModelRender modelRender;
	ModelRender m_sea;
	PhysicsStaticObject physicsStaticObject;
};

