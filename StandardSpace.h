/*
 *
 */
#ifndef _STANDARD_SPACE_H_
#define _STANDARD_SPACE_H_

#include "Common.h"

typedef struct GStandardSpace_t
{
    u32 distanceMap[HEIGHT][WIDTH];
} GStandardSpace;

void GStandardSpace_Initialize(GStandardSpace * This);

/*
 * 功能：  在位置(x,y)设置其距离入口的距离（步数）。
 * 返回值：如果这个位置已经被设置了更小的距离，不做修改，返回false。
 */
bool GStandardSpace_SetDistance(GStandardSpace * This, u32 x, u32 y, u32 distance);

#endif
