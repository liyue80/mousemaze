#define MAP_SIZE 30
#include <stdio.h>
struct node
{
	unsigned char path;
	unsigned short distance;
	struct node *from;
} map[MAP_SIZE + 2][MAP_SIZE + 2] = {0};

walk(unsigned char x, unsigned char y, struct node *from, unsigned char init)
{
	while(map[x + 1][y].path + map[x][y + 1].path + map[x - 1][y].path + map[x][y - 1].path + init <= 2)
	{
		map[x][y].distance = from->distance + 1;
		map[x][y].from = from;
		from = &map[x][y];

		if(map[x + 1][y].path && (!map[x + 1][y].distance || map[x + 1][y].distance > map[x][y].distance + 1))
			x ++;
		else if(map[x][y + 1].path && (!map[x][y + 1].distance || map[x][y + 1].distance > map[x][y].distance + 1))
			y ++;
		else if(map[x - 1][y].path && (!map[x - 1][y].distance || map[x - 1][y].distance > map[x][y].distance + 1))
			x --;
		else if(map[x][y - 1].path && (!map[x][y - 1].distance || map[x][y - 1].distance > map[x][y].distance + 1))
			y --;
		else
			return;
	}

	map[x][y].distance = from->distance + 1;
	map[x][y].from = from;

	if(map[x + 1][y].path && (!map[x + 1][y].distance || map[x + 1][y].distance > map[x][y].distance + 1))
		walk(x + 1, y, &map[x][y], 0);
	if(map[x][y + 1].path && (!map[x][y + 1].distance || map[x][y + 1].distance > map[x][y].distance + 1))
		walk(x, y + 1, &map[x][y], 0);
	if(map[x - 1][y].path && (!map[x - 1][y].distance || map[x - 1][y].distance > map[x][y].distance + 1))
		walk(x - 1, y, &map[x][y], 0);
	if(map[x][y - 1].path && (!map[x][y - 1].distance || map[x][y - 1].distance > map[x][y].distance + 1))
		walk(x, y - 1, &map[x][y], 0);
}

inline mark_path(struct node *current, char tag)
{
	while(current->from != 0)
	{
		current->path = tag;
		current = current->from;
	}
}

inline output(unsigned char x, unsigned char y)
{
	unsigned char i, j;

	if(map[x][y].distance)
	{
		mark_path(&map[x][y], 2);
		for(i = 1; i <= MAP_SIZE; i ++)
			for(j = 1; j <= MAP_SIZE; j ++)
				printf("%d", map[i][j].path);
	}
	else
		printf("0");
}

main()
{
	unsigned short i, j, k = 0;
	unsigned char input[MAP_SIZE * MAP_SIZE + 4] = {0};

	gets(input);
	for(i = 1; i <= MAP_SIZE; i ++)
		for(j = 1; j <= MAP_SIZE; j ++)
			map[i][j].path = input[k ++] - '0';

	if(map[30][30].path)
		walk(30, 30, &map[30][31], 1);

	output(1, 1);
	mark_path(&map[1][1], 1);
	output(30, 1);
}
