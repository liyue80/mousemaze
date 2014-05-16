/*
 */

#ifndef _PERFORMANCE_H_
#define _PERFORMANCE_H_

#include "Common.h"

typedef struct GPerformance_t
{
    u64 start;
    u64 summary;
    char name[64];
} GPerformance;

#ifdef PERFORMANCE_TEST
#define GPerformance_Resume(_this_)  pf_resume(_this_)
#define GPerformance_Pause(_this_)   pf_pause(_this_)
#define GPerformance_Output(_this_)  pf_output(_this_)
#else
#define GPerformance_Resume(_this_)
#define GPerformance_Pause(_this_)
#define GPerformance_Output(_this_)
#endif

void pf_resume(GPerformance *);
void pf_pause(GPerformance *);
void pf_output(GPerformance *);

#endif

