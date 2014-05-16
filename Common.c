/*
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Common.h"
#include "Performance.h"

#if defined(PERFORMANCE_TEST)
extern GPerformance pfMem;
#endif

void mem_cpy(void *d, const void *s, u32 n)
{
	pf_resume(&pfMem);
	memcpy(d, s, n);
    pf_pause(&pfMem);
}
