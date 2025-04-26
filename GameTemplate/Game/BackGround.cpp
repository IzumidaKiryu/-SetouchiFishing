#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	//�R�����g�A�E�g����B
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	modelRender.SetPosition(m_positio);
	modelRender.SetScale(Vector3{ 1.0f,1.0f,1.0f }*1.8);
	modelRender.Init("Assets/modelData/2Dship.tkm");
	//modelRender.Init("Assets/material/stera.tkm");
	modelRender.Update();
	physicsStaticObject.CreateFromModel(modelRender.GetModel(), modelRender.GetModel().GetWorldMatrix());
}

BackGround::~BackGround()
{

}

void BackGround::Update()
{
	Float();
	modelRender.SetPosition(m_floating + m_positio);
	modelRender.Update();
}

void BackGround::Float()
{
	t += 0.05;
	m_floating.y = (cos(t)) * 5;//�㉺�ɓ�����
	m_floating.x = (cos(t * 0.7/*���������炷*/) * 10);//���E�ɓ�����
}

void BackGround::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}