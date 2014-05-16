/*
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "Common.h"
#include "Performance.h"

#if defined(PERFORMANCE_TEST)
extern GPerformance pfMalloc;
#endif

void * mem_alloc(u32 size)
{
	void * p;

	GPerformance_Resume(&pfMalloc);

	p = malloc(size);

    GPerformance_Pause(&pfMalloc);

	return p;
}

void mem_free(void *ptr)
{
	free(ptr);
}
