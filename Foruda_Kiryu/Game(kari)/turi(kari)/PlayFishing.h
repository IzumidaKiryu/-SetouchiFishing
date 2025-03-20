#pragma once
class CastGauge;
class GameCamera;
class PlayFishingBackGround;
class PositionSelection;

class PlayFishing :public IGameObject
{
public:
	PlayFishing();
	~PlayFishing();
	void Update();
	void CallCastGauge();
	void DeleteThisClass();
	CastGauge* m_castGauge;
	GameCamera* gameCamera;			//�Q�[���J�����B
	PlayFishingBackGround* m_playFishingBackGround;
	PositionSelection* m_positionSelection;
};
