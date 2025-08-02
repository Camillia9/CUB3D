#include "../includes/cub3d.h"

int	is_valid_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			break ;
		if (!ft_strchr("01 NSEW", line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	count_map_elements(t_data *data, int *player_count, int *empty_spaces)
{
	int	i;
	int	j;

	*player_count = 0;
	*empty_spaces = 0;
	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width && data->map.grid[i][j])
		{
			if (is_player_char(data->map.grid[i][j]))
				(*player_count)++;
			if (data->map.grid[i][j] == '0')
				(*empty_spaces)++;
			j++;
		}
		i++;
	}
}

/**
 * Alloue la mémoire pour le grid de la map
 */
void	allocate_map_grid(t_data *data)
{
	//int i;
	if (data->map.height <= 0 || data->map.width <= 0)
		print_error("Invalid map dimensions", data);
	data->map.grid = malloc(sizeof(char *) * (data->map.height + 1));
	if (!data->map.grid)
		print_error("Memory allocation failed for map grid", data);
	//i = 0;
	//while (i < data->map.height)
	//{
	//	data->map.grid[i] = malloc(sizeof(char) * (data->map.width + 1));
	//	if (!data->map.grid[i])
	//		print_error("Memory allocation failed for map row", data);
	//	i++;
	//}
	//data->map.grid[i] = NULL;
}

int	get_line_length_without_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	return (len);
}
