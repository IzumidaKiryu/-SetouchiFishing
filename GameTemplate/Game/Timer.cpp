#include "stdafx.h"
#include "Timer.h"

void Timer::Update()
{
	if (m_isTimerRunning) {
		m_time += g_gameTime->GetFrameDeltaTime();
	}
}

void Timer::TimerStart()
{
	m_isTimerRunning = true;
}

void Timer::TimerStop()
{
	m_isTimerRunning = false;
}

float Timer::GetElapsedSeconds() const
{
	return m_time;
}
