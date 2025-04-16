#include "stdafx.h"
#include "ScoreDisplay.h"
#include"PlayFishing.h"
#include"PositionSelection.h"

ScoreDisplay::ScoreDisplay()
{
	m_playFishing=FindGO<PlayFishing>("playFishing");
	m_score=m_playFishing->GetFIshScore();

	//1スコアのそれぞれの桁を求める。
	SetOnesPlace();
	SetTensPlace();
	SetHundredsPlace();

	//それぞれの桁のUIを設定する。
	SetOnesPlaceUI();
	SetTensPlaceUI();
	SetHundredsPlaceUI();

}

ScoreDisplay::~ScoreDisplay()
{
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_positionSelection->SetisDisplayingTrue();
	//ポジションセレクトクラスのオブジェクトをアクティブにする
	m_positionSelection->SetActivate();
}

void ScoreDisplay::Update()
{
	SetOnesPlace();
	if (g_pad[0]->IsTrigger(enButtonA)) {
		DeleteGO(this);
	}
}

void ScoreDisplay::SetScore()
{
	
}

void ScoreDisplay::SetOnesPlace()
{
	m_onesPlace= m_score%10;
}

void ScoreDisplay::SetTensPlace()
{
	m_tensPlace = m_score / 10;
	m_tensPlace %= 10;
	
}

void ScoreDisplay::SetHundredsPlace()
{
	m_hundredsPlace = m_score / 100;
	m_hundredsPlace %= 10;
}

void ScoreDisplay::SetOnesPlaceUI()
{
	switch (m_onesPlace)
	{
	case 0:
		m_onesPlaceUI.Init("Assets/modelData/timelimit_zero.DDS", 100, 100);
		break;
	case 1:
		m_onesPlaceUI.Init("Assets/modelData/timelimit_one.DDS", 100, 100);
		break;
	case 2:
		m_onesPlaceUI.Init("Assets/modelData/timelimit_two.DDS", 100, 100);
		break;
	case 3:
		m_onesPlaceUI.Init("Assets/modelData/timelimit_three.DDS", 100, 100);
		break;
	case 4:
		m_onesPlaceUI.Init("Assets/modelData/timelimit_four.DDS", 100, 100);
		break;
	case 5:
		m_onesPlaceUI.Init("Assets/modelData/timelimit_five.DDS", 100, 100);
		break;
	case 6:
		m_onesPlaceUI.Init("Assets/modelData/timelimit_six.DDS", 100, 100);
		break;
	case 7:
		m_onesPlaceUI.Init("Assets/modelData/timelimit_seven.DDS", 100, 100);
		break;
	case 8:
		m_onesPlaceUI.Init("Assets/modelData/timelimit_eight.DDS", 100, 100);
		break;
	case 9:
		m_onesPlaceUI.Init("Assets/modelData/timelimit_nine.DDS", 100, 100);
		break;
	default:
		break;
	}
	m_onesPlaceUI.SetPivot(Vector2(0.5f, 0.5f));
	m_onesPlaceUI.SetPosition(m_onesPlaceUIPos);
	m_onesPlaceUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_onesPlaceUI.Update();
}

void ScoreDisplay::SetTensPlaceUI()
{
	switch (m_tensPlace)
	{
	case 0:
		m_tensPlaceUI.Init("Assets/modelData/timelimit_zero.DDS", 100, 100);
		break;
	case 1:
		m_tensPlaceUI.Init("Assets/modelData/timelimit_one.DDS", 100, 100);
		break;
	case 2:
		m_tensPlaceUI.Init("Assets/modelData/timelimit_two.DDS", 100, 100);
		break;
	case 3:
		m_tensPlaceUI.Init("Assets/modelData/timelimit_three.DDS", 100, 100);
		break;
	case 4:
		m_tensPlaceUI.Init("Assets/modelData/timelimit_four.DDS", 100, 100);
		break;
	case 5:
		m_tensPlaceUI.Init("Assets/modelData/timelimit_five.DDS", 100, 100);
		break;
	case 6:
		m_tensPlaceUI.Init("Assets/modelData/timelimit_six.DDS", 100, 100);
		break;
	case 7:
		m_tensPlaceUI.Init("Assets/modelData/timelimit_seven.DDS", 100, 100);
		break;
	case 8:
		m_tensPlaceUI.Init("Assets/modelData/timelimit_eight.DDS", 100, 100);
		break;
	case 9:
		m_tensPlaceUI.Init("Assets/modelData/timelimit_nine.DDS", 100, 100);
		break;
	default:
		break;
	}
	m_tensPlaceUI.SetPivot(Vector2(0.5f, 0.5f));
	m_tensPlaceUI.SetPosition(m_tensPlaceUIPos);
	m_tensPlaceUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_tensPlaceUI.Update();
}

void ScoreDisplay::SetHundredsPlaceUI()
{
	switch (m_hundredsPlace)
	{
	case 0:
		m_hundredsPlaceUI.Init("Assets/modelData/timelimit_zero.DDS", 100, 100);
		break;
	case 1:
		m_hundredsPlaceUI.Init("Assets/modelData/timelimit_one.DDS", 100, 100);
		break;
	case 2:
		m_hundredsPlaceUI.Init("Assets/modelData/timelimit_two.DDS", 100, 100);
		break;
	case 3:
		m_hundredsPlaceUI.Init("Assets/modelData/timelimit_three.DDS", 100, 100);
		break;
	case 4:
		m_hundredsPlaceUI.Init("Assets/modelData/timelimit_four.DDS", 100, 100);
		break;
	case 5:
		m_hundredsPlaceUI.Init("Assets/modelData/timelimit_five.DDS", 100, 100);
		break;
	case 6:
		m_hundredsPlaceUI.Init("Assets/modelData/timelimit_six.DDS", 100, 100);
		break;
	case 7:
		m_hundredsPlaceUI.Init("Assets/modelData/timelimit_seven.DDS", 100, 100);
		break;
	case 8:
		m_hundredsPlaceUI.Init("Assets/modelData/timelimit_eight.DDS", 100, 100);
		break;
	case 9:
		m_hundredsPlaceUI.Init("Assets/modelData/timelimit_nine.DDS", 100, 100);
		break;
	default:
		break;
	}
	m_hundredsPlaceUI.SetPivot(Vector2(0.5f, 0.5f));
	m_hundredsPlaceUI.SetPosition(m_hundredsPlaceUIPos);
	m_hundredsPlaceUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_hundredsPlaceUI.Update();
}

void ScoreDisplay::ScoreUI()
{

}

void ScoreDisplay::Render(RenderContext& rc)
{
	m_onesPlaceUI.Draw(rc);
	m_tensPlaceUI.Draw(rc);
	m_hundredsPlaceUI.Draw(rc);

}
