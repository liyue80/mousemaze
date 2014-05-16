/*
 * Implement a deque, which cannot modify its elements
 * except pushing to back and poping from front.
 */

#ifndef _FAST_DEQUE_H_
#define _FAST_DEQUE_H_

#include "common.h"
#include "ParallelSpace.h"

#define FAST_DEQUE_CAPACITY (WIDTH + HEIGHT)

typedef struct GFastDeque
{
    u32 head; // front
    u32 tail; // back
    GParallelSpace nodes[FAST_DEQUE_CAPACITY];
} GFastDeque;

GFastDeque * GFastDeque_Initialize(GFastDeque * This);

bool GFastDeque_PushBack(GFastDeque * This, const GParallelSpace * pValue);

bool GFastDeque_PopFront(GFastDeque * This, GParallelSpace * pValue);

#endif

