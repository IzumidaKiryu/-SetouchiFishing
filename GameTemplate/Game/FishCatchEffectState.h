#pragma once
#include "PlayFishingStateBase.h"


class FishCatchEffectState :public PlayFishingStateBase
{
public:
	FishCatchEffectState();
	~FishCatchEffectState();
	bool Start();

	Vector3 m_initCameraPos;

};

