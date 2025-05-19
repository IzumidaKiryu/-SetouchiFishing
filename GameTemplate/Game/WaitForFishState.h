#pragma once
#include "PlayFishingStateBase.h"

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
	void SetGoFishInWhich();
	void CameraManagement()override;
	void Update();

	void ComingFish();
	go_fish_in_which m_go_fish_in_which;//どっちの方向に進むか。

};

