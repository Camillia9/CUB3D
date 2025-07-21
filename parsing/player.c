#include "../includes/cub3d.h"

void	find_player_position(t_data *data, int *x, int *y)
{
	//int	i;
	//int	j;

	*x = 0;
	*y = 0;
	//i = 0;
	while (*y < data->map.height)
	{
		if (!data->map.grid[*y])
		{
			(*y)++;
			continue;
		}
		*x = 0;
		while (data->map.grid[*y][*x])
		{
			if (is_player_char(data->map.grid[*y][*x]))
			{
				data->map.player_x = *x;
				data->map.player_y = *y;
				data->map.player_dir = data->map.grid[*y][*x];
				return;
			}
			(*x)++;
		}
		(*y)++;
	}
}
