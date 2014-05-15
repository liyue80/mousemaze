/*
 *
 */
#ifndef _PARALLEL_SPACE_H_
#define _PARALLEL_SPACE_H_

#include "common.h"
#include "StandardSpace.h"

typedef struct GParallelSpace_t
{
    // Following members are private.
	GStandardSpace * standardSpace;
    Position currentPos;
	u32 distance;  // 已经移动的步数
    u8 * roadmap;
	u8 extData[1];
} GParallelSpace;

typedef enum Direction
{
    UP, RIGHT, DOWN, LEFT
} Direction;

GParallelSpace * GParallelSpace_Create(GStandardSpace * pStandardSpace);

void GFastDeque_Destory(GParallelSpace * This);

void GParallelSpace_InitializeTable(GParallelSpace * This, LPCSTR mapInitStr);

void GParallelSpace_InitializeEntry(GParallelSpace * This, u32 x, u32 y);

GParallelSpace * GParallelSpace_Move(const GParallelSpace * This, Direction dir);

bool GParallelSpace_TestGoal(const GParallelSpace * This, u32 x, u32 y);

LPCSTR GParallelSpace_Output(const GParallelSpace * This);

#endif

