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

    // 100秒以下になった瞬間にアニメーション開始
    if (m_prevTime > 100 && m_time <= 100) {
        m_isAnimActive = true;
        m_animTime = 0.0f;
    }
    m_prevTime = m_time;

    // アニメーション処理
    float scale = 3.0f;
    if (m_isAnimActive) {
        // 1秒間バウンド（sinカーブで拡大縮小）
        const float animDuration = 1.0f;
        m_animTime += g_gameTime->GetFrameDeltaTime();
        float t = m_animTime / animDuration;
        if (t < 1.0f) {
            scale = 3.0f + 2.0f * sinf(t * 3.14159f); // 3.0→5.0→3.0
        } 
        else {
            m_isAnimActive = false;
        }
    }

    //表示するテキストを設定。
    m_timeFont.SetText(wcsbuf);
    //フォントの位置を設定。
    m_timeFont.SetPosition(Vector3(-800.0f, 500.0f, 0.0f));
    //フォントの大きさを設定。
    m_timeFont.SetScale(scale);
    // 残り時間が100秒以下なら赤色、それ以外は白色
    if (m_time <= 100) {
        m_timeFont.SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
    }
    else {
        m_timeFont.SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
    }
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
