/*
 *
 */
#include "ParallelSpace.h"
#include "FastDeque.h"
#include "FixedMemPool.h"

/* **************************************
* Main function and global variables.
************************************** */
const u32 WIDTH = 30;
const u32 HEIGHT = 30;

int main(int argc, char **argv)
{
    char inputs[WIDTH * HEIGHT + 100];
    gets(inputs);

    GParallelSpace * pSpace = GParallelSpace_Create();
    GParallelSpace_InitializeTable(pSpace, WIDTH, HEIGHT, inputs);
    GParallelSpace_InitializeEntry(pSpace, 29, 29);

    GFastDeque * pDeque = GFastDeque_Create();
    GFastDeque_PushBack(pDeque, pSpace);

    GParallelSpace * pGoalSpace1 = NULL;
    GParallelSpace * pGoalSpace2 = NULL;

    // reuse pSpace in the while loop
    while (!pGoalSpace1 || !pGoalSpace2)
    {
        if (GFastDeque_IsEmpty(pDeque))
        {
            // TBD
            break;
        }

        pSpace = GFastDeque_PopFront(pDeque);

        Direction dir;
        GParallelSpace * pParallel;

        for ( dir = UP; dir <= LEFT; dir++ )
        {
            pParallel = GParallelSpace_Move(pSpace, dir);
            if (pParallel != NULL)
            {
                if (GParallelSpace_TestGoal(pParallel, 0, 0))
                {
                }
                else if (GParallelSpace_TestGoal(pParallel, 29, 0))
                {
                }
                else
                {
                    GFastDeque_PushBack(pDeque, (void *)pParallel);
                }
            }
        }
    }
}

