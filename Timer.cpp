#include "DXUT.h"
#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::SetTimer(float time, int loopCount, function<void()> func, bool loop)
{
	m_time = time;
	m_loopCount = loopCount;
	m_func = func;

	is_start = false;

	SCENE->m_timers.push_back(this);
}

void Timer::TimerStart()
{
	is_start = true;
}

void Timer::Update()
{
	if (!is_start) return;

	startTime += DELTA;

	if (startTime >= m_time)
	{
		m_func();
		if (m_loopCount > 1 || m_loop)
		{
			m_loopCount--;
			startTime = 0;
		}
		else is_end = true;
	}

}

void Timer::Release()
{
	delete this;
}
