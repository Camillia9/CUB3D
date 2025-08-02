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
		{
			print_error("bad character in map\n", data);
		}
		len = get_line_length_without_newline(line);
		if (len > data->map.width)
			data->map.width = len;
		data->map.height++;
		i++;
	}
	if (data->map.height == 0)
		print_error("Empty map", data);
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
