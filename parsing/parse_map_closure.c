#include "../includes/cub3d.h"

int	flood_fill_check(char **grid, int x, int y, t_data *data)
{
	if (x < 0 || y < 0 || x >= data->map.width || y >= data->map.height)
		return (0);
	if (grid[y][x] == ' ' || grid[y][x] == '2')
		return (0);
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (1);
	grid[y][x] = 'V';
	if (!flood_fill_check(grid, x - 1, y, data))
		return (0);
	if (!flood_fill_check(grid, x + 1, y, data))
		return (0);
	if (!flood_fill_check(grid, x, y - 1, data))
		return (0);
	if (!flood_fill_check(grid, x, y + 1, data))
		return (0);
	return (1);
}

static int	check_all_zeros_enclosed(t_data *data)
{
	char	**temp_grid;
	int		result;
	int		y;
	int		x;

	temp_grid = duplicate_grid(data);
	if (!temp_grid)
		return (0);
	result = 1;
	y = 0;
	while (y < data->map.height && result)
	{
		x = 0;
		while (x < data->map.width && result)
		{
			if (temp_grid[y][x] == '0')
				result = flood_fill_check(temp_grid, x, y, data);
			x++;
		}
		y++;
	}
	free_temp_grid(temp_grid, data->map.height);
	return (result);
}

static int	check_player_enclosed(t_data *data)
{
	char	**temp_grid;
	int		result;

	temp_grid = duplicate_grid(data);
	if (!temp_grid)
		return (0);
	result = flood_fill_check(temp_grid, data->map.player_x,
			data->map.player_y, data);
	free_temp_grid(temp_grid, data->map.height);
	return (result);
}

int	validate_map_closure(t_data *data)
{
	printf("🔍 Checking all empty spaces are enclosed...\n");
	if (!check_all_zeros_enclosed(data))
	{
		print_error("Map not closed: some empty spaces can escape", data);
		return (0);
	}
	printf("✓ All empty spaces are properly enclosed\n");
	printf("🔍 Checking player can't escape...\n");
	if (!check_player_enclosed(data))
	{
		print_error("Map not closed: player can escape", data);
		return (0);
	}
	printf("✓ Player is properly enclosed\n");
	return (1);
}
