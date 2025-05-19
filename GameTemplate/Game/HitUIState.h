#pragma once
#include "WaitForFishState.h"

class HitUIState :public PlayFishingStateBase
{

public:
	enum UIMoveState {
		in,
		wait,
		out,
	};

	HitUIState();
	void Update();
	bool Start();
	void UIMoveStateManager();
	void SetPosition();
	void In();
	void Wait();
	void Out();
	void Render(RenderContext& rc);


	
	float m_t;
	Vector3 m_hitUIPos;
	Vector3 m_hitUIBarPos;

	Vector3 m_initHitUIPos_in = { 1500.0f,0.0f,0.0f };
	Vector3 m_initHitUIBarPos_in = { 1500.0f,0.0f,0.0f };
	Vector3 m_endHitUIPos_in = { 0.0f,0.0f,0.0f };
	Vector3 m_endHitUIBarPos_in{ 0.0f,0.0f,0.0f };


	Vector3 m_initHitUIPos_out = { 0.0f,0.0f,0.0f };
	Vector3 m_initHitUIBarPos_out = { 0.0f,0.0f,0.0f };
	Vector3 m_endHitUIPos_out = { -1500.0f,0.0f,0.0f };
	Vector3 m_endHitUIBarPos_out = { -1500.0f,0.0f,0.0f };

	
	SpriteRender m_hitUI;
	SpriteRender m_hitUI_Bar;

	UIMoveState m_uiMoveState;
};

