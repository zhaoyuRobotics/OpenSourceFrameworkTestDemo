#ifndef PRECISETIMER_H
#define PRECISETIMER_H

#include <time.h>
#include <stdint.h>


class PreciseTimer
{
public:
    PreciseTimer();

    //设置超时间隔（微秒为单位）
    void setInterval(int interval_us);

    //标记开始时间点
    void markStartTime();

    void markStartTime(int interval_us);

    //等待下一个时间点:根据上一个时间点和超时间隔 计算得到等待的时间点
    int  waitTimeout();

    //等待固定时间: 从当前时间点算起(单位为微秒)
    static int  delay(uint32_t interval_us);

    //计算时间差(单位为微秒)
    static int64_t timeDifference(struct timespec &bigTimePoint, struct timespec &smallTimePoint);

private:
    static void timespecNormalize(struct timespec &ts);

private:
    long   m_interval;    //ns

    struct timespec m_nextTimePoint;
};

#endif // PRECISETIMER_H
