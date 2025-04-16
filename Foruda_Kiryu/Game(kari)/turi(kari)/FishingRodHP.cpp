#include "stdafx.h"
#include "FishingRodHP.h"
#include "TensionGauge.h"
#include"PlayFishing.h"
#include"PositionSelection.h"


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
		float a = m_tensionGauge->GetRotationPower();
		m_RodHPBar.SetScale(Vector3{ m_Hp* 2/m_MaxHp, 1.0f, 1.0f });
		m_RodHPBar.Update();
	/*}*/

	failure();//���s�������ǂ����B

	m_previousFrameHP = m_Hp;
}

void FishingRodHP::SetFishingRodHP()
{
	m_tensionGauge = FindGO<TensionGauge>("tensionGauge");

	
	if (m_tensionGauge->m_isFishDirectionisLeft==true) {
		//���̌��������Ȃ�B
		//�R���g���[���[���񂵂��������Ƃ�HP������B
		m_Hp -= m_tensionGauge->GetRotationPower() * 100.0f;
	}
	if (m_tensionGauge->m_isFishDirectionisLeft == false) {
		//���̌��������Ȃ�B
		//�R���g���[���[���񂵂��������Ƃ�HP������B
		m_Hp +=0.1 ;
	}


	float a = m_tensionGauge->GetRotationPower();
	//�R���g���[���[������ĂȂ��Ƃ���HP���񕜂���B
	if (a<= 0.0000f) {
		m_Hp += 0.5;
	}


	//HP��MAX�𒴂��Ă�����AMAX�̒l�ɂ���B
	if (m_Hp > m_MaxHp) {
		m_Hp = m_MaxHp;
	}
}

void FishingRodHP::SetUI()
{
	m_RodHPGaugeInside.Init("Assets/modelData/castGauge_inside.DDS", 500, 100);
	m_RodHPGaugeInside.SetPivot(Vector2(0.0f, 0.5f));
	m_RodHPGaugeInside.SetPosition(Vector3(-300.0f, -300.0f, 0.0f));
	m_RodHPGaugeInside.SetScale(Vector3{ 2.0f, 1.0f, 1.0f });
	m_RodHPGaugeInside.Update();

	m_RodHPGaugeOutside.Init("Assets / modelData / tensionGaugeFrame.DDS", 500, 100);
	m_RodHPGaugeOutside.SetPivot(Vector2(0.5f, 0.5f));
	m_RodHPGaugeOutside.SetPosition(Vector3(-300.0f, -300.0f, 0.0f));
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
		m_RodHPGaugeOutside.Draw(rc);
		m_RodHPBar.Draw(rc);
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
	m_positionSelection = NewGO<PositionSelection>(0, "m_PositionSelection");
	m_positionSelection->m_stealPositionPoint += m_Hp;
}
