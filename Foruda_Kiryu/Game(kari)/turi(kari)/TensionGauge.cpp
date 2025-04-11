#include "stdafx.h"
#include "TensionGauge.h"
#include "GetRotation.h"
#include"PlayFishing.h"
#include <random>


TensionGauge::TensionGauge()
{
	srand(time(nullptr));
	//m_tensionGaugeInside.Init("Assets/modelData/tensionGauge.DDS", 500, 100);
	m_tensionGaugeInside.Init("Assets/modelData/Sea.DDS", 500, 100);
	m_tensionGaugeInside.SetPivot(Vector2(0.5f, 0.5f));
	m_tensionGaugeInside.SetPosition(Vector3(0.0f, -200.0f, 0.0f));
	m_tensionGaugeInside.SetScale(Vector3{ 2.0f, 1.0f, 1.0f });
	m_tensionGaugeInside.Update();

	m_tensionGaugeOutside.Init("Assets/modelData/tensionGaugeFrame.DDS", 500, 100);
	m_tensionGaugeOutside.SetPivot(Vector2(0.5f, 0.5f));
	m_tensionGaugeOutside.SetPosition(Vector3(0.0f, -200.0f, 0.0f));
	m_tensionGaugeOutside.SetScale(Vector3{ 2.0f, 1.0f, 1.0f });
	m_tensionGaugeOutside.Update();

	m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_Facing_left.DDS", 50, 50);
	m_signs_of_Fish.SetPivot(Vector2(0.5f, 0.5f));
	m_signs_of_Fish.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_getRotation = NewGO<GetRotation>(0, "getRotation");
}

TensionGauge::~TensionGauge()
{
}

void TensionGauge::Update()
{
	FishDirectionChange();
	SetFishEscapePower();
	SetSigns_of_Fish_Position();  
	Set_signs_of_Fish_UI();
	failure();//���������ғ���
	success();//���s�������ǂ����B
}

void TensionGauge::RightAndLeftManagement()
{

}

void TensionGauge::SetSigns_of_Fish_Position()
{
	//SetFishEscapePower();
	if (m_isFishDirectionisLeft == true) {//�������������Ă���Ƃ��͂܂��͂���������B(���������Ă���Ƃ��ɂ������͉E�Ɉ��������悤�ɂ��邽��)�B
		m_forcePullFish += m_getRotation->nowFrameRotationQuantity * 200*1.3;
	}
	else {
		m_forcePullFish += m_getRotation->nowFrameRotationQuantity* 200;
	}

		m_signs_of_Fish_Position = m_forcePullFish + m_fishEscapePower;
	m_signs_of_Fish.SetPosition(Vector3(m_signs_of_Fish_Position, -200.0f, 0.0f));
	m_signs_of_Fish.Update();
}

void TensionGauge::SetFishEscapePower()
{
	if (m_isFishDirectionisLeft == true) {
		m_fishEscapePower -= 2.0f;
	}

}

void TensionGauge::SetFishDirection()
{
	
	
}

/// <summary>
/// ���̌���������ύX���邽�߂̊֐��B
/// </summary>
void TensionGauge::FishDirectionChange()
{
	std::random_device rd;
	int randum = rd() % 50;
	if (randum == 0)//�[�����o�������������ς���B
	{
		switch (m_isFishDirectionisLeft)
		{

		case true:
			m_isFishDirectionisLeft = false;
			break;

		case false:
			m_isFishDirectionisLeft = true;
			break;

		default:
			break;
		}

	}
}

/// <summary>
/// ���s
/// </summary>
void TensionGauge::failure()
{
	if (m_signs_of_Fish_Position <= m_gaugeLeftmost) {
		m_playFishing = FindGO<PlayFishing>("playFishing");
		m_playFishing->SetFailure();
	}
}

void TensionGauge::success()
{
	if (m_signs_of_Fish_Position >= m_gaugeRightmost) {
		m_playFishing = FindGO<PlayFishing>("playFishing");
		m_playFishing->SetSuccess();
	}
}

float TensionGauge::GetRotationPower()
{
	return m_getRotation->nowFrameRotationQuantity;

}

void TensionGauge::Set_signs_of_Fish_UI()
{
	if (m_previous_isFishDirectionisLeft != m_isFishDirectionisLeft) {//�O�̃t���[���Ə�Ԃ��Ⴄ�������B
		switch (m_isFishDirectionisLeft)
		{

		case true:
			m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_Facing_left.DDS", 50, 50);
			break;

		case false:
			m_signs_of_Fish.Init("Assets/modelData/signs_of_fish_Facing_right.DDS", 50, 50);
			break;

		default:
			break;
		}
		m_signs_of_Fish.Update();
	}

	m_previous_isFishDirectionisLeft = m_isFishDirectionisLeft;
}


void TensionGauge::Render(RenderContext& rc)
{
	m_tensionGaugeInside.Draw(rc);
	m_tensionGaugeOutside.Draw(rc);
	m_signs_of_Fish.Draw(rc);
}
