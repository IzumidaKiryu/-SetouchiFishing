#pragma once
class PlayFishing;
class TensionGauge;
class FishDetectionRadius:public IGameObject
{
public:
	FishDetectionRadius();
	~FishDetectionRadius();
	bool Init();
	bool Start() override;
	void Update();
	void CalculateDetectionRange();
	void CalculateDetectionRangePos();
	void CalculateFishDetectionRadiusUIScale();
	float GetFishDetectionRadius();
	float GetPos();
	void DeletThis();
	SpriteRender& GetUI();

	void SetFishDetectionRadiusUIPosition();
	Vector3 m_uiScale = { 1.0f, 1.0f, 1.0f };
	float m_fishDetectionRadius = 0.0f;//青いバーの長さを基準に0.0f～1.0fの間で設定する。
	float m_fishDetectionRadiusPos = 0.0f;
	Vector3 m_fishDetectionRadiusUIPos = { 0.0f, 0.0f, 0.0f };

	SpriteRender m_fishDetectionRadiusUI;
	PlayFishing* m_playFishing=nullptr;
	TensionGauge* m_tensionGauge=nullptr;
};

