#pragma once
class TensionGauge;
class PlayFishing;

class FishingRodHP:public IGameObject
{
public:


	FishingRodHP();
	~FishingRodHP();

	void Update();
	void SetFishingRodHP();
	void SetUI();
	void Render(RenderContext& rc);
	void failure();//失敗。

	float m_MaxHp = 200.0f;//HPの上限。
	float m_Hp = m_MaxHp;//釣り竿のHP。
	float m_previousFrameHP = 0.0f;//前のフレームでのHP。
	float test;

	SpriteRender m_RodHPGaugeInside;
	SpriteRender m_RodHPGaugeOutside;
	SpriteRender m_RodHPBar;

	PlayFishing* m_playFishing;
	TensionGauge* m_tensionGauge;
};

