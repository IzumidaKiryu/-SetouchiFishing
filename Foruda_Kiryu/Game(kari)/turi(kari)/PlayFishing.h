#pragma once
class CastGauge;
class GameCamera;
class PlayFishingBackGround;
class PlayFishing:public IGameObject
{
public:
	PlayFishing();
	~PlayFishing();
	void Update();
	void CallCastGauge();
	CastGauge* castGauge;
	GameCamera* gameCamera;			//ƒQ[ƒ€ƒJƒƒ‰B
	PlayFishingBackGround* m_playFishingBackGround;
};

