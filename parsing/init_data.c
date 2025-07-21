#include "../includes/cub3d.h"
#include "../Libft/get_next_line/get_next_line.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		print_error("Memory allocation failed", NULL);
	ft_memset(data, 0, sizeof(t_data));
	init_default_values(data);
	return (data);
}

/**
 * Initialise les structures de configuration
 */
void	init_default_values(t_data *data)
{
    // Initialiser les textures
    data->textures.north_path = NULL;
    data->textures.south_path = NULL;
    data->textures.west_path = NULL;
    data->textures.east_path = NULL;
    
    // Initialiser les couleurs avec -1 (non définies)
    data->colors.floor_r = -1;
    data->colors.floor_g = -1;
    data->colors.floor_b = -1;
    data->colors.ceiling_r = -1;
    data->colors.ceiling_g = -1;
    data->colors.ceiling_b = -1;
    data->colors.floor_color = 0;
    data->colors.ceiling_color = 0;
    
    // Initialiser d'autres valeurs par défaut si nécessaire
    data->screen_width = 800;   // Valeurs par défaut
    data->screen_height = 600;
    data->running = 1;

    data->map.player_x = -1;
	data->map.player_y = -1;
	data->map.player_dir = 0;
    
}

// Fonction pour compter les lignes
int count_lines(const char *filename)
{
    int fd;
    char *line;
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return -1;
    int count = 0;
    while ((line = get_next_line(fd)))
    {
        count++;
        free(line);
    }
    close(fd);
    return count;
}

// Lire le fichier entier dans un tableau de char*
char **read_file_into_array(const char *filename)
{
    int fd;
    int lines_count;
    char **lines;
    char *line;
    int i;

    lines_count = count_lines(filename);
    if (lines_count <= 0)
        return NULL;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return NULL;

    lines = malloc(sizeof(char *) * (lines_count + 1));
    if (!lines)
        return NULL;
    i = 0;
    while ((line = get_next_line(fd)))
    {
        lines[i++] = line;
    }
    lines[i] = NULL;
    close(fd);
    return lines;
}

