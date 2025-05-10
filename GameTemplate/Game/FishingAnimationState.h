#pragma once
#include "PlayFishingStateBase.h"

class Player;
class FishingAnimationState:public PlayFishingStateBase
{
public:

	FishingAnimationState();
	~FishingAnimationState();
	bool Start();
	void Update();
	void Count();
	void SetCastAnimation();
	Player* m_player;
};

