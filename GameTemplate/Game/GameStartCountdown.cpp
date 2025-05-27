#include "stdafx.h"
#include "GameStartCountdown.h"
#include "GameCamera.h"
#include"PositionSelection.h"
#include"FishSlot.h"
#include"BackGround.h"
#include "GameCamera.h"
#include <iostream>
#include <cmath>
#include< memory >


    
    
GameStartCountdown::GameStartCountdown()
{
	SetInitCameraRotation();
	SetCameraTarget();
	SetInitCameraPos();
	SetEndCameraPos();
	//カメラと船の間の距離を初期化。
	SetInitCameraToShipDistance();
	InitUI();
	//DeleteGO(this);
}
GameStartCountdown::~GameStartCountdown()
{
	m_stopwatch.Stop();
	m_positionSelection->Init();

	m_fishSlot = FindGO<FishSlot>("fishSlot");
	m_fishSlot->ThiscClassInit();
}

bool GameStartCountdown::Start()
{
	FindGameObjects();
    return true;
}

bool GameStartCountdown::ShouldChangeState()
{
	return false;
}

void GameStartCountdown::OnUpdate()
{
	m_camera = FindGO<GameCamera>("gameCamera");
	CountStart();

	//カウントダウンの時間を取得する。
	UpdateCountdownState();

	//UI大きさ更新
	UpdateUIScale();

	//UI更新
	UpdateUI();

	//カメラの更新
	UpdateCamera();

	NextScene();


}

void GameStartCountdown::OnEnter()
{
}

void GameStartCountdown::OnExit()
{
}

void GameStartCountdown::FindGameObjects()
{
	m_positionSelection = FindGO<PositionSelection>("positionSelection");

}

void GameStartCountdown::UpdateCountdownState()
{
	int time = m_stopwatch.GetElapsed();
	m_stopwatch.Stop();

	m_countdownState = ConvertTimeToCountdownState(time);

}

void GameStartCountdown::CountStart()
{
	if (isCountStart) {
		m_stopwatch.Start();
		isCountStart = false;
	}
}

void GameStartCountdown::SetInitCameraToShipDistance()
{
	m_backGround = FindGO<BackGround>("backGround");
	Vector2 initCameraToShipDistance2D;
	Vector2 shipPos2D= Vector2(m_backGround->m_shipPosition.x, m_backGround->m_shipPosition.z);
	Vector2 cameraPos2D= Vector2(m_initCameraPos.z, m_initCameraPos.x);

	//船とカメラの間のベクトル
	initCameraToShipDistance2D = Subtract(shipPos2D,cameraPos2D);

	//長さを取得
	m_initCameraToShipDistance=initCameraToShipDistance2D.GetLength();
}

CountdownState GameStartCountdown::ConvertTimeToCountdownState(int time) {
	switch (time) {
	case 0: return CountdownState::Three;
	case 1: return CountdownState::Two;
	case 2: return CountdownState::One;
	case 3: return CountdownState::Start;
	case 4:return CountdownState::NextScene;
	}
}


void GameStartCountdown::InitUI()
{
	SetUItexture();
	SetUIPivot(m_UIPivot);
	SetUIPosition(m_UIPos);
	UpdateUI();

}

void GameStartCountdown::SetUItexture()
{
	m_countdownUI[static_cast<int>(CountdownState::Three)].Init("Assets/modelData/timelimit_three.DDS", 130, 130);
	m_countdownUI[static_cast<int>(CountdownState::Two)].Init("Assets/modelData/timelimit_two.DDS", 130, 130);
	m_countdownUI[static_cast<int>(CountdownState::One)].Init("Assets/modelData/timelimit_one.DDS", 130, 130);
	m_countdownUI[static_cast<int>(CountdownState::Start)].Init("Assets/modelData/fish_display_ui_inside.DDS", 130, 130);

}


void GameStartCountdown::UpdateUI()
{
	for (int i = 0; i < 4; i++) {
		m_countdownUI[i].Update();
	}
}


void GameStartCountdown::SetUIPivot(Vector2 pivot)
{
	for (int i = 0; i < 4;i++) {
		m_countdownUI[i].SetPivot(pivot);
	}
}

void GameStartCountdown::SetUIPosition(Vector3 pos)
{
	for (int i = 0; i < 4; i++) {
		m_countdownUI[i].SetPosition(pos);
	}
}




void GameStartCountdown::UpdateUIScale()
{
	m_UIScale.Lerp(GetUIRatios(), m_initUIScale, m_endUIScale);
	SetUIScale(m_UIScale);
}
void GameStartCountdown::SetUIScale(Vector3 scale)
{
	for (int i = 0; i < 4; i++) {
		//フォントの大きさを設定。
		m_countdownUI[i].SetScale(scale);
	}
}

void GameStartCountdown::SetCameraPosition(Vector3 pos)
{
	m_camera = FindGO<GameCamera>("gameCamera");
	m_camera->SetPosition(UpdateCameraPostion());
}

Vector3 GameStartCountdown::UpdateCameraPostion()
{
	float thita;//回転度
	thita = GetCameraRatios()*2*3.1415926534;
	m_cameraPos.x = -(cos(thita))* UpdateCameraToShipDistance();
	m_cameraPos.z = sin(thita)* UpdateCameraToShipDistance();
	m_cameraPos.y = Lerp(GetCameraRatios(), m_initCameraPos.y, m_endCameraPos.y);

	return m_cameraPos;
}

float GameStartCountdown::UpdateCameraToShipDistance()
{
	m_CameraToShipDistance = Lerp(GetCameraRatios(), m_initCameraToShipDistance, m_endCameraToShipDistance);
	return m_CameraToShipDistance;
}


void GameStartCountdown::UpdateCamera()
{
	SetCameraPosition(UpdateCameraPostion());
	m_cameraPos;
}


void GameStartCountdown::SetCamera()
{

}


float GameStartCountdown::Lerp(float t, float init, float end)
{
	return init + t * (end - init);
}

Vector2 GameStartCountdown::Subtract(const Vector2& a, const Vector2& b)
{
	return { a.x - b.x, a.y - b.y };
}

float GameStartCountdown::GetUIRatios()
{
	int intTime = m_stopwatch.GetElapsed();
	float ratio= m_stopwatch.GetElapsed()-intTime;

	return ratio;
}

float GameStartCountdown::GetCameraRatios()
{
	int intTime = m_stopwatch.GetElapsed();
	float ratio = m_stopwatch.GetElapsed()/ static_cast<int>(CountdownState::NextScene);

	return ratio;
}

float GameStartCountdown::GetCameraToShipDistance()
{
	float initCameraToShipDistance;
	float endCameraToShipDistance=0;
	return 0.0f;
}

void GameStartCountdown::SetCameraTarget()
{
	m_backGround = FindGO<BackGround>("backGround");
	m_cameraTarget = m_backGround->m_shipPosition;
	m_camera->SetTarget(m_cameraTarget);
}

void GameStartCountdown::SetInitCameraPos()
{
	m_backGround = FindGO<BackGround>("backGround");
	m_initCameraPos = m_backGround->m_shipPosition + Vector3{ 0.0f,200.0f,1500.0f };

}

void GameStartCountdown::SetEndCameraPos()
{
	m_backGround = FindGO<BackGround>("backGround");
	m_endCameraPos = m_backGround->m_shipPosition + Vector3{ 0.0f,1500.0f,0.0f };
}

void GameStartCountdown::SetInitCameraRotation()
{
	m_camera = FindGO<GameCamera>("gameCamera");

	Quaternion rot;
	rot.AddRotationDegZ(180);
	m_camera->RotateOriginTarget(rot);
}


void GameStartCountdown::Render(RenderContext& rc)
{
	switch (m_countdownState)
	{
	case CountdownState::None:
		break;
	case CountdownState::Three:
		m_countdownUI[static_cast<int>(CountdownState::Three)].Draw(rc);
		break;
	case CountdownState::Two:
		m_countdownUI[static_cast<int>(CountdownState::Two)].Draw(rc);
		break;
	case CountdownState::One:
		m_countdownUI[static_cast<int>(CountdownState::One)].Draw(rc);
		break;
	case CountdownState::Start:
		m_countdownUI[static_cast<int>(CountdownState::Start)].Draw(rc);
		break;
	default:
		break;
	}
	
}

void GameStartCountdown::NextScene()
{
	if (m_countdownState == CountdownState::NextScene) {
		DeleteGO(this);
	}
}


