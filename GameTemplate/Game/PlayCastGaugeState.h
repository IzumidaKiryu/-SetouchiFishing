#pragma once
#include "PlayFishingStateBase.h"
class CastGauge;
class Player;
class PlayCastGaugeState:public PlayFishingStateBase
{

public:

	PlayCastGaugeState();
	~PlayCastGaugeState();
	void Update();

	Player* m_player;
	CastGauge* m_castGauge;
};

