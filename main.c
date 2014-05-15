/*
 *
 */
#ifdef _MSC_VER
#include <stdio.h>
#endif
#ifdef _DEBUG
#include <string.h>
#endif
#include "ParallelSpace.h"
#include "FastDeque.h"
#include "FixedMemPool.h"

/* **************************************
* Main function and global variables.
************************************** */
#define WIDTH  30
#define HEIGHT 30

int main(int argc, char **argv)
{
    char inputs[WIDTH * HEIGHT + 100];
	GParallelSpace * pSpace = NULL;
	GFastDeque * pDeque = NULL;
    GParallelSpace * pGoalSpace1 = NULL;
    GParallelSpace * pGoalSpace2 = NULL;
#ifdef _DEBUG
	strcpy(inputs, "222220000000000000000000000011110020111111111110111111110100110020100000010000100000010010110022211100010000100111110010110010200101111110100000010010110110200101111110111111111110111010200101111110100000010010110010200101111110101111110010110010200101111110100000010010110110200101111110111111010110111010200101111110100000010010110010210111111111100000010010110010201001010100101111110110110010200101010101100000010010010010200001010110111111110110010010211101010100111111110010011110200000010101111111110110000000200000000110111111110010111011211111110100111111110010101011200000000100111111110010101011200000000101100000001110101011211111110110100000000010101011200000001100101111111110111000201001000100100000000000001000201001000000111111111111011111222222222220010000010001010100101010010020001010100111010100101010010022222222200100010100101110010100101010222222110111100011110000000000000002");
#else
    gets(inputs);
#endif
    pSpace = GParallelSpace_Create();
    GParallelSpace_InitializeTable(pSpace, WIDTH, HEIGHT, inputs);
    GParallelSpace_InitializeEntry(pSpace, 29, 29);

    pDeque = GFastDeque_Create();
    GFastDeque_PushBack(pDeque, pSpace);

    // reuse pSpace in the while loop
    while (!pGoalSpace1 || !pGoalSpace2)
    {
        Direction dir;
        GParallelSpace * pParallel;

		if (GFastDeque_IsEmpty(pDeque))
        {
            // TBD
            break;
        }

        pSpace = GFastDeque_PopFront(pDeque);

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

