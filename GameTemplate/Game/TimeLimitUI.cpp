#include "stdafx.h"
#include "TimeLimitUI.h"

TimeLimitUI::TimeLimitUI()
{


}

TimeLimitUI::~TimeLimitUI()
{
}

bool TimeLimitUI::Init()
{
	return true;
}

bool TimeLimitUI::Start()
{
	return true;
}

void TimeLimitUI::Update()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%d", int(m_time));

	//表示するテキストを設定。
	m_timeFont.SetText(wcsbuf);
	//フォントの位置を設定。
	m_timeFont.SetPosition(Vector3(-800.0f, 500.0f, 0.0f));
	//フォントの大きさを設定。
	m_timeFont.SetScale(3.0f);
	//フォントの色を設定。
	m_timeFont.SetColor({ 0.0f,0.0f,0.0f,1.0f });
}
void TimeLimitUI::SetTime(int time)
{
	if (time > 0) {
		m_time = time;
	}
	else {
		time = 0;
	}
}

FontRender& TimeLimitUI::GetTimeFont()
{
	return m_timeFont;
}
