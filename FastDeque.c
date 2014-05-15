/*
 *
 */
#include <stdlib.h>
#include <assert.h>
#include "FastDeque.h"

static u32 GFastDeque_RoundPlusPlus(const GFastDeque * This, u32 value);

GFastDeque * GFastDeque_Create(void)
{
    GFastDeque * fd = (GFastDeque*)malloc(sizeof(GFastDeque));
    fd->capacity = FAST_DEQUE_CAPACITY;
    fd->head = 0;
    fd->tail = 0;
    return fd;
}

void GFastDeque_PushBack(GFastDeque * This, void * data)
{
    u32 nextTail = GFastDeque_RoundPlusPlus(This, This->tail);
	//printf("%d %d", This->head, This->tail);
    if (nextTail == This->head) // array if full
    {
        assert(0);
        return;
    }

    This->elements[This->tail] = data;
    This->tail = nextTail;
	//printf(" => %d %d\n", This->head, This->tail);
    return;
}

void * GFastDeque_PopFront(GFastDeque * This)
{
	void * data;

    if (This->head == This->tail) // array is empty
	{
        return NULL;
	}

    data = This->elements[This->head];
    This->head = GFastDeque_RoundPlusPlus(This, This->head);
    return data;
}

bool GFastDeque_IsEmpty(const GFastDeque * This)
{
    return (This->head == This->tail);
}

static u32 GFastDeque_RoundPlusPlus(const GFastDeque * This, u32 value)
{
    value++;
    if (value >= This->capacity)
        return 0;
    return value;
}
