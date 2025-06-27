#pragma once
#include"GameStateBase.h"
#include< memory >


enum class CountdownState
{
	None = -1,
	Three,
	Two,
	One,
	Start,
	NextScene
};

class PositionSelection;
class FishSlot;
class BackGround;
class GameCamera; 
class InGameState;

class GameStartCountdown : public IGameObject
{
public:

	GameStartCountdown();
	~GameStartCountdown();

	void Update();
	bool Start();
	void FindGameObjects();

private:




	void SetInitCameraToShipDistance();
	void InitCamera();
	CountdownState ConvertTimeToCountdownState(int time);
	void UpdateCountdownState();

	void CountStart();

	std::string ToString(CountdownState count);

	void InitUI();

	void SetUItexture();

	void UpdateUI();

	void SetUIPivot(Vector2 pivot);

	void SetUIPosition(Vector3 pos);


	void UpdateUIScale();
	void SetUIScale(Vector3 scale);


	void SetCamera();
	void SetCameraPosition(Vector3 pos);
	Vector3 UpdateCameraPostion();
	float UpdateCameraToShipDistance();

	
	void UpdateCamera();

	float Lerp(float t,float init,float end);
	Vector2 Subtract(const Vector2& a, const Vector2& b);

	float  GetUIRatios();
	float GetCameraRatios();
	float GetCameraToShipDistance();

	void SetCameraTarget();
	void SetInitCameraPos();
	void SetEndCameraPos();
	void SetInitCameraRotation();


	void Render(RenderContext& rc);

	void NextScene();

	bool isCountStart=true;

	CountdownState m_countdownState = CountdownState::Three;

	Vector2 m_UIPivot = { 0.5f,0.5f};
	Vector3 m_UIPos = { 0.0f,0.0f,0.0f };


	const Vector3 m_initUIScale = Vector3::One*0.5;
	const Vector3 m_endUIScale = Vector3::One*5;
	Vector3 m_UIScale=Vector3::One ;


	SpriteRender m_countdownUI[4];


	Vector3 m_cameraPos=Vector3::Zero;
	Vector3 m_initCameraPos=Vector3::Zero;
	Vector3 m_endCameraPos=Vector3::Zero;

	Vector3 m_cameraTarget=Vector3::Zero;


	float m_initCameraToShipDistance=0;
	float m_endCameraToShipDistance = 0;
	float m_CameraToShipDistance=0;


	Vector3 m_endCameraTarget = Vector3::Zero;

	Stopwatch m_stopwatch;

	PositionSelection* m_positionSelection=nullptr;
	FishSlot* m_fishSlot = nullptr;
	BackGround* m_backGround = nullptr;
	GameCamera* m_camera = nullptr;
	InGameState* m_inGameState = nullptr;

};

