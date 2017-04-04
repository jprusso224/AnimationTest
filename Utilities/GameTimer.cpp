#include "GameTimer.h"

GameTimer::GameTimer()
{

}

void GameTimer::start(const quint64 timeToWait_ms)
{
    m_runningTime = 0;
    m_timeToWait = timeToWait_ms;
}

void GameTimer::update(const quint64 elapsedTime_ms)
{
    m_runningTime += elapsedTime_ms;
}

bool GameTimer::isExpired() const
{
    return (m_runningTime > m_timeToWait);
}
