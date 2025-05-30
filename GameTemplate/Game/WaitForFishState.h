#pragma once
#include "PlayFishingStateBase.h"

class FishDetectionRadius;
class WaitForFishState :public PlayFishingStateBase
{
public:
	enum go_fish_in_which {
		up,
		down,
	};
	bool Start();

	WaitForFishState();
	~WaitForFishState();
	/*bool Start();*/
	void IsFloatInDetectionRange();
	void SetGoFishInWhich();
	void CameraManagement()override;
	void Update();

	void ComingFish();

	float m_isFloatDetected=false;
	go_fish_in_which m_go_fish_in_which;//どっちの方向に進むか。
	FishDetectionRadius* m_fishDetectionRadius;
};

