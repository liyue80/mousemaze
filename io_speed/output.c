#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

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
    char buf[2000];
    int n;
    ulonglong a,b;

    
    gets(buf);
    memcpy(&buf[900], buf, 900);
    buf[1800] = 0;

    a = read_counter();
#if defined(_PRINTF)
    printf("%s", buf);
#elif defined(_PUTS)
    puts(buf);
#elif defined(_WRITE)
    write(1, buf, 1800);
#endif
    b = read_counter();
    
    fprintf(stderr, "interval %llu\n", b - a);

	return 0;
}
