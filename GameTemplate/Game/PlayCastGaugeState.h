#pragma once
#include "PlayFishingStateBase.h"
class CastGauge;
class Player;
class PlayCastGaugeState:public PlayFishingStateBase
{

public:

	PlayCastGaugeState();
	~PlayCastGaugeState();
	bool OnInit()override;
	bool OnStart()override;
	void Update();
	void CameraManagement()override;
	void SetArrowSpead();

	Player* m_player=nullptr;
	CastGauge* m_castGauge=nullptr;
};

