#include "../includes/cub3d.h"

static int	is_on_border(int x, int y, t_data *data)
{
	if (x == 0 || y == 0)
		return (1);
	if (x == data->map.width - 1 || y == data->map.height - 1)
		return (1);
	return (0);
}

static int	flood_fill_from_zero(char **grid, int x, int y, t_data *data)
{
	if (x < 0 || y < 0 || x >= data->map.width || y >= data->map.height)
		return (0);
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (1);
	if (grid[y][x] == ' ' || grid[y][x] == '2')
	{
		if (is_on_border(x, y, data))
			return (0);
	}
	grid[y][x] = 'V';
	if (!flood_fill_from_zero(grid, x - 1, y, data))
		return (0);
	if (!flood_fill_from_zero(grid, x + 1, y, data))
		return (0);
	if (!flood_fill_from_zero(grid, x, y - 1, data))
		return (0);
	if (!flood_fill_from_zero(grid, x, y + 1, data))
		return (0);
	return (1);
}
static void	free_grid_temp(char **grid, int height)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < height)
	{
		if (grid[i])
			free(grid[i]);
		i++;
	}
	free(grid);
}

static int	validate_all_zeros_closed(t_data *data)
{
	char	**temp_grid;
	int		x;
	int		y;
	int		result;

	temp_grid = dupplicate_grid(&data->map);
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
			{
				if (!flood_fill_from_zero(temp_grid, x, y, data))
					result = 0;
			}
			x++;
		}
		y++;
	}
	free_grid_temp(temp_grid, data->map.height);
	return (result);
}
static int	flood_fill_from_player(char **grid, int x, int y, t_data *data)
{
	if (x < 0 || y < 0 || x >= data->map.width || y >= data->map.height)
		return (0);
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (1);
	if (grid[y][x] == ' ' || grid[y][x] == '2')
	{
		if (is_on_border(x, y, data))
			return (0);
	}
	grid[y][x] = 'V';
	if (!flood_fill_from_player(grid, x - 1, y, data))
		return (0);
	if (!flood_fill_from_player(grid, x + 1, y, data))
		return (0);
	if (!flood_fill_from_player(grid, x, y - 1, data))
		return (0);
	if (!flood_fill_from_player(grid, x, y + 1, data))
		return (0);
	return (1);
}

static int	validate_player_enclosed(t_data *data)
{
	char	**temp_grid;
	int		result;

	temp_grid = dupplicate_grid(&data->map);
	if (!temp_grid)
		return (0);
	result = flood_fill_from_player(temp_grid, data->map.player_x, 
		data->map.player_y, data);
	free_grid_temp(temp_grid, data->map.height);
	return (result);
}


//int	validate_map_closure(t_data *data)
//{
//	printf("🔍 Checking map closure...\n");
//	if (!validate_all_zeros_closed(data))
//	{
//		print_error("Map is not closed: empty spaces can reach borders", data);
//		return (0);
//	}
//	printf("✓ All empty spaces are properly enclosed\n");
//	if (!validate_player_enclosed(data))
//	{
//		print_error("Player can escape from the map", data);
//		return (0);
//	}
//	printf("✓ Player is properly enclosed\n");
//	return (1);
//}