/*
*/
#include <stdio.h>
#ifdef _MSC_VER
#include <windows.h>
#endif
#include "Performance.h"

static __inline u64 read_counter()
{
    u64 ts;
#if defined(_MSC_VER)
    QueryPerformanceCounter((LARGE_INTEGER*)&ts);
#else
    u32 ts1, ts2;
    __asm__ __volatile__("rdtsc\n\t":"=a"(ts1), "=d"(ts2));
    ts = ((u64) ts2 << 32) | ((u64) ts1);
#endif
    return ts;
}

void pf_resume(GPerformance * This)
{
    This->start = read_counter();
}

void pf_pause(GPerformance * This)
{
    This->summary += (read_counter() - This->start);
}

void pf_output(GPerformance * This)
{
    printf("performance counter \"%s\" result : %llu\n", This->name, This->summary);
}
