#include "../includes/cub3d.h"

int	is_wall(t_data *data, int x, int y)
{
	if ((x < 0) || (x >= data->map.width) || (y < 0) || (y >= data->map.height))
		return (1);
	if (data->map.grid[y][x] == '1')
		return (1);
	return (0);
}
