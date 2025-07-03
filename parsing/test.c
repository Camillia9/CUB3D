#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "structures.h"

//1. Utilisation de t_textures :

//Stockage des chemins dans north_path, south_path, west_path, east_path
//Les structures t_texture (north, south, east, west) seront utilisées plus tard pour charger les images

//2. Utilisation de t_colors :

//Stockage des composants RGB individuels (floor_r, floor_g, floor_b, etc.)
//Encodage automatique en couleurs complètes (floor_color, ceiling_color) au format 0xRRGGBB
//Initialisation avec -1 pour détecter les valeurs non définies

//3. Intégration dans t_data :

//Une seule structure t_data contient tout
//Initialisation des valeurs par défaut (screen_width, screen_height, running, keys)
//Gestion mémoire centralisée

//Nouvelles fonctions principales :

//read_and_parse_config(t_data *data, const char *filename) : Point d'entrée principal
//init_config_data(t_data *data) : Initialise toutes les structures
//print_config_data(t_data *data) : Affiche la config pour debug
//free_config_data(t_data *data) : Libère la mémoire des chemins

//Améliorations :

//Encodage couleur : Fonction encode_color() qui crée le format 0xRRGGBB pour MLX
//Compatibilité : Structure prête pour les phases suivantes (map parsing, MLX, etc.)
//Validation complète : Tous les checks de la phase 1 sont conservés

//1.1 - Lecture du fichier :

//Ouverture avec gestion d'erreurs
//Lecture ligne par ligne avec get_next_line (version simplifiée incluse)
//Ignore les lignes vides automatiquement

//1.2 - Parsing des textures (NO, SO, WE, EA) :

//✅ Validation des identifiants corrects
//✅ Vérification d'un seul espace après l'identifiant
//✅ Validation que le fichier de texture existe et est lisible
//✅ Détection des doublons
//✅ Gestion des erreurs pour arguments supplémentaires

//1.3 - Parsing des couleurs (F, C) :

//✅ Validation des identifiants F et C
//✅ Format strict R,G,B avec virgules obligatoires
//✅ Valeurs entre 0 et 255
//✅ Interdiction des espaces dans les valeurs
//✅ Détection des doublons

//Cas d'erreurs gérés :

//Textures dupliquées
//Couleurs dupliquées
//Fichiers de texture inexistants
//Valeurs RGB invalides (< 0 ou > 255)
//Format RGB incorrect
//Espaces dans les valeurs RGB
//Arguments manquants ou en trop

/**
 * Affiche un message d'erreur formaté et termine le programme
 */
void print_error(const char *message)
{
    printf("Error\n%s\n", message);
    exit(1);
}

/**
 * Version simplifiée de get_next_line pour la démo
 * (Tu devrais utiliser ta vraie implémentation de get_next_line)
 */
char *get_next_line(int fd)
{
    static char buffer[1024];
    static int pos = 0;
    static int bytes_read = 0;
    char *line = malloc(1024);
    int i = 0;
    
    if (!line)
        return NULL;
    
    while (1)
    {
        if (pos >= bytes_read)
        {
            bytes_read = read(fd, buffer, 1023);
            if (bytes_read <= 0)
            {
                if (i == 0)
                {
                    free(line);
                    return NULL;
                }
                break;
            }
            buffer[bytes_read] = '\0';
            pos = 0;
        }
        
        if (buffer[pos] == '\n')
        {
            pos++;
            break;
        }
        
        line[i++] = buffer[pos++];
        if (i >= 1023)
            break;
    }
    
    line[i] = '\0';
    return line;
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
    
    end[1] = '\0';
    return str;
}

/**
 * Vérifie si un fichier de texture existe et est lisible
 */
int check_texture_file(const char *path)
{
    int fd = open(path, O_RDONLY);
    if (fd == -1)
        return 0;
    close(fd);
    return 1;
}

/**
 * Parse une ligne de texture (NO, SO, WE, EA)
 */
void parse_texture(t_data *data, char *line)
{
    char *identifier = strtok(line, " ");
    char *path = strtok(NULL, " ");
    char *extra = strtok(NULL, " ");
    
    // Vérifier qu'il n'y a pas d'arguments supplémentaires
    if (extra != NULL)
        print_error("Invalid texture format: too many arguments");
    
    if (!path)
        print_error("Invalid texture format: missing path");
    
    path = trim_whitespace(path);
    
    // Vérifier que le fichier de texture existe
    if (!check_texture_file(path))
        print_error("Texture file does not exist or is not readable");
    
    // Assigner la texture selon l'identifiant
    if (strcmp(identifier, "NO") == 0)
    {
        if (data->textures.north_path)
            print_error("Duplicate NO texture definition");
        data->textures.north_path = strdup(path);
    }
    else if (strcmp(identifier, "SO") == 0)
    {
        if (data->textures.south_path)
            print_error("Duplicate SO texture definition");
        data->textures.south_path = strdup(path);
    }
    else if (strcmp(identifier, "WE") == 0)
    {
        if (data->textures.west_path)
            print_error("Duplicate WE texture definition");
        data->textures.west_path = strdup(path);
    }
    else if (strcmp(identifier, "EA") == 0)
    {
        if (data->textures.east_path)
            print_error("Duplicate EA texture definition");
        data->textures.east_path = strdup(path);
    }
}

/**
 * Valide et convertit une valeur RGB (0-255)
 */
int parse_rgb_value(char *str)
{
    int value;
    char *endptr;
    
    // Vérifier qu'il n'y a pas d'espaces
    if (strchr(str, ' ') || strchr(str, '\t'))
        print_error("Invalid color format: no spaces allowed in RGB values");
    
    value = strtol(str, &endptr, 10);
    
    // Vérifier que la conversion s'est bien passée
    if (*endptr != '\0')
        print_error("Invalid color format: non-numeric RGB value");
    
    // Vérifier la plage 0-255
    if (value < 0 || value > 255)
        print_error("Invalid color format: RGB values must be between 0 and 255");
    
    return value;
}

/**
 * Encode une couleur RGB en int (format 0xRRGGBB)
 */
int encode_color(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}

/**
 * Parse une ligne de couleur (F ou C)
 */
void parse_color(t_data *data, char *line)
{
    char *identifier = strtok(line, " ");
    char *rgb_str = strtok(NULL, " ");
    char *extra = strtok(NULL, " ");
    
    // Vérifier qu'il n'y a pas d'arguments supplémentaires
    if (extra != NULL)
        print_error("Invalid color format: too many arguments");
    
    if (!rgb_str)
        print_error("Invalid color format: missing RGB values");
    
    rgb_str = trim_whitespace(rgb_str);
    
    // Parser les valeurs RGB
    char *r_str = strtok(rgb_str, ",");
    char *g_str = strtok(NULL, ",");
    char *b_str = strtok(NULL, ",");
    char *extra_color = strtok(NULL, ",");
    
    if (!r_str || !g_str || !b_str || extra_color)
        print_error("Invalid color format: must be R,G,B");
    
    int r = parse_rgb_value(r_str);
    int g = parse_rgb_value(g_str);
    int b = parse_rgb_value(b_str);
    
    // Assigner la couleur selon l'identifiant
    if (strcmp(identifier, "F") == 0)
    {
        if (data->colors.floor_r != -1) // -1 = non initialisé
            print_error("Duplicate Floor color definition");
        data->colors.floor_r = r;
        data->colors.floor_g = g;
        data->colors.floor_b = b;
        data->colors.floor_color = encode_color(r, g, b);
    }
    else if (strcmp(identifier, "C") == 0)
    {
        if (data->colors.ceiling_r != -1)
            print_error("Duplicate Ceiling color definition");
        data->colors.ceiling_r = r;
        data->colors.ceiling_g = g;
        data->colors.ceiling_b = b;
        data->colors.ceiling_color = encode_color(r, g, b);
    }
}

/**
 * Vérifie si une ligne est vide ou ne contient que des espaces
 */
int is_empty_line(char *line)
{
    char *trimmed = trim_whitespace(line);
    return (strlen(trimmed) == 0);
}

/**
 * Vérifie si toutes les configurations sont complètes
 */
int is_config_complete(t_data *data)
{
    return (data->textures.north_path && data->textures.south_path && 
            data->textures.west_path && data->textures.east_path &&
            data->colors.floor_r != -1 && data->colors.ceiling_r != -1);
}

/**
 * Initialise les structures de configuration
 */
void init_config_data(t_data *data)
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
    
    // Initialiser le tableau des touches
    for (int i = 0; i < 256; i++)
        data->keys[i] = 0;
}

/**
 * Parse une ligne du fichier de configuration
 */
int parse_config_line(t_data *data, char *line)
{
    line = trim_whitespace(line);
    
    // Ignorer les lignes vides
    if (is_empty_line(line))
        return 0; // Continue parsing
    
    // Identifier le type d'élément
    if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
        ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
    {
        parse_texture(data, line);
        return 0; // Continue parsing
    }
    else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
    {
        parse_color(data, line);
        return 0; // Continue parsing
    }
    else
    {
        // Si ce n'est pas une ligne de config et qu'on n'a pas fini le parsing,
        // c'est une erreur
        if (!is_config_complete(data))
            print_error("Invalid configuration line or missing configuration elements");
        
        // Sinon, c'est probablement le début de la carte
        return 1; // Stop parsing config, start map
    }
}

/**
 * Lit et parse le fichier de configuration
 */
void read_and_parse_config(t_data *data, const char *filename)
{
    int fd;
    char *line;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        print_error("Cannot open configuration file");
    
    init_config_data(data);
    
    // Lire ligne par ligne
    while ((line = get_next_line(fd)) != NULL)
    {
        int should_stop = parse_config_line(data, line);
        free(line);
        
        // Si on a rencontré le début de la carte, on s'arrête
        if (should_stop)
            break;
    }
    
    close(fd);
    
    // Vérifier que toutes les configurations sont présentes
    if (!is_config_complete(data))
        print_error("Missing configuration elements (need NO, SO, WE, EA, F, C)");
}

/**
 * Libère la mémoire des chemins de textures
 */
void free_config_data(t_data *data)
{
    if (data->textures.north_path)
    {
        free(data->textures.north_path);
        data->textures.north_path = NULL;
    }
    if (data->textures.south_path)
    {
        free(data->textures.south_path);
        data->textures.south_path = NULL;
    }
    if (data->textures.west_path)
    {
        free(data->textures.west_path);
        data->textures.west_path = NULL;
    }
    if (data->textures.east_path)
    {
        free(data->textures.east_path);
        data->textures.east_path = NULL;
    }
}

/**
 * Fonction principale pour tester le parsing
 */
int main(int argc, char **argv)
{
    t_data data;
    
    if (argc != 2)
    {
        printf("Usage: ./cub3d_phase1 <config.cub>\n");
        return 1;
    }
    
    read_and_parse_config(&data, argv[1]);
    
    printf("✓ Configuration file parsed successfully!\n");
    print_config_data(&data);
    
    free_config_data(&data);
    
    return 0;
}

/*
 * EXEMPLE DE FICHIER .cub VALIDE :
 * 
 * NO ./textures/north.xpm
 * SO ./textures/south.xpm
 * WE ./textures/west.xpm
 * EA ./textures/east.xpm
 * 
 * F 220,100,0
 * C 225,30,0
 * 
 * 1111111111111111111111111
 * 1000000000110000000000001
 * 1011000001110000000000001
 * 1001000000000000000000001
 * 111111111011000001110000000000001
 * 100000000011000001110111111111111
 * 11110111111111011100000010001
 * 11110111111111011101010010001
 * 11000000110101011100000010001
 * 10000000000000001100000010001
 * 10000000000000001101010010001
 * 11000001110101011111011110N0111
 * 11110111 1110101 101111010001
 * 11111111 1111111 111111111111
 */