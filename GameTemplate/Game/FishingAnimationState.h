#pragma once
#include "PlayFishingStateBase.h"
class FishModel;
class Player;
class FishingAnimationState:public PlayFishingStateBase
{
public:

	FishingAnimationState();
	~FishingAnimationState();
	void CameraManagement()override;
	void Update();
	void Count();
	bool SetCastAnimation();
	Player* m_player;
	FishModel* m_fishModel;
};

