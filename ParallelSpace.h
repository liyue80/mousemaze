/*
 *
 */
#ifndef _PARALLEL_SPACE_H_
#define _PARALLEL_SPACE_H_

#include "common.h"
#include "StandardSpace.h"

typedef struct GParallelSpace_t
{
	GStandardSpace * standardSpace;
	u32 x;
	u32 y;
	u32 distance;  // 已经移动的步数
    u8 roadmap[HEIGHT][WIDTH];
} GParallelSpace;

typedef enum Direction
{
    LEFT, UP, RIGHT, DOWN
} Direction;

void GParallelSpace_Initialize(GParallelSpace * This, GStandardSpace * pStandardSpace);

void GParallelSpace_InitializeTable(GParallelSpace * This, LPCSTR mapInitStr);

void GParallelSpace_InitializeEntry(GParallelSpace * This, u32 x, u32 y);

bool GParallelSpace_Move(const GParallelSpace * This, Direction dir, GParallelSpace * pNextSpace);

bool GParallelSpace_TestGoal(const GParallelSpace * This, u32 x, u32 y);

LPCSTR GParallelSpace_Output(const GParallelSpace * This);

#endif

