#pragma once
class TensionGauge;
class PlayFishing;
class PositionSelection;
class SceneFightFish;
class FightFishState;
class BuffManager;

class FishingRodHP :public IGameObject
{
public:


	FishingRodHP();
	~FishingRodHP();

	void Update();
	bool Start();
	float CalculateRecoveryAmount();
	void RecoverPower();
	void SetFishingRodHP();
	void SetUI();
	void Render(RenderContext& rc);
	void failure();//失敗。
	void SetIs_playFishingFinishedTrue();


	void CalculatePowerMultiplier();
	float GetPowerMultiplier();


	float m_MaxHp = 200.0f;//HPの上限。
	float m_Hp = m_MaxHp;//釣り竿のHP。
	float m_baseRecovery=1.0f;
	float m_previousFrameHP = 0.0f;//前のフレームでのHP。
	float test;
	bool m_is_playFishingFinished = false;
	float m_powerMultiplier;//HPの割合に比例して魚が引く力を変える。

	SpriteRender m_RodHPGaugeInside;
	SpriteRender m_RodHPGaugeOutside;
	SpriteRender m_RodHPBar;
	SpriteRender m_stamina;

	SpriteRender m_reelChanceUI;
	SpriteRender m_rotateLStick;

	SpriteRender m_playerIcon;
	SpriteRender m_playerIconFine;
	SpriteRender m_playerIconTired;


	PlayFishing* m_playFishing;
	TensionGauge* m_tensionGauge;
	PositionSelection* m_positionSelection;
	FightFishState* m_fightFishState;
	BuffManager* m_buffManager;
};

