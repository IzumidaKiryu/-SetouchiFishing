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
	/*g_soundEngine->ResistWaveFileBank(1, "Assets/sound/mainGameBGM.wav");

	m_sound = NewGO<SoundSource>(1);

	m_sound->Init(1);

	m_sound->Play(false);*/
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


	//modelRender.Init("Assets/material/stera.tkm");
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

	//船に当たり判定を反映。
	//physicsStaticObject.CreateFromModel(m_ship.GetModel(), m_ship.GetModel().GetWorldMatrix());

	return true;
}

void BackGround::Update()
{
	Float();
	m_ship.SetPosition(m_floating + m_shipPosition);
	m_ship.Update();

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
	physicsStaticObject.CreateFromModel(m_ship.GetModel(), m_ship.GetModel().GetWorldMatrix());

}



void BackGround::Render(RenderContext& rc)
{
	m_sea.Draw(rc);
	m_ship.Draw(rc);
	m_isrand.Draw(rc);
}