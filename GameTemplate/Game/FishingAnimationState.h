#pragma once
#include "PlayFishingStateBase.h"
class FishModel;
class Player;
class FishingAnimationState:public PlayFishingStateBase
{
public:

	FishingAnimationState();
	~FishingAnimationState();
	bool OnInit();
	bool OnStart();
	void CameraManagement()override;
	void Update();
	void Count();
	bool SetCastAnimation();
};

