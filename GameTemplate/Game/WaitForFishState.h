#pragma once
#include "PlayFishingStateBase.h"

class FishDetectionRadius;
class SuccessUIState;
class WaitForFishState :public PlayFishingStateBase
{
public:
	enum FishMovementDirection {
		up,
		down,
	};

	WaitForFishState();
	~WaitForFishState();
	bool OnInit();
	bool OnStart();
	void IsFloatInDetectionRange();
	void SetGoFishInWhich();
	void CameraManagement()override;
	void Update();
	void ComingFish();

private:
	bool m_isFloatDetected=false;
	FishMovementDirection m_fishMovementDirection=down;//どっちの方向に進むか。
	FishDetectionRadius* m_fishDetectionRadius=nullptr;
	SuccessUIState* m_successUIState=nullptr;


};

