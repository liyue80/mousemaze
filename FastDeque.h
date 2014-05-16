/*
 * Implement a deque, which cannot modify its elements
 * except pushing to back and poping from front.
 */
#include "common.h"

#ifndef _FAST_DEQUE_H_
#define _FAST_DEQUE_H_

#define FAST_DEQUE_CAPACITY 900

typedef struct GFastDeque
{
    // Following members are private
    u32 capacity;
    u32 head; // front
    u32 tail; // back
    void * elements[FAST_DEQUE_CAPACITY];
} GFastDeque;

GFastDeque * GFastDeque_Create(void);

void GFastDeque_PushBack(GFastDeque * This, void * data);

void * GFastDeque_PopFront(GFastDeque * This);

bool GFastDeque_IsEmpty(const GFastDeque * This);

#endif
