#pragma once
class PlayFishingBackGround :public IGameObject
{
public:
	PlayFishingBackGround();
	~PlayFishingBackGround();

	void Render(RenderContext& rc);
	ModelRender modelRender;
	ModelRender m_ship;
	ModelRender m_isrand;
	PhysicsStaticObject physicsStaticObject;
};


