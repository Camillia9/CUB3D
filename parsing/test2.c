#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "structures.h"


//Fonctions créées pour respecter la norme :

//count_map_elements() : Compte joueurs et espaces vides
//find_player_position() : Trouve et sauvegarde la position du joueur
//validate_map_chars() : Valide tous les caractères de la map
//check_flood_borders() : Vérifie les bordures pour le flood-fill
//is_border_position() : Détermine si une position est en bordure
//check_unreachable_areas() : Vérifie les zones inaccessibles
//check_accessible_borders() : Valide les bordures accessibles
//validate_accessible_positions() : Valide toutes les positions accessibles

//3.1 - Validation de Base (validate_map_basic)
//✅ Map non vide : Vérifie height, width et grid
//✅ Exactement un joueur : Compte les N, S, E, W
//✅ Au moins un espace vide : Compte les '0'
//✅ Caractères valides : Seuls '0', '1', 'N', 'S', 'E', 'W', ' ' autorisés
//✅ Sauvegarde position joueur : Dans data->map.player_x/y/dir
//3.2 - Validation de Fermeture (validate_map_closure)
//✅ Algorithme flood-fill : Part de la position du joueur
//✅ Détection des bords : Vérifie si on atteint une bordure non-murée
//✅ Zones accessibles : S'assure que tout est connecté
//✅ Matrice de visite : Évite les boucles infinies
//3.3 - Validations Spécifiques (validate_map_specific)
//✅ Bords sécurisés : Espaces accessibles ne touchent pas les bordures
//✅ Joueur accessible : Position du joueur n'est pas un mur
//✅ Gestion des espaces : Les espaces en bordure sont correctement traités
//Fonctionnalités Utilitaires :

//print_map_debug() : Affiche la map avec numérotation pour debug
//create_test_map() : Crée une map de test valide
//is_valid_char(), is_player_char(), is_accessible_char() : Vérifications de caractères
//Gestion complète de la mémoire

void	print_error(const char *message)
{
	printf("Error\n%s\n", message);
	exit(1);
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || 
			c == 'E' || c == 'W' || c == ' ');
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_accessible_char(char c)
{
	return (c == '0' || is_player_char(c));
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

void	find_player_position(t_data *data)
{
	int	i;
	int	j;

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
			{
				data->map.player_x = j;
				data->map.player_y = i;
				data->map.player_dir = data->map.grid[i][j];
				return;
			}
			j++;
		}
		i++;
	}
}

void	validate_map_chars(t_data *data)
{
	int	i;
	int	j;

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
			if (!is_valid_char(data->map.grid[i][j]))
				print_error("Invalid character in map");
			j++;
		}
		i++;
	}
}

void	validate_map_basic(t_data *data)
{
	int	player_count;
	int	empty_spaces;

	if (data->map.height == 0 || data->map.width == 0 || !data->map.grid)
		print_error("Map is empty");
	validate_map_chars(data);
	count_map_elements(data, &player_count, &empty_spaces);
	if (player_count == 0)
		print_error("No player found in map (need N, S, E, or W)");
	if (player_count > 1)
		print_error("Multiple players found in map (only one allowed)");
	if (empty_spaces == 0)
		print_error("No empty spaces found in map (need at least one '0')");
	find_player_position(data);
	printf("✓ Basic validation passed: 1 player (%c) at (%d,%d), %d empty\n",
		data->map.player_dir, data->map.player_x, data->map.player_y,
		empty_spaces);
}

int	is_valid_position(t_data *data, int x, int y)
{
	if (y < 0 || y >= data->map.height)
		return (0);
	if (x < 0 || !data->map.grid[y])
		return (0);
	if (x >= (int)strlen(data->map.grid[y]))
		return (0);
	return (1);
}

char	get_char_at(t_data *data, int x, int y)
{
	if (!is_valid_position(data, x, y))
		return (' ');
	return (data->map.grid[y][x]);
}

int	is_border_position(t_data *data, int x, int y)
{
	if (x == 0 || y == 0 || y == data->map.height - 1)
		return (1);
	if (x == (int)strlen(data->map.grid[y]) - 1)
		return (1);
	return (0);
}

int	check_flood_borders(t_data *data, int x, int y)
{
	if (y < 0 || y >= data->map.height || x < 0)
		return (1);
	if (!data->map.grid[y] || x >= (int)strlen(data->map.grid[y]))
		return (1);
	return (0);
}

int	flood_fill_recursive(t_data *data, char **visited, int x, int y)
{
	char	current;
	int		problem;

	if (check_flood_borders(data, x, y))
		return (1);
	if (visited[y][x] || data->map.grid[y][x] == '1')
		return (0);
	current = data->map.grid[y][x];
	if (is_border_position(data, x, y) && current != '1')
		return (1);
	if (!is_accessible_char(current))
		return (0);
	visited[y][x] = 1;
	problem = 0;
	problem |= flood_fill_recursive(data, visited, x + 1, y);
	problem |= flood_fill_recursive(data, visited, x - 1, y);
	problem |= flood_fill_recursive(data, visited, x, y + 1);
	problem |= flood_fill_recursive(data, visited, x, y - 1);
	return (problem);
}

char	**create_visited_matrix(t_data *data)
{
	char	**visited;
	int		i;

	visited = malloc(sizeof(char *) * data->map.height);
	if (!visited)
		print_error("Memory allocation failed for visited matrix");
	i = 0;
	while (i < data->map.height)
	{
		visited[i] = calloc(data->map.width + 1, sizeof(char));
		if (!visited[i])
			print_error("Memory allocation failed for visited matrix row");
		i++;
	}
	return (visited);
}

void	free_visited_matrix(char **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

void	check_unreachable_areas(t_data *data, char **visited)
{
	int	i;
	int	j;

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
			if (is_accessible_char(data->map.grid[i][j]) && !visited[i][j])
				print_error("Map contains unreachable accessible areas");
			j++;
		}
		i++;
	}
}

void	validate_map_closure(t_data *data)
{
	char	**visited;
	int		problem;

	visited = create_visited_matrix(data);
	problem = flood_fill_recursive(data, visited, data->map.player_x,
			data->map.player_y);
	if (problem)
	{
		free_visited_matrix(visited, data->map.height);
		print_error("Map is not properly closed (player can reach borders)");
	}
	check_unreachable_areas(data, visited);
	free_visited_matrix(visited, data->map.height);
	printf("✓ Closure validation passed: map is properly enclosed\n");
}

void	check_accessible_borders(t_data *data, int i, int j)
{
	char	up;
	char	down;
	char	left;
	char	right;
	int		line_len;

	up = get_char_at(data, j, i - 1);
	down = get_char_at(data, j, i + 1);
	left = get_char_at(data, j - 1, i);
	right = get_char_at(data, j + 1, i);
	line_len = strlen(data->map.grid[i]);
	if (up == ' ' && (i == 0))
		print_error("Map has accessible area touching border");
	if (down == ' ' && (i == data->map.height - 1))
		print_error("Map has accessible area touching border");
	if (left == ' ' && (j == 0))
		print_error("Map has accessible area touching border");
	if (right == ' ' && (j == line_len - 1))
		print_error("Map has accessible area touching border");
}

void	validate_accessible_positions(t_data *data)
{
	int		i;
	int		j;
	char	current;

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
			current = data->map.grid[i][j];
			if (is_accessible_char(current))
				check_accessible_borders(data, i, j);
			j++;
		}
		i++;
	}
}

void	validate_map_specific(t_data *data)
{
	char	player_pos;

	validate_accessible_positions(data);
	player_pos = get_char_at(data, data->map.player_x, data->map.player_y);
	if (!is_player_char(player_pos))
		print_error("Player position is invalid");
	printf("✓ Specific validation passed: player accessible, borders secure\n");
}

void	print_map_debug(t_data *data)
{
	int	i;

	printf("\n=== MAP DEBUG ===\n");
	printf("Size: %dx%d\n", data->map.width, data->map.height);
	printf("Player: %c at (%d,%d)\n", data->map.player_dir,
		data->map.player_x, data->map.player_y);
	printf("Map content:\n");
	i = 0;
	while (i < data->map.height)
	{
		if (data->map.grid[i])
			printf("%2d: |%s|\n", i, data->map.grid[i]);
		else
			printf("%2d: |NULL|\n", i);
		i++;
	}
	printf("=================\n\n");
}

void	validate_complete_map(t_data *data)
{
	printf("Starting complete map validation...\n");
	validate_map_basic(data);
	validate_map_closure(data);
	validate_map_specific(data);
	printf("✓ Complete map validation successful!\n");
}

void	create_test_map(t_data *data)
{
	data->map.height = 5;
	data->map.width = 9;
	data->map.grid = malloc(sizeof(char *) * 6);
	data->map.grid[0] = strdup("111111111");
	data->map.grid[1] = strdup("100000001");
	data->map.grid[2] = strdup("1000N0001");
	data->map.grid[3] = strdup("100000001");
	data->map.grid[4] = strdup("111111111");
	data->map.grid[5] = NULL;
}

void	free_map(t_data *data)
{
	int	i;

	if (data->map.grid)
	{
		i = 0;
		while (i < data->map.height)
		{
			if (data->map.grid[i])
				free(data->map.grid[i]);
			i++;
		}
		free(data->map.grid);
		data->map.grid = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (argc == 2 && strcmp(argv[1], "--test") == 0)
	{
		printf("Creating test map...\n");
		create_test_map(&data);
	}
	else
	{
		printf("Usage: ./cub3d_phase3 --test\n");
		printf("(This version creates a test map for validation)\n");
		printf("In your full project, the map should be loaded from ");
		printf("parsing phase 2\n");
		return (1);
	}
	print_map_debug(&data);
	validate_complete_map(&data);
	free_map(&data);
	return (0);
}

/*
** EXEMPLES DE MAPS POUR TESTER :
**
** MAP VALIDE :
** 111111111
** 100000001
** 1000N0001
** 100000001
** 111111111
**
** MAP INVALIDE (non fermée) :
** 111111111
** 100000001
** 1000N000   <- Manque le mur de droite
** 100000001
** 111111111
**
** MAP INVALIDE (plusieurs joueurs) :
** 111111111
** 100000001
** 1000N0001
** 1000S0001
** 111111111
**
** MAP INVALIDE (pas d'espaces vides) :
** 111111111
** 111111111
** 1111N1111
** 111111111
** 111111111
*/