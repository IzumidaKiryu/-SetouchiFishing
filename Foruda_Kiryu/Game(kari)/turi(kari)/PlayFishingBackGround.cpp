#include "stdafx.h"
#include "PlayFishingBackGround.h"

PlayFishingBackGround::PlayFishingBackGround()
{
	//コメントアウトする。
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	modelRender.Init("Assets/modelData/stage/stage.tkm");
	modelRender.Update();
	physicsStaticObject.CreateFromModel(modelRender.GetModel(), modelRender.GetModel().GetWorldMatrix());
}

PlayFishingBackGround::~PlayFishingBackGround()
{
}


void PlayFishingBackGround::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
