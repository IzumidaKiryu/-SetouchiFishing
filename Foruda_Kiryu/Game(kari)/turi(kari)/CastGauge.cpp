#include "stdafx.h"
#include "CastGauge.h"
#include "GaugeCastSuccessful.h"
#include "TensionGauge.h"
#include "FishingGauge.h"
#include "PositionSelection.h"
#include "PlayFishing.h"

CastGauge::CastGauge()
{
	m_castGaugeOutside.Init("Assets/modelData/castGauge_Outside.DDS", 100, 500);
	m_castGaugeOutside.SetPivot(Vector2(0.0f, 0.5f));
	m_castGaugeOutside.SetPosition(Vector3(500.0f, 0.0f, 0.0f));
	m_castGaugeOutside.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_castGaugeOutside.Update();

	m_castGaugeInside.Init("Assets/modelData/castGauge_inside.DDS", 100, 500);
	m_castGaugeInside.SetPivot(Vector2(0.0f, 0.5f));
	m_castGaugeInside.SetPosition(Vector3(500.0f, 0.0f, 0.0f));
	m_castGaugeInside.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_castGaugeInside.Update();

	m_castGaugeArrow.Init("Assets/modelData/castGauge_arrow.DDS", 110, 10);
	m_castGaugeArrow.SetPivot(Vector2(0.0f, 0.5f));
	m_castGaugeArrow.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });

	m_gaugeCastSuccessful = NewGO<GaugeCastSuccessful>(0, "gaugeCastSuccessful");
	m_gaugeCastSuccessful->Init(10.0f, 10.0f);

	m_positionSelection = FindGO<PositionSelection>("positionSelection");

}

CastGauge::~CastGauge()
{

}

void CastGauge::Update()
{
	SetGaugeSpead();
	UpAndDownManagement();//���̓������������߂�B
	SetArrowPosition();//���̏ꏊ�����߂�B
	m_castGaugeArrow.Update();//���̕`����X�V����B
	HitTest();
}

/// <summary>
/// ���̏ꏊ��ݒ�
/// </summary>
void CastGauge::SetArrowPosition()
{
	m_castGaugeArrow.SetPosition(Vector3(490.0f, m_arrowPosition, 0.0f));
}

/// <summary>
/// ������ɓ����������ɓ����������߂�B
/// </summary>
void CastGauge::UpAndDownManagement()
{
	if (upState == false) {
		DownwardOperation();
	}
	if (upState == true) {
		UpwardOperation();
	}
}
/// <summary>
/// ������Ɉړ��B
/// </summary>
void CastGauge::UpwardOperation()
{
	m_arrowPosition += m_gaugeSpead;
	if (m_arrowPosition >= m_gaugeUpperLimit) {
		m_arrowPosition = (-m_arrowPosition + m_gaugeUpperLimit) + m_gaugeUpperLimit;//�����ʂ�߂����炻�̕��߂鏈���B
		upState = false;
	}
}

/// <summary>
/// �������Ɉړ�
/// </summary>
void CastGauge::DownwardOperation()
{
	m_arrowPosition -= m_gaugeSpead;
	if (m_arrowPosition <= m_gaugeLowerLimit) {
		m_arrowPosition = (-m_arrowPosition + m_gaugeLowerLimit) + m_gaugeLowerLimit;//������ʂ�߂����炻�̕��߂鏈���B
		upState = true;
	}
}

/// <summary>
/// ���̃X�s�[�h��ݒ�
/// </summary>
void CastGauge::SetGaugeSpead()
{
	m_gaugeSpead = /*(237.0f*2.0f)/10*/5;
}

/// <summary>
/// �����蔻����m���߂�
/// </summary>
void CastGauge::HitTest()
{
	if (g_pad[0]->IsTrigger(enButtonA)) {
		if (m_gaugeCastSuccessful->hitTest(m_arrowPosition) == true)//����������B
		{
			m_fishingGauge=NewGO<FishingGauge>(0, "fishingGauge ");
			/*tensionGauge = NewGO<TensionGauge>(0, "tensionGauge");*/
			DeleteGO(this);
		}
		else if (m_gaugeCastSuccessful->hitTest(m_arrowPosition) == false) //���s������B
		{
			m_playFishing = FindGO<PlayFishing>("playFishing");
			m_playFishing->DeleteThisClass();
		}
	}
}

void CastGauge::Render(RenderContext& rc)
{
	m_castGaugeInside.Draw(rc);
	m_gaugeCastSuccessful->m_gaugeCastSuccessfulSprite.Draw(rc);
	m_castGaugeArrow.Draw(rc);
	m_castGaugeOutside.Draw(rc);
}
