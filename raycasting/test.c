#include "../includes/cub3d.h"

char *map_test[] = {
	"11111111111",
	"10000000001",
	"1000000S101",
	"10001111111",
	"10001100001",
	"10000111111",
	"10000000001",
	"11111111111"
};

int is_wall(int x, int y)
{
	if ((x < 0) || (x >= MAP_SIZE) || (y < 0) || (y >= MAP_SIZE))
		return 1;
	if (map_test[y][x] == '1')
		return 1;
	return 0;
}
