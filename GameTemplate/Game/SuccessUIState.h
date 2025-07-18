#pragma once
#include "CastState.h"

class SuccessUIState :public PlayFishingStateBase
{

public:
	enum SuccessUIMoveState {
		in,
		wait,
		out,
	};

	SuccessUIState();
	void Update();
	bool OnInit();
	bool OnStart();
	void SuccessUIMoveStateManager();
	void SetPosition();
	void In();
	void Wait();
	void Out();
	//void CameraManagement();
	void Render(RenderContext& rc);
private:
	float m_t=0.0f;
	Vector3 m_successUIPos=Vector3::Zero;
	Vector3 m_successUIBarPos=Vector3::Zero;

	Vector3 m_initSuccessUIPos_in = { 1500.0f,0.0f,0.0f };
	Vector3 m_initSuccessUIBarPos_in = { 1500.0f,0.0f,0.0f };
	Vector3 m_endSuccessUIPos_in = { 0.0f,0.0f,0.0f };
	Vector3 m_endSuccessUIBarPos_in{ 0.0f,0.0f,0.0f };


	Vector3 m_initSuccessUIPos_out = { 0.0f,0.0f,0.0f };
	Vector3 m_initSuccessUIBarPos_out = { 0.0f,0.0f,0.0f };
	Vector3 m_endSuccessUIPos_out = { -1500.0f,0.0f,0.0f };
	Vector3 m_endSuccessUIBarPos_out = { -1500.0f,0.0f,0.0f };


	SpriteRender m_successUI;
	SpriteRender m_successUI_Bar;

	SuccessUIMoveState m_successUIMoveState;
};
