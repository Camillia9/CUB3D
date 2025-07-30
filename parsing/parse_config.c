#include "../includes/cub3d.h"

/**
 * Parse une ligne de configuration (texture ou couleur)
 */
static int	parse_config_element(char *trimmed, t_data *data)
{
	if (is_texture_line(trimmed))
	{
		parse_texture_line(trimmed, data);
		return (1);
	}
	if (is_color_line(trimmed))
	{
		parse_color_line(trimmed, data);
		return (1);
	}
	return (0);
}

/**
 * Trouve l'index de début de la map
 */
static int	find_map_start_index(t_data *data)
{
	char	*trimmed;
	int		i;

	if (!data->file_content)
		print_error("No file content loaded", data);
	i = 0;
	while (data->file_content[i])
	{
		if (!data->file_content[i])
			break ;
		trimmed = trim_whitespace(data->file_content[i]);
		if (is_empty_line(trimmed))
		{
			i++;
			continue ;
		}
		if (parse_config_element(trimmed, data))
		{
			i++;
			continue ;
		}
		if (check_config_complete(data) && is_valid_map_line(trimmed))
			return (i);
		print_error("Invalid configuration line", data);
	}
	return (-1);
}

/**
 * Calcule les dimensions de la map
 * Exclure le \n du calcul
 */
static void	calculate_map_dimensions(char **map_lines, t_data *data)
{
	char	*trimmed;
	int		i;
	int		line_len;

	data->map.height = 0;
	data->map.width = 0;
	i = 0;
	while (map_lines[i])
	{
		//trimmed = trim_whitespace(map_lines[i]);
		trimmed = map_lines[i];
		//if (is_empty_line(trimmed))
		//{
		//	print_error("erreur map\n", data);
		//	//break ;
		//}
		if (!is_valid_map_line(trimmed))
			print_error("Invalid character in map", data);
		line_len = ft_strlen(trimmed);
		 if (line_len > 0 && trimmed[line_len - 1] == '\n')
            line_len--;
		if (line_len > data->map.width)
			data->map.width = line_len;
		data->map.height++;
		i++;
	}
}

/**
 * Alloue et remplit la grille de la map
 */
static void	fill_map_grid(char **map_lines, t_data *data)
{
	int		i;
	int		map_row;

	data->map.grid = safe_malloc(data, sizeof(char *) * (data->map.height + 1));
	i = 0;
	map_row = 0;
	while (map_lines[i] && map_row < data->map.height)
	{
		data->map.grid[map_row] = fill_line(map_lines[i], data->map.width, data);
		map_row++;
		i++;
	}
	data->map.grid[map_row] = NULL;
}

/**
 * Parse la map à partir des lignes restantes
 */
void	parse_map_from_lines(char **map_lines, t_data *data)
{
	calculate_map_dimensions(map_lines, data);
	if (data->map.height == 0)
		print_error("Empty map\n", data);
	fill_map_grid(map_lines, data);
}

/**
 * Parse la configuration à partir du tableau de lignes
 */
void	parse_configuration(t_data *data)
{
	int	map_start_index;

	map_start_index = find_map_start_index(data);
	if (!check_config_complete(data))
		print_error("Incomplete configuration before map", data);
	if (map_start_index == -1)
		print_error("No map found in file", data);
	parse_map_from_lines(data->file_content + map_start_index, data);
}

///**
// * Fonction principale qui remplace read_and_parse_config
// */
//void	read_and_parse_config(t_data *data, char *filename)
//{
//	data->file_content = read_entire_file(filename, data);
//	printf("✓ File read successfully\n");
//	parse_configuration(data);
//	printf("✓ Configuration parsed successfully\n");
//}
