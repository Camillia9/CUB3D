#include "../includes/cub3d.h"

//int	validate_complete_map(t_data *data)
//{
//	printf("Starting complete map validation...\n");
//	if (validate_map_basic(data) != 0)
//		return (-1);
//	// if (validate_map_closure(data) != 0)
//	// 	return -1;
//	printf("✓ Complete map validation successful!\n");
//	return (0);
//}

//int	validate_map_basic(t_data *data)
//{
//	int	player_count = 0;
//	int	empty_spaces = 0;
//	int	player_x = -1;
//	int	player_y = -1;

//	if (data->map.height == 0 || data->map.width == 0 || !data->map.grid)
//	{
//		fprintf(stderr, "Error: Map is empty\n");
//		return -1;
//	}

//	count_map_elements(data, &player_count, &empty_spaces);

//	if (player_count == 0)
//	{
//		fprintf(stderr, "Error: No player found in map (need N, S, E, or W)\n");
//		return -1;
//	}
//	if (player_count > 1)
//	{
//		fprintf(stderr, "Error: Multiple players found in map (only one allowed)\n");
//		return -1;
//	}
//	if (empty_spaces == 0)
//	{
//		fprintf(stderr, "Error: No empty spaces found in map (need at least one '0')\n");
//		return -1;
//	}

//	find_player_position(data, &player_x, &player_y);

//	printf("✓ Basic validation passed: 1 player (%c) at (%d,%d), %d empty\n",
//		data->map.player_dir, player_x, player_y, empty_spaces);

//	return 0;
//}

void	validate_complete_map(t_data *data)
{
	printf("Starting complete map validation...\n");
	validate_map_basic(data);
	validate_map_closure(data);
	printf("✓ Complete map validation successful!\n");
}

void	validate_map_basic(t_data *data)
{
	int	player_count;
	int	empty_spaces;
	int	player_x;
	int	player_y;

	if (data->map.height == 0 || data->map.width == 0 || !data->map.grid)
		print_error("Map is empty", data);
	count_map_elements(data, &player_count, &empty_spaces);
	if (player_count == 0)
		print_error("No player found in map (need N, S, E, or W)", data);
	if (player_count > 1)
		print_error("Multiple players found in map (only one allowed)",
			data);
	if (empty_spaces == 0)
		print_error("No empty spaces found in map (need at least one '0')",
			data);
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

int	flood_fill(char **grid, int x, int y, t_map *map)
{
	// Si on sort du tableau : map ouverte
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (0);

	// Si on touche un espace vide : map ouverte
	if (grid[y][x] == ' ' || grid[y][x] == '2')
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
