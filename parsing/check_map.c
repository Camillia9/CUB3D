#include "../includes/cub3d.h"

void	validate_complete_map(t_data *data)
{
	printf("Starting complete map validation...\n");
	validate_map_basic(data);
	validate_map_closure(data);
	//validate_map_specific(data);
	printf("✓ Complete map validation successful!\n");
}

void	validate_map_basic(t_data *data)
{
	int	player_count;
	int	empty_spaces;
	int	player_x;
	int	player_y;

	//player_count = 0;
	//empty_spaces = 0;
	if (data->map.height == 0 || data->map.width == 0 || !data->map.grid)
		print_error("Map is empty", data);
	//validate_map_chars(data);
	count_map_elements(data, &player_count, &empty_spaces);
	if (player_count == 0)
		print_error("No player found in map (need N, S, E, or W)", data);
	if (player_count > 1)
		print_error("Multiple players found in map (only one allowed)", data);
	if (empty_spaces == 0)
		print_error("No empty spaces found in map (need at least one '0')", data);
	find_player_position(data, &player_x, &player_y);
	printf("✓ Basic validation passed: 1 player (%c) at (%d,%d), %d empty\n",
		data->map.player_dir, data->map.player_x, data->map.player_y,
		empty_spaces);
}

int	validate_map_closure(t_data *data)
{
	t_map	*tmp;
	int		player[2];
	int		success;

	tmp = malloc(sizeof(t_map));
	if (!tmp)
		return (0);
	tmp->grid = dupplicate_grid(&data->map);
	if (!tmp->grid)
		return (0);
	tmp->height = data->map.height;
	tmp->width = data->map.width;
	find_player_position(data, &player[0], &player[1]);
	success = flood_fill(tmp->grid, player[0], player[1], tmp);
	free_map(tmp);
	free(tmp);
	if (!success)
	{
		print_error("❌ Error: Map is not closed!\n", data);
	}
	return (1);
}

char	**dupplicate_grid(t_map *map)
{
	char	**temp;
	int		i;

	temp = malloc(sizeof(char *) * (map->height + 1));
	if (!temp)
		return (NULL);
	temp[map->height] = NULL;
	i = 0;
	while (i < map->height)
	{
		temp[i] = ft_strdup(map->grid[i]);
		if (!temp[i])
		{
			while (i > 0)
			{
				free(temp[i]);
				i--;
			}
			free(temp);
			return (NULL);
		}
		i++;
	}
	return (temp);
}

//void	flood_fill(char **grid, int x, int y, t_map *map)
//{
//	if (x < 0 || y < 0 || grid[y][x] == '1' || grid[y][x] == 'V'
//		|| x > map->width || y > map->height || grid[y][x] == ' ' || grid[y][x] == '\0')
//		return ;
//	grid[y][x] = 'V';
//	flood_fill(grid, x - 1, y, map);
//	flood_fill(grid, x + 1, y, map);
//	flood_fill(grid, x, y - 1, map);
//	flood_fill(grid, x, y + 1, map);
//}

int	flood_fill(char **grid, int x, int y, t_map *map)
{
	// Si on sort du tableau : map ouverte
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (0);

	// Si on touche un espace vide : map ouverte
	if (grid[y][x] == ' ')
		return (0);

	// Si c'est un mur ou déjà visité, on ne continue pas
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (1);

	// Marquer comme visité
	grid[y][x] = 'V';

	// On propage dans toutes les directions et on vérifie qu'aucune ne retourne une erreur
	if (!flood_fill(grid, x - 1, y, map))
		return (0);
	if (!flood_fill(grid, x + 1, y, map))
		return (0);
	if (!flood_fill(grid, x, y - 1, map))
		return (0);
	if (!flood_fill(grid, x, y + 1, map))
		return (0);

	return (1);
}
