#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}

bool BackGround::Start()
{
	return true;
}

bool BackGround::Init()
{

	//コメントアウトする。

	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	m_ship.SetPosition(m_shipPosition);
	m_ship.SetScale(Vector3{ 1.0f,1.0f,1.0f }*1.5f);
	m_ship.Init("Assets/modelData/2DShip/2DNewShip.tkm", nullptr, 0, enModelUpAxisZ, false, true);

	m_hitBox.SetPosition(m_shipPosition);
	m_hitBox.SetScale(Vector3{1.0f,1.0f,1.0f }*1.5f);
	m_hitBox.Init("Assets/modelData/2DShipFloor.tkm", nullptr, 0, enModelUpAxisZ, false, true);


	m_hitBox.Update();

	physicsStaticObject.CreateFromModel(m_hitBox.GetModel(), m_hitBox.GetModel().GetWorldMatrix());


	m_sea.SetPosition(/*m_positio*/Vector3{ 1.0f,1.0f,1.0f });
	m_sea.SetScale(Vector3{ 1.0f,1.0f,1.0f }*10.0f);
	m_sea.Init("Assets/modelData/sea_Kari.tkm", nullptr, 0, enModelUpAxisZ, false, true);
	m_sea.Update();

	m_isrand.Init("Assets/modelData/stage/shima.tkm", nullptr, 0, enModelUpAxisZ, true, false);
	m_isrand.SetPosition(m_israndPosition);
	m_isrand.SetScale(Vector3(10.0f, 10.0f, 10.0f));
	m_isrand.Update();


	return true;
}

void BackGround::Update()
{
	UpdateFloating();
	m_ship.SetPosition(m_floating + m_shipPosition);
	m_ship.Update();

}

void BackGround::UpdateFloating()
{
	floatingTime += 0.05;
	m_floating.y = (cos(floatingTime)) * 5;//上下に動かす
	m_floating.x = (cos(floatingTime * 0.7/*周期をずらす*/) * 10);//左右に動かす
}

Vector3 BackGround::GetShipPosition() const
{
	return m_shipPosition;
}

void BackGround::Render(RenderContext& rc)
{
	m_sea.Draw(rc);
	m_ship.Draw(rc);
	m_isrand.Draw(rc);
}