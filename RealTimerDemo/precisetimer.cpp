#include "precisetimer.h"

#define NSEC_PER_SEC    1000000000

PreciseTimer::PreciseTimer()
{
    m_interval = 0;

    clock_gettime(CLOCK_REALTIME, &m_nextTimePoint);
}

void PreciseTimer::setInterval(int interval_us)
{
    m_interval = interval_us*1000;
}

void PreciseTimer::markStartTime()
{
    clock_gettime(CLOCK_REALTIME, &m_nextTimePoint);
}

void PreciseTimer::markStartTime(int interval_us)
{
    m_interval = interval_us*1000;

    clock_gettime(CLOCK_REALTIME, &m_nextTimePoint);
}

int PreciseTimer::waitTimeout()
{
    //计算得到等待时间点
    m_nextTimePoint.tv_nsec += m_interval;
    timespecNormalize(m_nextTimePoint);

    //等待时间点到达
    return clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &m_nextTimePoint, NULL);
}

int PreciseTimer::delay(uint32_t interval_us)
{
    struct timespec timePoint;

    //当前时间点
    clock_gettime(CLOCK_REALTIME, &timePoint);

    //计算得到等待时间点
    timePoint.tv_nsec += interval_us * 1000;
    timespecNormalize(timePoint);

    //等待时间点到达
    return clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &timePoint, NULL);
}

int64_t PreciseTimer::timeDifference(timespec &bigTimePoint, timespec &smallTimePoint)
{
    int64_t diff;

    diff = 1000000*(int64_t)((int)bigTimePoint.tv_sec - (int)smallTimePoint.tv_sec);
    diff += ((int)bigTimePoint.tv_nsec-(int)smallTimePoint.tv_nsec)/1000;

    return diff;
}

void PreciseTimer::timespecNormalize(timespec &ts)
{
    while (ts.tv_nsec >= NSEC_PER_SEC)
    {
        ts.tv_nsec -= NSEC_PER_SEC;
        ts.tv_sec++;
    }
}
