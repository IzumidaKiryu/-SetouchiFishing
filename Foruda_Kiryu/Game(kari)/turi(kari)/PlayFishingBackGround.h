#pragma once
class PlayFishingBackGround :public IGameObject
{
public:
	PlayFishingBackGround();
	~PlayFishingBackGround();

	void Render(RenderContext& rc);
	ModelRender modelRender;
	PhysicsStaticObject physicsStaticObject;
};


