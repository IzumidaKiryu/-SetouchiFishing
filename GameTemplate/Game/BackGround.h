#pragma once
#include "sound/SoundSource.h"
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start()override;
	bool Init();
	void Update();
	void Float();
	void BackGroundDeactive();
	void BackGroundActive();

	void Render(RenderContext& rc);
	float t;
	Vector3 m_shipPosition{ 0.0f,-100.0f,-400.0f };
	Vector3 m_israndPosition {-500.0f, 0.0f, 4000.0f};
	Vector3 m_seaPosition{ 100.0f,-100.0f,120.0f };
	Vector3 m_floating;
	ModelRender m_ship;
	ModelRender m_sea;
	ModelRender m_isrand;
	ModelRender m_hitBox;
	PhysicsStaticObject physicsStaticObject;
	//SoundSource* m_sound;
};

