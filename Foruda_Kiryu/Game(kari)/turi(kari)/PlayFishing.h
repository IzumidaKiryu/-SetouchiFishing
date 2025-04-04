#pragma once
class CastGauge;
class FishingGauge;
class GameCamera;
class PlayFishingBackGround;
class PositionSelection;
class FishManager;

class PlayFishing :public IGameObject
{
public:
	PlayFishing();
	~PlayFishing();
	void Update();
	void CallCastGauge();
	void DeleteThisClass();
	void SetFishManagerObjectName(std::string string_objectName);
	void FindeFishManager();//フィッシュマネージャーを探して魚の情報を取得する。　
	char* m_objectName;

	CastGauge* m_castGauge;
	GameCamera* gameCamera;			//�Q�[���J�����B
	PlayFishingBackGround* m_playFishingBackGround;
	PositionSelection* m_positionSelection;
	FishManager* m_fishManager;
};
