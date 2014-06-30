#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ulonglong;
typedef unsigned long ulong;

static __inline ulonglong read_counter()
{
    ulonglong ts;
  #if defined(_MSC_VER)
    QueryPerformanceCounter((LARGE_INTEGER*)&ts);
  #else
    ulong ts1, ts2;
    __asm__ __volatile__("rdtsc\n\t":"=a"(ts1), "=d"(ts2));
    ts = ((ulonglong) ts2 << 32) | ((ulonglong) ts1);
  #endif
    return ts;
}

int main()
{
    char buf[1024];
    int n;
    ulonglong a,b;

    a = read_counter();
#if defined(_GETS)
    gets(buf);
#elif defined(_READ)
    while (read(0, buf, sizeof(buf))==-1);
#endif
    b = read_counter();
    
    fprintf(stderr, "interval %llu\n", b - a);
    printf("%s", buf);
	return 0;
}
