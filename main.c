#include <stdio.h>
#include <string.h>

#define WIDTH  30
#define HEIGHT 30

#define LEFT  -2
#define UP    -1
#define DOWN   1
#define RIGHT  2

typedef struct node_t
{
    unsigned distance;
    long  direct;
} node_t;

char   input[WIDTH*HEIGHT+2];
node_t nodes[WIDTH*HEIGHT];

void move(unsigned offset, unsigned distance, long direct)
{
    if (input[offset] == '1' && nodes[offset].distance > distance)
    {
        unsigned x = offset % WIDTH;
        nodes[offset].distance = distance;
        nodes[offset].direct   = -direct;

        distance++;

        if (x!=0)           move(offset-1,     distance, LEFT);
        if (offset>=WIDTH)  move(offset-WIDTH, distance, UP);
        if (x<WIDTH-1)      move(offset+1,     distance, RIGHT);
        if (offset<=869)    move(offset+WIDTH, distance, DOWN);
    }
}

void output(unsigned offset)
{
	if (nodes[offset].distance == (unsigned)-1)
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
		printf((const char*)map);
    }
}

int main()
{
	gets((char*)input);
    memset((void*)nodes, 0xff, sizeof(nodes));

    input[899] = '2';
    nodes[899].distance = 0;

    move(898, 1, LEFT);
    move(869, 1, UP);

    output(0);
    output(870);

    return 0;
}

