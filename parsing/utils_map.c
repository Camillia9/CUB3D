#include "../includes/cub3d.h"

/**
 * Vérifie si un caractère est valide dans la map
 */
//int is_valid_map_char(char c)
//{
//    return (c == '0' || c == '1' || c == 'N' || c == 'S' || 
//            c == 'E' || c == 'W' || c == ' ');
//}
int	is_valid_map_line(char *line)
{
	int i = 0;

	while (line[i])
	{
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
		if (!data->map.grid[i])
		{
			i++;
			continue;
		}
		j = 0;
		while (data->map.grid[i][j])
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
 * Vérifie si un caractère est une direction de joueur
 */
int is_player_char(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/**
 * Calcule la largeur d'une ligne de map
 */
int get_line_width(char *line)
{
    int width;
    int i;

    if (!line)
        return (0);
    
    width = 0;
    i = 0;
    while (line[i] && line[i] != '\n')
    {
        width++;
        i++;
    }
    return (width);
}

/**
 * Alloue la mémoire pour le grid de la map
 */
void allocate_map_grid(t_data *data)
{
    int i;

    if (data->map.height <= 0 || data->map.width <= 0)
        print_error("Invalid map dimensions", data);
    
    data->map.grid = malloc(sizeof(char *) * (data->map.height + 1));
    if (!data->map.grid)
        print_error("Memory allocation failed for map grid", data);
    
    i = 0;
    while (i < data->map.height)
    {
        data->map.grid[i] = malloc(sizeof(char) * (data->map.width + 1));
        if (!data->map.grid[i])
            print_error("Memory allocation failed for map row", data);
        i++;
    }
    data->map.grid[i] = NULL;
}

///**
// * Compte les lignes de la map et trouve la largeur maximale
// */
//void calculate_map_dimensions(char *file_content, t_data *data, int *start_pos)
//{
//    char *current;
//    char *line;
//    int map_started;
//    int start_offset;

//    //current = skip_config_section(file_content);
//    map_started = 0;
//    start_offset = 0;
//    data->map.height = 0;
//    data->map.width = 0;
    
//    while (current && *current)
//    {
//        line = get_next_line_simulation(&current);
//        if (!line)
//            break;
        
//        if (!process_map_line(line, data, &map_started, &start_offset))
//        {
//            free(line);
//            break;
//        }
        
//        free(line);
//    }

//    if (start_offset)
//        *start_pos = current - file_content;
//    else
//        *start_pos = 0;
//}

/**
 * Vérifie si une ligne contient des caractères de map valides
 */
int is_map_line(char *line, t_data *data)
{
    int i;
    (void) data;

    if (!line || is_empty_line(line))
        return (0);
    
    i = 0;
    while (line[i] && line[i] != '\n')
    {
        //if (!is_valid_map_line(line[i]))
        //{
        //    //print_error("Invalid character in map", data);
        //    return (0);
        //}
            
        i++;
    }
    return (1);
}

/**
 * Met à jour les dimensions maximales de la map
 */
void update_map_dimensions(t_data *data, int line_width)
{
    data->map.height++;
    if (line_width > data->map.width)
        data->map.width = line_width;
}
/**
 * Traite une ligne potentielle de map
 */
int process_map_line(char *line, t_data *data, int *map_started, int *start_offset)
{
    int line_width;

    if (is_map_line(line, data))
    {
        if (!*map_started)
        {
            *map_started = 1;
            *start_offset = 1;
        }
        line_width = get_line_width(line);
        update_map_dimensions(data, line_width);
        return (1);
    }
    else if (*map_started)
    {
        return (0); // Fin de la map
    }
    return (1); // Continue
}


void	*safe_malloc(t_data *data, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
    {
	    print_error("Failed to allocate memory", data);
    }

	return (ptr);
}
