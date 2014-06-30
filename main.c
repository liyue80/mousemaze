
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#define inline
#include <Windows.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEST_IN_CPE		1	/* �������ܲ���ģʽ����CPE_Check����ʾ�����ʱ�����ᵼ��CPE_Check ʧ�ܣ��������IO ������ִ�е�ʱ��  Ĭ��ֵ��0 */
#define FRIENDLY_OUTPUT 0   /* ʹ���Ѻõ�������ᵼ��CPE_Check ʧ�� Ĭ��ֵ��0 */

/* ��Ҫ��Ϊ���Ż����룬������ʹ������������������Բ��ܸĶ�WIDTH ��HEIGHT ��ֵ*/
#define WIDTH  30
#define HEIGHT 30

/* �Ӹ�����ʼ������룬����Ҫ��0xFFȥ��� */
#define DISTANCE_ZERO  (-2000)

#if FRIENDLY_OUTPUT
/* ��֪��3���������� */
#define C1 "111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111111111111111101111111111111111"
#define C2 "111110000000000000000000000011110010111111111110111111110100110010100000010000100000010010110011111100010000100111110010110010100101111110100000010010110110100101111110111111111110111010100101111110100000010010110010100101111110101111110010110010100101111110100000010010110110100101111110111111010110111010100101111110100000010010110010110111111111100000010010110010101001010100101111110110110010100101010101100000010010010010100001010110111111110110010010111101010100111111110010011110100000010101111111110110000000100000000110111111110010111011111111110100111111110010101011100000000100111111110010101011100000000101100000001110101011111111110110100000000010101011100000001100101111111110111000101001000100100000000000001000101001000000111111111111011111111111111110010000010001010100101010010010001010100111010100101010010011111111100100010100101110010100101010111111110111100011110000000000000001"
#define C3 "111110000100010010101001000011110010111111111110111111110100110010100000010000100000010011110011111100010000101111110010110010100101111110100000010010110110100101111110111111111111111010100101111110100000010010110010100101111110101111110010110010100101111110100000010010110110100101111110111111010111111010100101111110100000010010110010110111111111100000010010110010101001010100101111110111110010100101010101100000010010010010100001010110111111110111010010111101010100111111110010011110100000010101111111110111000000100000010110111111110010111011111111110100111111110010101011100000010100111111110010101011100000010101100000001111101011111111110110100000000010101011100000001100101111111111111000101001110100101000000000001000001001000000111111111111011111111111111110010000010001010100101010010010001010100111010100101010010011111111100100010100101110010100101010111111110111100011110000000000101101"

/* No way to left-top corner */
#define M1 "100000000000000000000000000000011111111111111111111111110000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000111111111111111111111111111111100000000000000000000000000001"
/* No way to left-bottom corner */
#define M2 "110000000000000000000000000000111111111111111111111111110000110000000000000000000000010000100000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000000000000000000000000000010000101111111111111111111111111111100000000000000000000001000001"

#endif

#ifdef TEST_IN_CPE
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
#endif

// ��Ϊ�෴�����ɼ򻯴���
#define LEFT  -1
#define UP    -30
#define DOWN   30
#define RIGHT  1

typedef struct node_t
{
    long  distance;
    long  direct;
} node_t;

char   input[WIDTH*HEIGHT*2+4];  // larger than the map, in order to contain the full output string.
char   deathmap[WIDTH*HEIGHT+2];
node_t nodes[WIDTH*HEIGHT] = {0};
int    fake_stack[WIDTH*HEIGHT];
int   *pfsHead, *pfsTail;

#if TEST_IN_CPE
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

#if FRIENDLY_OUTPUT
const char * draw(const char *map)
{
	ulong i, j;

    if ( *map == '0' )
    {
        printf("0\n");
        return map + 1;
    }

	for (i=0; i<HEIGHT; i++)
	{
		for(j=0; j<WIDTH; j++)
			printf("%c", map[WIDTH*i+j]);
		printf("\n");
	}
	printf("\n");

    return map + 900;
}
#endif

// ����nodes����д��ɵ����ݣ���30x30��С��map�л�����������ս����
// ����ֵ������ָ���ַ���ĩβӦ����'\0'��λ�ã����˺���������'\0'��������Ӧע�⡣
inline char* build(char *map, unsigned entry)
{
	/* ����ʹ��ָ�뷴�������ٶ� ???  */
	char * ret;
	if (nodes[entry].distance == 0)
	{
		map[0] = '0';
		ret = &map[1];
	}
	else
	{
		while (nodes[entry].distance != DISTANCE_ZERO)
		{
			map[entry] = '2';
			entry += nodes[entry].direct;
		}
		map[entry] = '2';
		ret = &map[900];
	}

	return ret;
}

#if TEST_IN_CPE
#define init_cp                                 \
    ulonglong tick = read_counter();            \
    ulonglong tick_a = tick;

#define check_point                             \
    fprintf(stderr, "#%d : %lld\n", __LINE__, read_counter() - tick); \
    tick = read_counter()

#define final_cp								\
	fprintf(stderr, "Final : %lld\n", read_counter() - tick_a);
	
#else
#define init_cp
#define check_point
#define final_cp
#endif

// ��death()���ã��ݹ���չ'0'��ֱ�������ױ߽�ʱ����1�����������յ�֮�䱻'0'������޷�ͨ�����������������߽�ʱ����0��
int spread(ulong offset)
{
    unsigned r;

    if (offset > 898)
        return 0;
    if (deathmap[offset] != '0')
        return 0;
    if (offset > 870)
        return 1;
    deathmap[offset] = '4';

    r = offset % 30;    
    if (spread(offset+WIDTH))   return 1;
    if (r != 0) if (spread(offset+29)) return 1;
    if (r != 29) if (spread(offset+31)) return 1;

    return 0;
}

// �жϳ�����ڼ��Ƿ���ͨ·��
ulong offsets[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
    21,22,23,24,25,26,27,28,29,59,89,119,149,179,209,239,269,299,329,
    359,389,419,449,479,509,539,569,599,629,659,689,719,749,779,809,839,869,0};

int death()
{
    ulong *p;

	memcpy(deathmap, input, sizeof(deathmap));

    for (p = offsets; *p != 0; p++)
	{
        unsigned r = (*p) % 30;

        if (deathmap[*p] == '0')
        {
            deathmap[*p] = '4';
            if (spread(*p+WIDTH)) return 1;
            if (r != 0)  if (spread(*p+29)) return 1;
            if (r != 29) if (spread(*p+31)) return 1;
        }
	}

    return 0;
}

int i;
int remainde;
char * pout;
char * pbkup;
int main(int argc, char **argv)
{
	init_cp;
	check_point;

#if FRIENDLY_OUTPUT
    if (argc > 1)
        switch ( *argv[1] )
        {
            case '1': strcpy((char*)input, C1); break;
            case '2': strcpy((char*)input, C2); break;
            case '3': strcpy((char*)input, C3); break;
            case '4': strcpy((char*)input, M1); break;
            case '5': strcpy((char*)input, M2); break;
            default:  strcpy((char*)input, C1); break;
        }
    else
        strcpy((char*)input, C1);

    draw(input);
#else
	gets(input);
#endif

    check_point;
#if 1
	if (death())
	{
        check_point;
		printf("00");
        check_point;
        final_cp;
		exit(0);
	}
#endif
    check_point;

    nodes[899].distance = DISTANCE_ZERO;
    pfsTail = pfsHead = fake_stack;
    *pfsHead++ = 899;

    check_point;
    while (pfsHead != pfsTail)
    {
		if (*pfsTail == 0 || *pfsTail == 870) {
			pfsTail++;
			continue;
		}

		remainde = (*pfsTail % 30);

		if (remainde != 0) { //        if (!EDGE_LEFT((*pfsTail))) {
            *pfsHead = ((*pfsTail)-1);
            if (input[*pfsHead] == '1' && nodes[*pfsHead].distance > nodes[*pfsTail].distance + 1) {
                nodes[*pfsHead].distance = nodes[*pfsTail].distance + 1;
                nodes[*pfsHead].direct   = RIGHT;
                pfsHead++;
            }

			if (remainde != 29) { //        	if (!EDGE_RIGHT((*pfsTail))) {
				*pfsHead = ((*pfsTail)+1);
				if (input[*pfsHead] == '1' && nodes[*pfsHead].distance > nodes[*pfsTail].distance + 1) {
					nodes[*pfsHead].distance = nodes[*pfsTail].distance + 1;
					nodes[*pfsHead].direct   = LEFT;
					pfsHead++;
				}
			}
        }

        if (*pfsTail > 29) { //		if (!EDGE_TOP((*pfsTail))) {
            *pfsHead = ((*pfsTail)-WIDTH);
            if ( (input[*pfsHead] == '1') && (nodes[*pfsHead].distance > nodes[*pfsTail].distance + 1) ) {
                nodes[*pfsHead].distance = nodes[*pfsTail].distance + 1;
                nodes[*pfsHead].direct   = DOWN;
                pfsHead++;
            }

			if (*pfsTail < 870) { //			if (!EDGE_BOTTOM((*pfsTail))) {
				*pfsHead = ((*pfsTail)+WIDTH);
				if (input[*pfsHead] == '1' && nodes[*pfsHead].distance > nodes[*pfsTail].distance + 1) {
					nodes[*pfsHead].distance = nodes[*pfsTail].distance + 1;
					nodes[*pfsHead].direct   = UP;
					pfsHead++;
				}
			}
        }
        
        pfsTail++;
    }

    check_point;

	// ��д����ַ�������ʾ֮��
	pbkup = &input[900];
	memcpy(pbkup, input, 900);
	pout = build(input, 0);
	if (pout != pbkup)
		memmove(pout, pbkup, 900);
	pout = build(pout, 870);
	*pout = '\0';

#if !FRIENDLY_OUTPUT
	puts(input);
#else
	draw(draw(input));
#endif

    check_point;
	final_cp;

    return 0;
}

