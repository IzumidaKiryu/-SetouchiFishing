#include "stdafx.h"
#include "PlayFishingBackGround.h"

PlayFishingBackGround::PlayFishingBackGround()
{
	//?R?????g?A?E?g????B
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	modelRender.Init("Assets/modelData/sea_kari.tkm");
	modelRender.SetScale(Vector3(10.0f, 10.0f, 10.0f));
	modelRender.Update();
	/*physicsStaticObject.CreateFromModel(modelRender.GetModel(), modelRender.GetModel().GetWorldMatrix());*/

}

PlayFishingBackGround::~PlayFishingBackGround()
{

}


void PlayFishingBackGround::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
