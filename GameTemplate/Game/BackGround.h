#pragma once
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	void Update();
	void Float();

	void Render(RenderContext& rc);
	float t;
	Vector3 m_positio{ 100.0f,-100.0f,120.0f };
	Vector3 m_floating;
	ModelRender modelRender;
	PhysicsStaticObject physicsStaticObject;
};

