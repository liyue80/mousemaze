/*
 *
 */
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "FastDeque.h"
#include "Performance.h"

static u32 GFastDeque_RoundPlusPlus(const GFastDeque * This, u32 value);

GFastDeque * GFastDeque_Initialize(GFastDeque * This)
{
    This->head = 0;
    This->tail = 0;
    return This;
}

bool GFastDeque_PushBack(GFastDeque * This, const GParallelSpace * pValue)
{
    u32 nextTail = GFastDeque_RoundPlusPlus(This, This->tail);

    assert(pValue != NULL);

    if (nextTail == This->head) // array if full
    {
        assert(0);
        return false;
    }

    mem_cpy(&This->nodes[This->tail], pValue, sizeof(GParallelSpace));
    This->tail = nextTail;

    return true;
}

bool GFastDeque_PopFront(GFastDeque * This, GParallelSpace * pValue)
{
    assert(pValue != NULL);

    if (This->head == This->tail) // array is empty
	{
        return false;
	}

    mem_cpy(pValue, &This->nodes[This->head], sizeof(GParallelSpace));
    This->head = GFastDeque_RoundPlusPlus(This, This->head);
    return true;
}

static u32 GFastDeque_RoundPlusPlus(const GFastDeque * This, u32 value)
{
    value++;
    if (value >= FAST_DEQUE_CAPACITY)
        return 0;
    return value;
}

