#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	//コメントアウトする。
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	modelRender.SetPosition(Vector3{ -400.0f,0.0f,0.0f });
	//modelRender.Init("Assets/modelData/stage/stage.tkm");
	modelRender.Init("Assets/material/stera.tkm");
	modelRender.Update();
	physicsStaticObject.CreateFromModel(modelRender.GetModel(), modelRender.GetModel().GetWorldMatrix());
}

BackGround::~BackGround()
{

}

void BackGround::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}