#include "../includes/cub3d.h"

int	check_xpm_extension(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".xpm", 4) != 0)
		return (0);
	return (1);
}

void	validate_texture_file(t_data *data, char *path)
{
	if (!path)
		print_error("Missing texture path", data);
	if (!check_xpm_extension(path))
		print_error("Texture file must have .xpm extension", data);
	if (!check_file_access(path))
		print_error("Texture file does not exist or is not readable", data);
	//if (!check_xpm_header(path))
	//	error_texture(data, "Invalid XPM file format (missing XPM header)"); c trop header ca veut dire lit la photo et le contenu des lignes de l'image
}


///**
// * Lit et parse le fichier de configuration
// */
//void read_and_parse_config(t_data *data, char *filename)
//{
//    int fd;
//    char *line;
//	int should_stop;
    
//    fd = open(filename, O_RDONLY);
//    if (fd == -1)
//        print_error("Cannot open configuration file");
    
//    init_config_data(data);
    
//    // Lire ligne par ligne
//	line = get_next_line(fd);
//    while (line != NULL)
//    {
//        should_stop = parse_config_line(data, line);
//        free(line);
        
//        // Si on a rencontré le début de la carte, on s'arrête
//        if (should_stop)
//            break;
//    }
    
//    close(fd);
    
//    // Vérifier que toutes les configurations sont présentes
//    if (!is_config_complete(data))
//        print_error("Missing configuration elements (need NO, SO, WE, EA, F, C)");
//}

//int is_texture_line(char *line)
//{
//    return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
//            ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0);
//}

//int is_color_line(char *line)
//{
//    return (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
//}

//int parse_config_line(t_data *data, char *line)
//{
//    line = trim_whitespace(line);
//    if (is_empty_line(line))
//        return 0;
//    if (is_texture_line(line))
//    {
//        parse_texture(data, line);
//        return 0;
//    }
//    if (is_color_line(line))
//    {
//        parse_color(data, line);
//        return 0;
//    }
//    if (!is_config_complete(data))
//        print_error("Invalid configuration line or missing configuration elements");
//    return 1;
//}


void	validate_all_textures(t_data *data)
{
	if (!data->textures.north_path)
		print_error("Missing NO texture", data);
	if (!data->textures.south_path)
		print_error("Missing SO texture", data);
	if (!data->textures.west_path)
		print_error("Missing WE texture", data);
	if (!data->textures.east_path)
		print_error("Missing EA texture", data);
	validate_texture_file(data, data->textures.north_path);
	validate_texture_file(data, data->textures.south_path);
	validate_texture_file(data, data->textures.west_path);
	validate_texture_file(data, data->textures.east_path);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}
//int	find_identifier_end(char *line)
//{
//	int	i;

//	i = 0;
//	while (line[i] && !is_whitespace(line[i]))
//		i++;
//	return (i);
//}

//int	skip_whitespace(char *line, int start)
//{
//	while (line[start] && is_whitespace(line[start]))
//		start++;
//	return (start);
//}

//int	find_path_end(char *line, int start)
//{
//	int	end;

//	end = start;
//	while (line[end] && line[end] != ' ' && line[end] != '\t' 
//		&& line[end] != '\n' && line[end] != '\r')
//		end++;
//	return (end);
//}

//void	assign_texture_path(t_data *data, char *id, char *path)
//{
//	if (ft_strncmp(id, "NO", 2) == 0)
//	{
//		if (data->textures.north_path)
//			error_texture(data, "Duplicate NO texture definition");
//		data->textures.north_path = safe_strdup(data, path);
//	}
//	else if (ft_strncmp(id, "SO", 2) == 0)
//	{
//		if (data->textures.south_path)
//			error_texture(data, "Duplicate SO texture definition");
//		data->textures.south_path = safe_strdup(data, path);
//	}
//	else if (ft_strncmp(id, "WE", 2) == 0)
//	{
//		if (data->textures.west_path)
//			error_texture(data, "Duplicate WE texture definition");
//		data->textures.west_path = safe_strdup(data, path);
//	}
//	else if (ft_strncmp(id, "EA", 2) == 0)
//	{
//		if (data->textures.east_path)
//			error_texture(data, "Duplicate EA texture definition");
//		data->textures.east_path = safe_strdup(data, path);
//	}
//	else
//		error_texture(data, "Invalid texture identifier");
//}

//void	parse_texture(t_data *data, char *line)
//{
//	int		id_end;
//	int		path_start;
//	int		path_end;
//	int		extra_check;
//	char	identifier[3];
//	char	*path;

//	id_end = find_identifier_end(line);
//	if (id_end != 2)
//		print_error("Invalid texture identifier");
//	ft_strncpy(identifier, line, 2);
//	identifier[2] = '\0';
//	path_start = skip_whitespace(line, id_end);
//	if (!line[path_start])
//		print_error("Missing texture path");
//	path_end = find_path_end(line, path_start);
//	extra_check = skip_whitespace(line, path_end);
//	if (line[extra_check])
//		print_error("Too many arguments");
//	path = ft_substr(line, path_start, path_end - path_start);
//	if (!path)
//		error_memory(data, "Failed to extract path");
//	validate_texture_file(data, path);
//	assign_texture_path(data, identifier, path);
//	free(path);
//}

//void	parse_texture_simple(t_data *data, char *line)
//{
//	int		i;
//	char	identifier[3];
//	char	*path;
//	int		path_start;
//	int		path_end;

//	// 1. Skip les espaces du début
//	i = 0;
//	while (line[i] == ' ' || line[i] == '\t')
//		i++;
	
//	// 2. Lire l'identifiant (2 caractères)
//	if (!line[i] || !line[i + 1])
//		return ; // Pas assez de caractères, ignore la ligne
//	identifier[0] = line[i];
//	identifier[1] = line[i + 1];
//	identifier[2] = '\0';
	
//	// 3. Vérifier que c'est un identifiant valide
//	if (ft_strncmp(identifier, "NO", 2) != 0 && 
//		ft_strncmp(identifier, "SO", 2) != 0 &&
//		ft_strncmp(identifier, "WE", 2) != 0 && 
//		ft_strncmp(identifier, "EA", 2) != 0)
//		return ; // Pas un identifiant texture, ignore la ligne
	
//	// 4. Vérifier qu'il y a un espace après l'identifiant
//	i += 2;
//	if (line[i] != ' ' && line[i] != '\t')
//		print_error("Invalid texture format");
	
//	// 5. Skip les espaces après l'identifiant
//	while (line[i] == ' ' || line[i] == '\t')
//		i++;
	
//	// 6. Extraire le chemin jusqu'à la fin de ligne
//	if (!line[i])
//		print_error("Missing texture path");
//	path_start = i;
//	while (line[i] && line[i] != ' ' && line[i] != '\t' && 
//		   line[i] != '\n' && line[i] != '\r')
//		i++;
//	path_end = i;
	
//	// 7. Vérifier qu'il n'y a rien après le chemin
//	while (line[i] == ' ' || line[i] == '\t')
//		i++;
//	if (line[i] && line[i] != '\n' && line[i] != '\r')
//		print_error("Too many arguments", data);
	
//	// 8. Créer le chemin
//	path = ft_substr(line, path_start, path_end - path_start);
//	if (!path)
//		error_memory(data, "Failed to extract path");
	
//	// 9. Valider et assigner
//	validate_texture_file(data, path);
//	assign_texture_path(data, identifier, path);
//	free(path);
//}

void	parse_texture(t_data *data, char *line)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		line += 3;
		while (*line == ' ')
			line++;
		if (data->textures.north_path)
			print_error("Texture NO déjà définie", data);
		data->textures.north_path = ft_strdup(line);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		line += 3;
		while (*line == ' ')
			line++;
		if (data->textures.south_path)
			print_error("Texture SO déjà définie", data);
		data->textures.south_path = ft_strdup(line);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		line += 3;
		while (*line == ' ')
			line++;
		if (data->textures.west_path)
			print_error("Texture WE déjà définie", data);
		data->textures.west_path = ft_strdup(line);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		line += 3;
		while (*line == ' ')
			line++;
		if (data->textures.east_path)
			print_error("Texture EA déjà définie", data);
		data->textures.east_path = ft_strdup(line);
	}
	else
		print_error("Identifiant de texture inconnu", data);
}

char	*fill_line(char *line, int width, t_data *data)
{
	char	*new;
	int		i;
    
    i = 0;
    new = safe_malloc(data, width + 1);
	while (line[i])
	{
        new[i] = line[i];
		i++;
	}
	while (i < width)
		new[i++] = '2';
	new[i] = '\0';
	return (new);
}
