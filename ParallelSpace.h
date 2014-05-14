/*
 *
 */
#ifndef _PARALLEL_SPACE_H_
#define _PARALLEL_SPACE_H_

#include "common.h"

typedef struct GParallelSpace_t
{
    // Following members are private.
    Size mapSize;
    Position currentPos;
    unsigned char * roadmap;
} GParallelSpace;

typedef enum Direction
{
    UP, RIGHT, DOWN, LEFT
} Direction;

GParallelSpace * GParallelSpace_Create();

void GParallelSpace_InitializeTable(GParallelSpace * This, u32 width, u32 height, LPCSTR mapInitStr);

void GParallelSpace_InitializeEntry(GParallelSpace * This, u32 x, u32 y);

GParallelSpace * GParallelSpace_Move(const GParallelSpace * This, Direction dir);

bool GParallelSpace_TestGoal(const GParallelSpace * This, u32 x, u32 y);

#endif

