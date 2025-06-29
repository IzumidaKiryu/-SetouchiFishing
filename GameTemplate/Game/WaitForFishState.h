#pragma once
#include "PlayFishingStateBase.h"

class FishDetectionRadius;
class SuccessUIState;
class WaitForFishState :public PlayFishingStateBase
{
public:
	enum go_fish_in_which {
		up,
		down,
	};

	WaitForFishState();
	~WaitForFishState();
	bool OnInit();
	bool OnStart();
	/*bool Start();*/
	void IsFloatInDetectionRange();
	void SetGoFishInWhich();
	void CameraManagement()override;
	void Update();

	void ComingFish();

	bool m_isFloatDetected=false;
	go_fish_in_which m_go_fish_in_which;//どっちの方向に進むか。
	FishDetectionRadius* m_fishDetectionRadius;
	SuccessUIState* m_successUIState;


};

