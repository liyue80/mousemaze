/*
 *
 */
#ifdef _MSC_VER
#include <Windows.h>
#endif
#include <stdio.h>
#include <string.h>

/* 为了优化代码，程序中使用了相关立即数，所以不能改动WIDTH 和HEIGHT 的值*/
#define WIDTH  30
#define HEIGHT 30

/* 已知的3个测试用例 */
#define C1 "111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111"
#define C2 "111110000000000000000000000011110010111111111110111111110100110010100000010000100000010010110011111100010000100111110010110010100101111110100000010010110110100101111110111111111110111010100101111110100000010010110010100101111110101111110010110010100101111110100000010010110110100101111110111111010110111010100101111110100000010010110010110111111111100000010010110010101001010100101111110110110010100101010101100000010010010010100001010110111111110110010010111101010100111111110010011110100000010101111111110110000000100000000110111111110010111011111111110100111111110010101011100000000100111111110010101011100000000101100000001110101011111111110110100000000010101011100000001100101111111110111000101001000100100000000000001000101001000000111111111111011111111111111110010000010001010100101010010010001010100111010100101010010011111111100100010100101110010100101010111111110111100011110000000000000001"
#define C3 "111110000100010010101001000011110010111111111110111111110100110010100000010000100000010011110011111100010000101111110010110010100101111110100000010010110110100101111110111111111111111010100101111110100000010010110010100101111110101111110010110010100101111110100000010010110110100101111110111111010111111010100101111110100000010010110010110111111111100000010010110010101001010100101111110111110010100101010101100000010010010010100001010110111111110111010010111101010100111111110010011110100000010101111111110111000000100000010110111111110010111011111111110100111111110010101011100000010100111111110010101011100000010101100000001111101011111111110110100000000010101011100000001100101111111111111000101001110100101000000000001000001001000000111111111111011111111111111110010000010001010100101010010010001010100111010100101010010011111111100100010100101110010100101010111111110111100011110000000000101101"

typedef unsigned long ulong;
typedef unsigned long long ulonglong;

#define LEFT  -2
#define UP    -1
#define DOWN   1
#define RIGHT  2

typedef struct node_t
{
    ulong distance;
    long  direct;
} node_t;

char   input[WIDTH*HEIGHT+2];
node_t nodes[WIDTH*HEIGHT];

#define PERFORMANCE_TEST 1

#if PERFORMANCE_TEST
static __inline ulonglong read_counter()
{
    ulonglong ts;
#if defined(_MSC_VER)
    QueryPerformanceCounter((LARGE_INTEGER*)&ts);
#else
    ulong ts1, ts2;
    __asm__ __volatile__("rdtsc\n\t":"=a"(ts1), "=d"(ts2));
    ts = ((ulonglong) ts2 << 32) | ((ulonglong) ts1);
#endif
    return ts;
}
#endif

void move(char *input_xy, node_t *node_xy, ulong distance, long direct)
{
    ulong offset = (ulong)(input_xy - &input[0]);
    ulong x = offset % WIDTH;

    if (*input_xy == '1' && node_xy->distance > distance)
    {
        node_xy->direct = -direct;
        node_xy->distance = distance;

        if (x!=0) move(input_xy-1, node_xy-1, distance+1, LEFT);
        if (offset>=WIDTH) move(input_xy-WIDTH, node_xy-WIDTH, distance+1, UP);
        if (x!=WIDTH-1) move(input_xy+1, node_xy+1, distance+1, RIGHT);
        if (offset<870) move(input_xy+WIDTH, node_xy+WIDTH, distance+1, DOWN);
    }

#if 0
    switch (direct)
    {
        case LEFT:
            if (x==0) return;
            input_xy--;
            node_xy--;
            break;
        case UP:
            if (offset<WIDTH) return;
            input_xy -= WIDTH;
            node_xy -= WIDTH;
            break;
        case RIGHT:
            if (x==WIDTH-1) return;
            input_xy++;
            node_xy++;
            break;
        case DOWN:
            if (offset>869) return;
            input_xy += WIDTH;
            node_xy += WIDTH;
            break;
    }

    if (*input_xy != '1' || node_xy->distance <= distance)
        return;

    node_xy->direct   = -direct;
    node_xy->distance = distance;

    move(input_xy, node_xy, LEFT);
    move(input_xy, node_xy, UP);
    move(input_xy, node_xy, RIGHT);
    move(input_xy, node_xy, DOWN);
#endif
}

void draw(const char *map)
{
	ulong i, j;
	for (i=0; i<HEIGHT; i++)
	{
		for(j=0; j<WIDTH; j++)
			printf("%c", map[WIDTH*i+j]);
		printf("\n");
	}
	printf("\n");
}

void output(ulong offset)
{
	if (nodes[offset].distance == (ulong)-1)
	{
		printf("0");
	}
    else
    {
        char map[WIDTH*HEIGHT+2];
        memcpy((void*)map, (const void*)input, sizeof(map));
        map[offset] = '2';

        do
		{
            switch (nodes[offset].direct)
            {
                case RIGHT: offset++; break;
                case DOWN : offset+=WIDTH; break;
                case UP   : offset-=WIDTH; break;
                default   : offset--;
            }
            map[offset] = '2';
		} while(nodes[offset].distance != 0);

        map[900] = 0;

#if 1
#if !PERFORMANCE_TEST
		printf((const char*)map);
#endif
#else
		draw((const char*)map);
#endif
    }
}

#if PERFORMANCE_TEST
#define init_cp                                 \
    ulonglong tick = 0
    
#define check_point                             \
    printf(" : %lld\n", read_counter() - tick); \
    tick = read_counter()
#else
#define init_cp
#define check_point
#endif

int main()
{
	init_cp;

#if PERFORMANCE_TEST
	strcpy((char*)input, C2);
#else
	gets((char*)input);
#endif

    check_point;

    memset((void*)nodes, 0xff, sizeof(nodes));

    check_point;

    input[899] = '2';
    nodes[899].distance = 0;

    //check_point;

    move(&input[898], &nodes[898], 1, LEFT);
    move(&input[869], &nodes[869], 1, UP);
    //move(898, 1, LEFT);
    //move(869, 1, UP);

    check_point;

    output(0);
    output(870);

    check_point;

    return 0;
}

