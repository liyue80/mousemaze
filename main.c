/*
 *
 */
#ifdef _MSC_VER
#include <Windows.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PERFORMANCE_TEST 0    // 开启性能测试模式  默认值：0
#define FRIENDLY_OUTPUT  0    // 使用友好的输出 默认值：0

/* 为了优化代码，程序中使用了相关立即数，所以不能改动WIDTH 和HEIGHT 的值*/
#define WIDTH  30
#define HEIGHT 30

/* 已知的3个测试用例 */
#define C1 "111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111"
#define C2 "111110000000000000000000000011110010111111111110111111110100110010100000010000100000010010110011111100010000100111110010110010100101111110100000010010110110100101111110111111111110111010100101111110100000010010110010100101111110101111110010110010100101111110100000010010110110100101111110111111010110111010100101111110100000010010110010110111111111100000010010110010101001010100101111110110110010100101010101100000010010010010100001010110111111110110010010111101010100111111110010011110100000010101111111110110000000100000000110111111110010111011111111110100111111110010101011100000000100111111110010101011100000000101100000001110101011111111110110100000000010101011100000001100101111111110111000101001000100100000000000001000101001000000111111111111011111111111111110010000010001010100101010010010001010100111010100101010010011111111100100010100101110010100101010111111110111100011110000000000000001"
#define C3 "111110000100010010101001000011110010111111111110111111110100110010100000010000100000010011110011111100010000101111110010110010100101111110100000010010110110100101111110111111111111111010100101111110100000010010110010100101111110101111110010110010100101111110100000010010110110100101111110111111010111111010100101111110100000010010110010110111111111100000010010110010101001010100101111110111110010100101010101100000010010010010100001010110111111110111010010111101010100111111110010011110100000010101111111110111000000100000010110111111110010111011111111110100111111110010101011100000010100111111110010101011100000010101100000001111101011111111110110100000000010101011100000001100101111111111111000101001110100101000000000001000001001000000111111111111011111111111111110010000010001010100101010010010001010100111010100101010010011111111100100010100101110010100101010111111110111100011110000000000101101"

typedef unsigned long ulong;
typedef unsigned long long ulonglong;

// 互为相反数，可简化代码
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
char   deathmap[WIDTH*HEIGHT+2];
node_t nodes[WIDTH*HEIGHT];

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

void move(ulong offset, ulong distance, long direct)
{
	node_t *pnode = &nodes[offset];
	if (input[offset] == '1' && pnode->distance > distance)
    {
        ulong x = offset % WIDTH;
		pnode->direct = -direct;
        pnode->distance = distance;
        distance++;

        if (x!=0)           move(offset-1,     distance, LEFT);
        if (offset>=WIDTH)  move(offset-WIDTH, distance, UP);
        if (x<WIDTH-1)      move(offset+1,     distance, RIGHT);
        if (offset<=869)    move(offset+WIDTH, distance, DOWN);
    }
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
#if !PERFORMANCE_TEST
		printf("0");
#endif
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

#if !FRIENDLY_OUTPUT
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

// 统计地图中'1'的个数
int onecount()
{
    char * p = (char *)input;
	int a = strlen(input);
    ulong count = 0;
    do
    {
        count += (*p - '0');
    } while (*(++p));

    return count;
}

// 被death()调用，递归扩展'0'，直到遇到底边界时返回1，或者遇到其它边界时返回0.
int spread(ulong offset)
{
    if (offset > 898)
        return 0;
    if (deathmap[offset] != '0')
        return 0;
    if (offset > 870)
        return 1;
    deathmap[offset] = '4';
    
    if (spread(offset+WIDTH))   return 1;
    if (spread(offset+WIDTH-1)) return 1;
    if (spread(offset+WIDTH+1)) return 1;

    return 0;
}

// 判断地图是否是死图，即无路径连接出口和入口。
int death()
{
	ulong offsets[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,59,89,119,149,179,209,239,269,299,329,359,389,419,449,479,509,539,569,599,629,659,689,719,749,779,809,839,869,0};
    ulong *p;

	memcpy((void*)deathmap, (const void*)input, sizeof(deathmap));

    for (p = offsets; *p != 0; p++)
	{
        if (deathmap[*p] == '0')
        {
            deathmap[*p] = '4';
            if (spread(*p+WIDTH))   return 1;
            if (spread(*p+WIDTH-1)) return 1;
            if (spread(*p+WIDTH+1)) return 1;
        }
	}

    return 0;
}

int main(int argc, char **argv)
{
	init_cp;

#if PERFORMANCE_TEST
    if (argc > 1)
        switch ( *argv[1] )
        {
            case '1': strcpy((char*)input, C1); break;
            case '2': strcpy((char*)input, C2); break;
            case '3': strcpy((char*)input, C3); break;
            default:  strcpy((char*)input, C1); break;
        }
    else
        strcpy((char*)input, C2);
#else
	gets((char*)input);
#endif
    
    check_point;
	if (onecount() > 600)
	{
		if (death())
		{
            check_point;
#if !PERFORMANCE_TEST
			printf("00");
#endif
			exit(0);
		}
	}

    check_point;

    memset((void*)nodes, 0xff, sizeof(nodes));

    check_point;

    input[899] = '2';
    nodes[899].distance = 0;

    check_point;

    move(898, 1, LEFT);
    move(869, 1, UP);

    check_point;

    output(0);
    output(870);

    check_point;

    return 0;
}

