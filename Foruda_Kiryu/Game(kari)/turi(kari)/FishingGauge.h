#pragma once
class TensionGauge;
class PlayFishing;
class FishingGauge : public IGameObject
{
public:
	FishingGauge();
	~FishingGauge();
	void Update();
	void SetBarPosition();//上下に動くバー
	void UpAndDownManagement();//バーの上下動作の管理。
	void UpwardOperation();
	void DownwardOperation();
	void SetBarSpead();
	void HitTest();
	float m_barPosition = -237.0f;//バーのポジション（初期設定は???）
	bool upState = true;//上がっているかのステート
	void Render(RenderContext& rc);
	float m_barUpperLimit = 237.0f;//バーの上限
	float m_barLowerLimit = -237.0f;//バーの下限
	float m_barSpead;//バーのスピード
	void Attack();
	float m_attack = 1;
	float m_hpMinimumDecreaseLimit = 1.0f;
	float m_hpMaxDecreseLimit =0.5f;

	SpriteRender m_fishingGauge;
	SpriteRender m_fishingGaugeFrame;
	SpriteRender m_fishingGaugeBar;
	TensionGauge* m_tensionGauge;
	PlayFishing* m_playFishing;

	
};



