#include "../includes/cub3d.h"

/**
 * Identifie le type de texture et vérifie les doublons
 */
int	identify_texture_type(char *line, t_data *data)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (data->textures.north_path)
			print_error("Duplicate North texture", data);
		return (NORTH);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (data->textures.south_path)
			print_error("Duplicate South texture", data);
		return (SOUTH);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (data->textures.west_path)
			print_error("Duplicate West texture", data);
		return (WEST);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (data->textures.east_path)
			print_error("Duplicate East texture", data);
		return (EAST);
	}
	return (0);
}

/**
 * Extrait le chemin de la texture depuis la ligne
 * Vérifier qu'il n'y a pas de caractères supplémentaires après le chemin
 */
char	*extract_texture_path(char *line, t_data *data)
{
	char	*path_start;
	char	*path_end;
	char	*path;
	int		path_len;
	char	*remaining;
	int		i;

	path_start = skip_whitespace(line + 2);
	path_end = path_start;
	while (*path_end && *path_end != '\n' && *path_end != ' ' && *path_end != '\t')
		path_end++;
	path_len = path_end - path_start;
	if (path_len == 0)
		print_error("Missing texture path", data);
	remaining = skip_whitespace(path_end);
	if (*remaining && *remaining != '\n')
		print_error("Invalid syntax: extra characters after texture path", data);
	path = safe_malloc(data, path_len + 1);
	i = 0;
	while (i < path_len)
	{
		path[i] = path_start[i];
		i++;
	}
	path[i] = '\0';
	return (path);
}

/**
 * Assigne la texture au bon champ de la structure
 */
void	assign_texture_to_data(t_data *data, char *path, int texture_type)
{
	if (texture_type == NORTH)
		data->textures.north_path = path;
	else if (texture_type == SOUTH)
		data->textures.south_path = path;
	else if (texture_type == WEST)
		data->textures.west_path = path;
	else if (texture_type == EAST)
		data->textures.east_path = path;
}

static void	validate_texture_path(char *path, t_data *data)
{
	int	len;
	int	fd;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		free(path);
		print_error("Texture must have .xpm extension", data);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		free(path);
		print_error("Cannot open texture file", data);
	}
	close(fd);
}

/**
 * Parse une ligne de texture (NO, SO, WE, EA)
 */
int	parse_texture_line(char *line, t_data *data)
{
	char	*trimmed;
	int		texture_type;
	char	*path;

	trimmed = skip_whitespace(line);
	texture_type = identify_texture_type(trimmed, data);
	if (texture_type == 0)
		return (0);
	path = extract_texture_path(trimmed, data);
	validate_texture_path(path, data);
	assign_texture_to_data(data, path, texture_type);
	return (1);
}
