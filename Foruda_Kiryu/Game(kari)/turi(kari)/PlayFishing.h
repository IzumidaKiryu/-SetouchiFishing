#pragma once
class CastGauge;
class FishingGauge;
class GameCamera;
class PlayFishingBackGround;
class PlayFishing :public IGameObject
{
public:
	PlayFishing();
	~PlayFishing();
	void Update();
	void CallCastGauge();
	void CallFishingGauge();
	CastGauge* castGauge;
	FishingGauge* fishingGauge;
	GameCamera* gameCamera;			//�Q�[���J�����B
	PlayFishingBackGround* m_playFishingBackGround;
};
