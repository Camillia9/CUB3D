#include "../includes/cub3d.h"

int is_texture_line(char *line)
{
    return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
            ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0);
}

int is_color_line(char *line)
{
    return (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

/**
 * Supprime les espaces en début et fin de chaîne
 */
char *trim_whitespace(char *str)
{
    char *end;
    
    // Supprimer les espaces de début
    while (*str == ' ' || *str == '\t')
        str++;
    
    if (*str == 0)
        return str;
    
    // Supprimer les espaces de fin
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r'))
        end--;
    
    *(end + 1)= '\0';
    return str;
}

/**
 * Ignore les espaces et tabulations au début d'une ligne
 */
char *skip_whitespace(char *line)
{
    while (*line && (*line == ' ' || *line == '\t'))
        line++;
    return (line);
}

/**
 * Vérifie si une ligne est vide ou ne contient que des espaces
 */
int is_empty_line(char *line)
{
    char *trimmed;
	trimmed = skip_whitespace(line);
    return (*trimmed == '\0' || *trimmed == '\n');
}

/**
 * Identifie le type de texture et vérifie les doublons
 */
int identify_texture_type(char *line, t_data *data)
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
 */
char *extract_texture_path(char *line, int texture_type, t_data *data)
{
    char *path_start;
    char *path_end;
    char *path;
    int path_len;
    int i;
    (void) texture_type;

    path_start = skip_whitespace(line + 2);
    path_end = path_start;
    while (*path_end && *path_end != '\n' && *path_end != ' ' && *path_end != '\t')
        path_end++;
    
    path_len = path_end - path_start;
    if (path_len == 0)
        print_error("Missing texture path", data);
        
    // Vérifier qu'il n'y a pas de caractères supplémentaires après le chemin
    char *remaining = skip_whitespace(path_end);
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
void assign_texture_to_data(t_data *data, char *path, int texture_type)
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

/**
 * Parse une ligne de texture (NO, SO, WE, EA)
 */
int parse_texture_line(char *line, t_data *data)
{
    char *trimmed;
    int texture_type;
    char *path;

    trimmed = skip_whitespace(line);
    texture_type = identify_texture_type(trimmed, data);
    
    if (texture_type == 0)
        return (0);
    
    path = extract_texture_path(trimmed, texture_type, data);
    
    if (!check_file_access(path))
    {
        free(path);
        print_error("Texture file does not exist or is not readable", data);
    }
    
    assign_texture_to_data(data, path, texture_type);
    return (1);
}
/**
 * Vérifie que toutes les configurations sont complètes
 */
int check_config_complete(t_data *data)
{
    if (!data->textures.north_path || !data->textures.south_path || 
        !data->textures.west_path || !data->textures.east_path)
        //print_error("Missing texture configuration");
        return 0;

    if (data->colors.floor_r == -1 || data->colors.floor_g == -1 || 
        data->colors.floor_b == -1)
        //print_error("Missing floor color configuration");
        return 0;
    
    if (data->colors.ceiling_r == -1 || data->colors.ceiling_g == -1 || 
        data->colors.ceiling_b == -1)
        //print_error("Missing ceiling color configuration");
        return 0;
    
    return (1);
}
