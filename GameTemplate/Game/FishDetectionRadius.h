#pragma once
class PlayFishing;
class TensionGauge;
class FishDetectionRadius:public IGameObject
{
public:
	float t = 0.0f;
	FishDetectionRadius();
	~FishDetectionRadius();
	void Update();
	void SetFishDetectionRadius();
	void Render(RenderContext& rc);
	//void SetFishDetectionRadiusPosition(Vector3 position);
	//Vector3 GetFishDetectionRadiusPosition();
	//float GetFishDetectionRadius();
	//void SetFishDetectionRadiusScale(Vector3 scale);

	//void SetFishDetectionRadiusRotation(Vector3 rotation);

	void SetFishDetectionRadiusUIScale();


	void SetFishDetectionRadiusUIPosition();
	Vector3 m_uiScale = { 1.0f, 1.0f, 1.0f };
	float m_fishDetectionRadius = 0.0f;//青いバーの長さを基準に0.0f～1.0fの間で設定する。
	Vector3 m_fishDetectionRadiusUIPosition = { 0.0f, 0.0f, 0.0f };

	SpriteRender m_fishDetectionRadiusUI;
	PlayFishing* m_playFishing;
	TensionGauge* m_tensionGauge;
};

