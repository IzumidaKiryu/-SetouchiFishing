#pragma once
#include "PlayFishingStateBase.h"

class WaitForFishState :public PlayFishingStateBase
{
public:

	WaitForFishState();
	~WaitForFishState();
	void Update();

	void ComingFish();
};

