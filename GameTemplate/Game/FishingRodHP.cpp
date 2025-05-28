#include "stdafx.h"
#include "FishingRodHP.h"
#include "TensionGauge.h"
#include"PlayFishing.h"
#include"PositionSelection.h"
#include"SceneFightFish.h"
#include"FightFishState.h"


FishingRodHP::FishingRodHP()
{
	SetUI();
}

FishingRodHP::~FishingRodHP()
{
}

void FishingRodHP::Update()
{
	SetFishingRodHP();
	/*if (m_previousFrameHP != m_Hp) {*/
	float m_rotationPower = m_fightFishState->GetRotationPower();
	m_RodHPBar.SetScale(Vector3{ m_Hp * 2 / m_MaxHp, 1.0f, 1.0f });
	m_RodHPBar.Update();
	/*}*/
	SetPullPowerBuff();
	failure();//失敗したかどうか。
	m_previousFrameHP = m_Hp;
}

float FishingRodHP::CalculateRecoveryAmount()
{

	//今のスタミナの割合によって回復量を決める。
	float recoveryMultiplier;
	recoveryMultiplier=std::pow((m_Hp / m_MaxHp),1.5);

	return recoveryMultiplier;
}

void FishingRodHP::RecoverPower()
{
	//回転量を取得。
	float m_rotationPower = m_fightFishState->GetRotationPower();

	//コントローラーが回ってないときはHPを回復する。
	if (m_rotationPower <= 0.0f) {
		m_Hp += m_baseRecovery* CalculateRecoveryAmount();
	}
}

void FishingRodHP::SetFishingRodHP()
{
	m_fightFishState = FindGO<FightFishState>("fightFishState");


	if (m_fightFishState->m_fishFacing == Upward) {
		//魚の向きが上なら。
		//コントローラーを回した分だけ竿のHPが減る。
		m_Hp -= m_fightFishState->GetRotationPower() * 100.0f;
	}
	if (m_fightFishState->m_fishFacing == Downward) {
		//魚の向きが下なら。
		//コントローラーを回した分だけ竿のHP少しが減る。
		/*m_Hp += 0.1;*/
		m_Hp -= m_fightFishState->GetRotationPower() * 10.0f;
	}

	if (m_Hp<0) {
		m_Hp = 0.0f;
	}


	float m_rotationPower = m_fightFishState->GetRotationPower();
	//回復。
	RecoverPower();


	//HPがMAXを超えていたら、MAXの値にする。
	if (m_Hp > m_MaxHp) {
		m_Hp = m_MaxHp;
	}
}

void FishingRodHP::SetUI()
{
	m_RodHPGaugeInside.Init("Assets/modelData/castGauge_inside.DDS", 500, 100);
	m_RodHPGaugeInside.SetPivot(Vector2(0.0f, 0.5f));
	m_RodHPGaugeInside.SetPosition(Vector3(-450.0f, -300.0f, 0.0f));
	m_RodHPGaugeInside.SetScale(Vector3{ 2.0f, 1.0f, 1.0f });
	m_RodHPGaugeInside.Update();

	m_RodHPGaugeOutside.Init("Assets/modelData/landscape_gauge_outer.DDS", 510, 110);
	m_RodHPGaugeOutside.SetPivot(Vector2(0.0f, 0.5f));
	m_RodHPGaugeOutside.SetPosition(Vector3(-470.0f, -300.0f, 0.0f));
	m_RodHPGaugeOutside.SetScale(Vector3{ 2.0f, 1.0f, 1.0f });
	m_RodHPGaugeOutside.Update();

	m_RodHPBar.Init("Assets/modelData/cast_successful.DDS", 500.0f, 100);
	m_RodHPBar.SetPivot(Vector2(0.0f, 0.5f));
	m_RodHPBar.SetPosition(Vector3(-450.0f, -300.0f, 0.0f));
	m_RodHPBar.SetScale(Vector3{ 2.0f, 1.0f, 1.0f });

}

void FishingRodHP::Render(RenderContext& rc)
{
	m_RodHPGaugeInside.Draw(rc);
	m_RodHPBar.Draw(rc);
	m_RodHPGaugeOutside.Draw(rc);
}

void FishingRodHP::failure()
{
	if (m_Hp <= 0.0f) {
		m_playFishing = FindGO<PlayFishing>("playFishing");
		m_playFishing->SetFailure();
	}
}

void FishingRodHP::SetIs_playFishingFinishedTrue()
{
	m_is_playFishingFinished = true;
}

void FishingRodHP::AddStealPositionPoint()
{
	/*m_positionSelection = NewGO<PositionSelection>(0, "m_PositionSelection");*/
	m_positionSelection = FindGO<PositionSelection>("m_PositionSelection");
	/*m_positionSelection->m_stealPositionPoint += m_Hp;*/
}

void FishingRodHP::SetPullPowerBuff()
{
	//1倍から6倍の範囲で魚を引く力を大きくする。
	m_pullPowerBuff = ((m_Hp / m_MaxHp)*6)+1;
}

float FishingRodHP::GetPullPowerBuff()
{
	return m_pullPowerBuff;
}
