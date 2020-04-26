#include <iostream>
#include <precisetimer.h>
#include <sys/time.h>
#include  <stdio.h>
#include  <unistd.h>
#include  <pthread.h>

using namespace std;

// 进程绑定cpu: sched_setaffinity
// 线程绑定cpu: pthread_setaffinity_np
// 设置优先级:  sched_setscheduler


// 测试用
int set_cpu(int cpuno)
{
    int max_cpus = sysconf(_SC_NPROCESSORS_ONLN);
    printf("%d\n",max_cpus);
    pthread_t tid;
    cpu_set_t mask;
    if(cpuno >=0 && cpuno < max_cpus)
    {
        CPU_ZERO(&mask);
        CPU_SET(cpuno, &mask);
        tid = pthread_self();
        if(pthread_setaffinity_np(tid, sizeof(mask), &mask) == -1)
        {
            printf("Could not set CPU affinity to CPU #%d\n", cpuno);
            return -1;
        }
        return 0;
    }
    return -1;
}



// 测试用
int set_priority(int prio)
{
    struct sched_param param;
    param.sched_priority = prio;

    return sched_setscheduler(0, SCHED_FIFO, &param);
}




static double MaxValue(double m_dest,double m_src)
{
    if(m_dest > m_src){
        return m_dest;
    } else{
        return m_src;
    }
}


void *testTimer(void *args)
{
    set_cpu(2);

    struct timeval tv_start;
    struct timeval tv_end;
    double tv_diff = 0.;
    double tv_Max = 0.;
    int    all_cnt = 0;
    int    timeout_cnt = 0;

    PreciseTimer m_timeTest;

    gettimeofday(&tv_start,NULL);
    gettimeofday(&tv_end,NULL);

    while(1)
    {
        gettimeofday(&tv_start,NULL);

        m_timeTest.delay(5000);

        gettimeofday(&tv_end,NULL);

        tv_diff = (double)(tv_end.tv_sec*1000000 + tv_end.tv_usec) - (double)(tv_start.tv_sec*1000000 + tv_start.tv_usec);
        tv_Max = MaxValue(tv_Max,tv_diff);

        printf("\033[31;42m  本次延时时间:%lf\033[0m,  最大延时时间:%lf   总体次数:%d ，超时次数:%d\n",tv_diff,tv_Max,all_cnt,timeout_cnt);

        if(tv_diff > 6000)
        {
            timeout_cnt++;
        }
        all_cnt++;

    }
}

int main(int argc, char *argv[])
{
//    /* NOTE: All processes execute code from here down! */
//    cpu_set_t mask;
//    /* CPU_ZERO initializes all the bits in the mask to zero. */
//    CPU_ZERO( &mask );
//    /* CPU_SET sets only the bit corresponding to cpu. */
//    CPU_SET(1, &mask );
//    /* sched_setaffinity returns 0 in success */
//    if( sched_setaffinity( 0, sizeof(mask), &mask ) == -1 ){
//        cout << "WARNING: Could not set CPU Affinity, continuing..." << endl;
//    }
//    set_priority(80);




    pthread_t threadId;
    if(0 != pthread_create(&threadId,NULL,testTimer,NULL))
    {
        printf("创建线程失败\n");
    }

    pthread_join(threadId,NULL);


   return 0;
}
