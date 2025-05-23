#include "stdafx.h"
#include "PlayFishingBackGround.h"

PlayFishingBackGround::PlayFishingBackGround()
{
	//?R?????g?A?E?g????B
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	modelRender.Init("Assets/modelData/sea_kari.tkm",false);
	modelRender.SetScale(Vector3(10.0f, 10.0f, 10.0f));
	modelRender.Update();

	m_ship.Init("Assets/modelData/newStage/MAP.tkm",false);
	m_ship.SetScale(Vector3(1.0f, 1.0f, 1.0f));
	m_ship.Update();


	m_isrand.Init("Assets/modelData/stage/shima.tkm");
	m_isrand.SetPosition(Vector3(-500.0f, 0.0f, 4000.0f));
	m_isrand.SetScale(Vector3(10.0f, 10.0f, 10.0f));
	m_isrand.Update();

	/*physicsStaticObject.CreateFromModel(modelRender.GetModel(), modelRender.GetModel().GetWorldMatrix());*/

}

PlayFishingBackGround::~PlayFishingBackGround()
{

}


void PlayFishingBackGround::Render(RenderContext& rc)
{
	/*modelRender.Draw(rc);*/
	/*m_ship.Draw(rc);*/
	m_isrand.Draw(rc);
}
