#pragma once
class Timer:public IGameObject
{
public:
	void Update();

	void TimerStart();

	void TimerStop();

	float GetElapsedSeconds() const;

private:
	float m_time=0.0f;
	bool m_isTimerRunning = false;
};

