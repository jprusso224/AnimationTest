#ifndef GAMETIMER_H
#define GAMETIMER_H

#include "GameTypes.h"

class GameTimer
{
public:
    GameTimer();
    virtual ~GameTimer(){}

    void start(const quint64 timeToWait_ms);

    void update(const quint64 elapsedTime_ms);

    bool isExpired() const;

private:

    quint64 m_timeToWait;
    quint64 m_runningTime;

};
#endif // GAMETIMER_H
