#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	//コメントアウトする。
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	modelRender.SetPosition(m_shipPosition);
	modelRender.SetScale(Vector3{ 1.0f,1.0f,1.0f }*1.8);
	modelRender.Init("Assets/modelData/2Dship.tkm",false);
	//modelRender.Init("Assets/material/stera.tkm");
	modelRender.Update();

	physicsStaticObject.CreateFromModel(modelRender.GetModel(), modelRender.GetModel().GetWorldMatrix());


	m_sea.SetPosition(/*m_positio*/Vector3{ 1.0f,1.0f,1.0f });
	m_sea.SetScale(Vector3{ 1.0f,1.0f,1.0f }*10.0f);
	m_sea.Init("Assets/modelData/sea_kari.tkm",false);
	m_sea.Update();
}

BackGround::~BackGround()
{

}

void BackGround::Update()
{
	Float();
	modelRender.SetPosition(m_floating + m_shipPosition);
	modelRender.Update();

}

void BackGround::Float()
{
	t += 0.05;
	m_floating.y = (cos(t)) * 5;//上下に動かす
	m_floating.x = (cos(t * 0.7/*周期をずらす*/) * 10);//左右に動かす
}

void BackGround::BackGroundDeactive()
{
	if (m_isActive != true) {
		physicsStaticObject.Release();
	}
}

void BackGround::BackGroundActive()
{
	physicsStaticObject.CreateFromModel(modelRender.GetModel(), modelRender.GetModel().GetWorldMatrix());

}



void BackGround::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
	m_sea.Draw(rc);
}