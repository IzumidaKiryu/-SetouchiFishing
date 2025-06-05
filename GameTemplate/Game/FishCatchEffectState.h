#pragma once
#include "PlayFishingStateBase.h"


class FishCatchEffectState :public PlayFishingStateBase
{
public:
	FishCatchEffectState();
	~FishCatchEffectState();

	Vector3 m_initCameraPos;

};

