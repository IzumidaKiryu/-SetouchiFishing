#include "stdafx.h"
#include "FishingRodHP.h"
#include "TensionGauge.h"
#include"PlayFishing.h"
#include"PositionSelection.h"
#include"SceneFightFish.h"
#include"FightFishState.h"
#include"BuffManager.h"


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
	CalculatePowerMultiplier();
	failure();//失敗したかどうか。
	m_previousFrameHP = m_Hp;

	//ゲージの色を更新。
	UpdateStaminaGaugeColor();
}

bool FishingRodHP::Start()
{
	m_fightFishState = FindGO<FightFishState>("fightFishState");
	m_positionSelection = FindGO<PositionSelection>("m_PositionSelection");
	m_buffManager= FindGO<BuffManager>("buffManager");
	m_playFishing = FindGO<PlayFishing>("playFishing");

	return true;
}

float FishingRodHP::CalculateRecoveryAmount()
{

	//今のスタミナの割合によって回復量を決める。
	float recoveryMultiplier=0.0f;
	recoveryMultiplier=std::pow((m_Hp / m_MaxHp),1.5)+0.5;

	return recoveryMultiplier;
}

void FishingRodHP::RecoverPower()
{
	//回転量を取得。
	float m_rotationPower = m_fightFishState->GetRotationPower();

	//コントローラーが回ってないときはHPを回復する。
	if (m_rotationPower <= 0.0f) {
		m_Hp += m_baseRecovery* CalculateRecoveryAmount()* (1 + m_buffManager->GetTotalStaminaRegenBuff());
	}
}

void FishingRodHP::SetFishingRodHP()
{


	if (m_fightFishState->m_fishFacing == Upward) {
		//魚の向きが上なら。
		//コントローラーを回した分だけ竿のHPが減る。
		m_Hp -= m_fightFishState->GetRotationPower() * 16000.0f*m_playFishing->GetFishData().escapeForce;
	}
	if (m_fightFishState->m_fishFacing == Downward) {
		//魚の向きが下なら。
		//コントローラーを回した分だけ竿のHP少しが減る。
		/*m_Hp += 0.1;*/
		m_Hp -= m_fightFishState->GetRotationPower() * 20.0f;
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
	m_RodHPGaugeInside.Init("Assets/modelData/landscape_gauge_inside.DDS", 510, 110);
	m_RodHPGaugeInside.SetPivot(Vector2(0.0f, 0.5f));
	m_RodHPGaugeInside.SetPosition(Vector3(-450.0f, -300.0f, 0.0f));
	m_RodHPGaugeInside.SetScale(Vector3{ 1.5f, 1.0f, 1.0f });
	m_RodHPGaugeInside.Update();

	m_RodHPGaugeOutside.Init("Assets/modelData/landscape_gauge_outer.DDS", 510, 110);
	m_RodHPGaugeOutside.SetPivot(Vector2(0.0f, 0.5f));
	m_RodHPGaugeOutside.SetPosition(Vector3(-450.0f, -300.0f, 0.0f));
	m_RodHPGaugeOutside.SetScale(Vector3{ 1.5f, 1.0f, 1.0f });
	m_RodHPGaugeOutside.Update();

	m_RodHPBar.Init("Assets/sprite/staminaGauge.DDS", 365.0f, 85);
	m_RodHPBar.SetPivot(Vector2(0.0f, 0.5f));
	m_RodHPBar.SetPosition(Vector3(-430.0f, -300.0f, 0.0f));
	m_RodHPBar.SetScale(Vector3{ 1.5f, 1.0f, 1.0f });
	m_RodHPBar.Update();

	m_stamina.Init("Assets/modelData/Stamina/stamina.DDS", 300.0f, 150);
	m_stamina.SetPivot(Vector2(0.0f, 0.0f));
	m_stamina.SetPosition(Vector3(-200.0f, -300.0f, 0.0f));
	m_stamina.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_stamina.Update();

	
	m_reelChanceUI.Init("Assets/modelData/PromptUI/ReelChance.DDS", 200.0f, 200);
	m_reelChanceUI.SetPivot(Vector2(0.0f, 0.0f));
	m_reelChanceUI.SetPosition(Vector3(430.0f, -100.0f, 0.0f));
	m_reelChanceUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_reelChanceUI.Update();

	
	m_rotateLStick.Init("Assets/modelData/PromptUI/RotateLStick.DDS", 200.0f, 200);
	m_rotateLStick.SetPivot(Vector2(0.0f, 0.0f));
	m_rotateLStick.SetPosition(Vector3(-800.0f, -400.0f, 0.0f));
	m_rotateLStick.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_rotateLStick.Update();

	
	m_playerIcon.Init("Assets/modelData/PlayerIcon/PlayerUI.DDS", 150.0f, 150);
	m_playerIcon.SetPivot(Vector2(0.0f, 0.0f));
	m_playerIcon.SetPosition(Vector3(0.0f, -300.0f, 0.0f));
	m_playerIcon.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_playerIcon.Update();

	m_playerIconFine.Init("Assets/modelData/PlayerIcon/PlayerUIFine.DDS", 150.0f, 150);
	m_playerIconFine.SetPivot(Vector2(0.0f, 0.0f));
	m_playerIconFine.SetPosition(Vector3(0.0f, -300.0f, 0.0f));
	m_playerIconFine.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_playerIconFine.Update();

	m_playerIconTired.Init("Assets/modelData/PlayerIcon/PlayerUITired.DDS", 150.0f, 150);
	m_playerIconTired.SetPivot(Vector2(0.0f, 0.0f));
	m_playerIconTired.SetPosition(Vector3(0.0f, -300.0f, 0.0f));
	m_playerIconTired.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_playerIconTired.Update();


}

void FishingRodHP::Render(RenderContext& rc)
{
	m_RodHPGaugeInside.Draw(rc);
	m_RodHPBar.Draw(rc);
	m_RodHPGaugeOutside.Draw(rc);
	m_stamina.Draw(rc);
	m_rotateLStick.Draw(rc);

	//魚が上を向いているときだけ、ReelChance!!と表示する。
	if (m_fightFishState->GetFishFacing() == Downward) {
		m_reelChanceUI.Draw(rc);
	}

	if (m_Hp / m_MaxHp<0.2) {
		m_playerIconTired.Draw(rc);
	}
	if (0.2<=m_Hp / m_MaxHp&& m_Hp / m_MaxHp<= 0.8) {
		m_playerIcon.Draw(rc);
	}
	if (m_Hp / m_MaxHp > 0.8) {
		m_playerIconFine.Draw(rc);
	}

}

void FishingRodHP::failure()
{
	if (m_Hp <= 0.0f) {
		/*m_playFishing = FindGO<PlayFishing>("playFishing");
		m_playFishing->SetFailure();*/
	}
}

void FishingRodHP::SetIs_playFishingFinishedTrue()
{
	m_is_playFishingFinished = true;
}

/// <summary>
/// プレイヤーのパワーに比例して引く力を変える。
/// </summary>
void FishingRodHP::CalculatePowerMultiplier()
{
	//値が増えるスピードがなだらかすぎず速すぎない
	//この式を描かづにするとHPマックスの時と、HP半分の時で差が大きい（２倍）。
	//0.6乗することで、急に増える量が大きくなったり（X^2）、
	// 途中であまり増えなくなった(ln(x))りせずにちょうどいい値を返してくれる。
	m_powerMultiplier = pow((m_Hp / m_MaxHp),0.4);
	//0倍から15倍の範囲にする。
	m_powerMultiplier *= 15;
}



/// <summary>
/// HPの割合に比例して魚が引く力を変える。
/// </summary>
/// <returns></returns>
float FishingRodHP::GetPowerMultiplier()
{
	return m_powerMultiplier;
}

void FishingRodHP::UpdateStaminaGaugeColor()
{
	if ((m_Hp / m_MaxHp) > 0.5) {
		float t = (m_Hp / m_MaxHp) - 0.5f;
		staminaGaugeColor.Lerp(t, m_midStaminaGaugeColor,m_highStaminaGaugeColor);
	}
	else {
		float t = (m_Hp / m_MaxHp) / 0.5f;
		staminaGaugeColor.Lerp(t,m_lowStaminaGaugeColor, m_midStaminaGaugeColor);
	}
	m_RodHPBar.SetMulColor(staminaGaugeColor);
}
