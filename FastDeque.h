/*
 * Implement a deque, which cannot modify its elements
 * except pushing to back and poping from front.
 */
#include <stdlib.h>

#ifndef _FAST_DEQUE_H_
#define _FAST_DEQUE_H_

typedef struct GFastDeque
{
    // Following members are private
    unsigned int _capacity;
    unsigned int _front;
    unsigned int _back;
    void *       _elements[640];
} GFastDeque;

GFastDeque * GFastDeque_Create();

void GFastDeque_PushBack(GFastDeque * This, void * data);

void * GFastDeque_PopFront(GFastDeque * This);

unsigned int GFastDeque_GetCount(const GFastDeque * This);

#endif
