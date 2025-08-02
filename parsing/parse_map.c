#include "../includes/cub3d.h"

static void	calculate_map_dimensions(t_data *data, int start)
{
	int		i;
	int		len;
	char	*line;

	data->map.height = 0;
	data->map.width = 0;
	i = start;
	while (data->file_content[i])
	{
		line = data->file_content[i];
		if (!is_valid_map_line(line))
			break ;
		len = get_line_length_without_newline(line);
		if (len > data->map.width)
			data->map.width = len;
		data->map.height++;
		i++;
	}
	if (data->map.height == 0)
		print_error("Empty map", data);
}

static char	*create_normalized_line(char *line, int target_width, t_data *data)
{
	char	*normalized;
	int		i;
	int		line_len;

	line_len = get_line_length_without_newline(line);
	normalized = malloc(target_width + 1);
	if (!normalized)
		print_error("Memory allocation failed", data);
	i = 0;
	while (i < line_len && i < target_width)
	{
		normalized[i] = line[i];
		i++;
	}
	while (i < target_width)
	{
		normalized[i] = '2';
		i++;
	}
	normalized[i] = '\0';
	return (normalized);
}

static void	fill_map_grid(t_data *data, int start)
{
	int		i;
	int		row;
	char	*line;

	i = start;
	row = 0;
	while (row < data->map.height && data->file_content[i])
	{
		line = data->file_content[i];
		if (!is_valid_map_line(line))
			break ;
		data->map.grid[row] = create_normalized_line(line, data->map.width,
				data);
		row++;
		i++;
	}
	data->map.grid[row] = NULL;
}

void	parse_map_section(t_data *data, int start_index)
{
	calculate_map_dimensions(data, start_index);
	allocate_map_grid(data);
	fill_map_grid(data, start_index);
}

static void	validate_map_elements(t_data *data)
{
	int	player_count;
	int	empty_count;

	if (!data->map.grid || data->map.height == 0 || data->map.width == 0)
		print_error("Invalid map structure", data);
	count_map_elements(data, &player_count, &empty_count);
	if (player_count == 0)
		print_error("No player found in map", data);
	if (player_count > 1)
		print_error("Multiple players found in map", data);
	if (empty_count == 0)
		print_error("No empty spaces in map", data);
	find_player_position(data);
}

void	validate_map(t_data *data)
{
	validate_map_elements(data);
	validate_map_closure(data);
	ft_putstr_fd("✓ Map validation successful\n", 1);
}

void	free_temp_grid(char **grid, int height)
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

char	**duplicate_grid(t_data *data)
{
	char	**temp;
	int		i;

	temp = malloc(sizeof(char *) * (data->map.height + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < data->map.height)
	{
		temp[i] = ft_strdup(data->map.grid[i]);
		if (!temp[i])
		{
			free_temp_grid(temp, i);
			return (NULL);
		}
		i++;
	}
	temp[i] = NULL;
	return (temp);
}
