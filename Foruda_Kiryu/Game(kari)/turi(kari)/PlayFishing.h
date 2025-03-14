#pragma once
class CastGauge;
class GameCamera;
class PlayFishingBackGround;
class PlayFishing :public IGameObject
{
public:
	PlayFishing();
	~PlayFishing();
	void Update();
	void CallCastGauge();
	CastGauge* castGauge;
	GameCamera* gameCamera;			//�Q�[���J�����B
	PlayFishingBackGround* m_playFishingBackGround;
};
