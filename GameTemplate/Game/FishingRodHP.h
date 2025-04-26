#pragma once
class TensionGauge;
class PlayFishing;
class PositionSelection;
class SceneFightFish;

class FishingRodHP :public IGameObject
{
public:


	FishingRodHP();
	~FishingRodHP();

	void Update();
	void SetFishingRodHP();
	void SetUI();
	void Render(RenderContext& rc);
	void failure();//���s�B
	void SetIs_playFishingFinishedTrue();
	void AddStealPositionPoint();

	float m_MaxHp = 200.0f;//HP�̏���B
	float m_Hp = m_MaxHp;//�ނ�Ƃ�HP�B
	float m_previousFrameHP = 0.0f;//�O�̃t���[���ł�HP�B
	float test;
	bool m_is_playFishingFinished = false;

	SpriteRender m_RodHPGaugeInside;
	SpriteRender m_RodHPGaugeOutside;
	SpriteRender m_RodHPBar;

	PlayFishing* m_playFishing;
	TensionGauge* m_tensionGauge;
	PositionSelection* m_positionSelection;
	SceneFightFish* m_sceneFightFish;
};

