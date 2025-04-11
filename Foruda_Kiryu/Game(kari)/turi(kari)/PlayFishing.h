#pragma once
#include "Fish.h"

enum PlayFishingStatus {
	chastGauge,
	fishingGsauge,
	tensionGauge
};

enum  Successful_or_Failure {
	unfixed,//未確定
	success,//成功
	failure//失敗
};

class CastGauge;
class FishingGauge;
class GameCamera;
class PlayFishingBackGround;
class PositionSelection;
class FishManager;
class FishingGauge;
class TensionGauge;
class FishingRodHP;

class PlayFishing :public IGameObject
{
public:
	PlayFishing();
	~PlayFishing();
	void Init();
	void Update();
	void NewGOCastGauge();
	void NewGOFishingGauge();
	void NewGOTensionGauge();
	void DeleteThisClass();
	void SetFishManagerObjectName(std::string string_objectName);
	void FindeFishManager();//フィッシュマネージャーを探して魚の情報を取得する。　
	char* m_objectName;
	void StatusManager();
	void NewGOFishingRodHP();
	bool canNewGOFishingRodHP=true;//釣り竿のHPクラスをNewGO可能か。
	void SetSuccess();
	void SetFailure();
	void Unfixed();//Successful_or_Failureを未確定にする。
	void Success();
	void Failure();
	void SetPlayFishingStatus_FishingGsauge();//プレイフィッシングステートをフィッシングゲージにする。
	void SetFishData();
	FishData& GetFishData();
	float GetFIshScore();//スコアディスプレイクラスにスコアを渡す関数。



	PlayFishingStatus m_playFishingStatus= chastGauge;
	Successful_or_Failure m_successful_or_failure= unfixed;

	FishData m_fishData;//魚のデータ。
	FishData* p_fishData = &m_fishData;//フィッシュデータのポインタ


	CastGauge* m_castGauge;
	GameCamera* gameCamera;			//�Q�[���J�����B
	PlayFishingBackGround* m_playFishingBackGround;
	PositionSelection* m_positionSelection;
	FishManager* m_fishManager;
	FishingGauge* m_fishingGauge;
	TensionGauge* m_tensionGauge;
	FishingRodHP* m_fishingRodHP;
};
