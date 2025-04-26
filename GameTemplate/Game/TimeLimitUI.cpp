#include "stdafx.h"
#include "TimeLimitUI.h"

TimeLimitUI::TimeLimitUI()
{
	m_clockUI.Init("Assets/modelData/timelimit_clock.DDS", 60, 100);
	m_clockUI.SetPivot(Vector2(0.5f, 0.5f));
	m_clockUI.SetPosition(m_clockUIPos);
	m_clockUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_clockUI.Update();



	m_hundredsPlaceUI.SetPivot(Vector2(0.5f, 0.5f));
	m_hundredsPlaceUI.SetPosition(m_hundredsPlaceUIPos);
	m_hundredsPlaceUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_hundredsPlaceUI.Update();
}

TimeLimitUI::~TimeLimitUI()
{
}

void TimeLimitUI::DisplayTimeLimitUI(int time)
{
	if (time != m_prevTime) {//時間が変わった時だけ処理をする。

		SetTime(time);//時間をメンバ変数に設定する

		SetOnesPlace();//1の位を設定する。
		SetTensPlace();//10の位を設定する
		SetHundredsPlace();//100の位を設定する。

		SetOnesPlaceUI();//1の位のUIを設定する。
		SetTensPlaceUI();//10の位のUIを設定する。
		SetHundredsPlaceUI();//100の位のUIを設定する。

		/*m_hundredsPlaceUI.Update();*/
		m_prevTime = m_time;

	}
}

void TimeLimitUI::SetTime(int time)
{
	m_time = time;
}

void TimeLimitUI::SetOnesPlace()
{
	m_onesPlace = m_time % 10;
}

void TimeLimitUI::SetTensPlace()
{
	m_tensPlace = m_time / 10;
	m_tensPlace %= 10;
}

void TimeLimitUI::SetHundredsPlace()
{
	m_hundredsPlace = m_time / 100;
}

void TimeLimitUI::SetOnesPlaceUI()
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
		m_onesPlaceUI.Init("Assets/modelData/timelimit_zero.DDS", 100, 100);
		break;
	case 8:
		m_onesPlaceUI.Init("Assets/modelData/timelimit_zero.DDS", 100, 100);
		break;
	case 9:
		m_onesPlaceUI.Init("Assets/modelData/timelimit_zero.DDS", 100, 100);
		break;
	default:
		break;
	}
	m_onesPlaceUI.SetPivot(Vector2(0.5f, 0.5f));
	m_onesPlaceUI.SetPosition(m_onesPlaceUIPos);
	m_onesPlaceUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_onesPlaceUI.Update();

}

void TimeLimitUI::SetTensPlaceUI()
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

void TimeLimitUI::SetHundredsPlaceUI()
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

SpriteRender& TimeLimitUI::GetClockUI()
{
	return m_clockUI;
}

SpriteRender& TimeLimitUI::GetOnesPlacUI()
{
	return m_onesPlaceUI;
}

SpriteRender& TimeLimitUI::GetTensPlacUI()
{
	return m_tensPlaceUI;
}

SpriteRender& TimeLimitUI::GetHundredsPlacUI()
{
	return m_hundredsPlaceUI;
}
