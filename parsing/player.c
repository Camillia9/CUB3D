#include "../includes/cub3d.h"

/**
 * Vérifie si un caractère est une direction de joueur
 */
int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	find_player_position(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width && data->map.grid[y][x])
		{
			if (is_player_char(data->map.grid[y][x]))
			{
				data->map.player_x = x;
				data->map.player_y = y;
				data->map.player_dir = data->map.grid[y][x];
				return ;
			}
			x++;
		}
		y++;
	}
}
