#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "structures.h"

/*
** ============================================================================
** TYPES D'ERREURS
** ============================================================================
*/

typedef enum e_error_type
{
	ERR_ARGS,
	ERR_FILE,
	ERR_CONFIG,
	ERR_TEXTURE,
	ERR_COLOR,
	ERR_MAP,
	ERR_MEMORY
}	t_error_type;

static char	*g_error_messages[] = {
	"Invalid arguments",
	"File error",
	"Configuration error",
	"Texture error",
	"Color error",
	"Map error",
	"Memory allocation failed"
};

/*
** ============================================================================
** FONCTIONS DE LIBÉRATION MÉMOIRE
** ============================================================================
*/

void	free_texture_paths(t_data *data)
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

void	free_map_grid(t_data *data)
{
	int	i;

	if (data->map.grid)
	{
		i = 0;
		while (i < data->map.height && data->map.grid[i])
		{
			free(data->map.grid[i]);
			data->map.grid[i] = NULL;
			i++;
		}
		free(data->map.grid);
		data->map.grid = NULL;
	}
	data->map.height = 0;
	data->map.width = 0;
}

void	free_mlx_textures(t_data *data)
{
	if (data->textures.north.img)
	{
		mlx_destroy_image(data->mlx.mlx, data->textures.north.img);
		data->textures.north.img = NULL;
	}
	if (data->textures.south.img)
	{
		mlx_destroy_image(data->mlx.mlx, data->textures.south.img);
		data->textures.south.img = NULL;
	}
	if (data->textures.west.img)
	{
		mlx_destroy_image(data->mlx.mlx, data->textures.west.img);
		data->textures.west.img = NULL;
	}
	if (data->textures.east.img)
	{
		mlx_destroy_image(data->mlx.mlx, data->textures.east.img);
		data->textures.east.img = NULL;
	}
}

void	free_mlx_resources(t_data *data)
{
	if (data->mlx.img)
	{
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
		data->mlx.img = NULL;
	}
	free_mlx_textures(data);
	if (data->mlx.win)
	{
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
		data->mlx.win = NULL;
	}
	if (data->mlx.mlx)
	{
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
		data->mlx.mlx = NULL;
	}
}

void	cleanup_all_resources(t_data *data)
{
	if (!data)
		return ;
	free_texture_paths(data);
	free_map_grid(data);
	free_mlx_resources(data);
}

/*
** ============================================================================
** FONCTION PRINCIPALE D'ERREUR
** ============================================================================
*/

void	error_exit(t_data *data, t_error_type type, const char *details)
{
	printf("Error\n");
	if (details)
		printf("%s: %s\n", g_error_messages[type], details);
	else
		printf("%s\n", g_error_messages[type]);
	cleanup_all_resources(data);
	exit(1);
}

/*
** ============================================================================
** FONCTION ERROR_MEMORY
** ============================================================================
*/

void	error_memory(t_data *data, const char *details)
{
	error_exit(data, ERR_MEMORY, details);
}

/*
** ============================================================================
** AUTRES FONCTIONS D'ERREUR
** ============================================================================
*/

void	error_args(t_data *data, const char *details)
{
	error_exit(data, ERR_ARGS, details);
}

void	error_file(t_data *data, const char *details)
{
	error_exit(data, ERR_FILE, details);
}

void	error_config(t_data *data, const char *details)
{
	error_exit(data, ERR_CONFIG, details);
}

void	error_texture(t_data *data, const char *details)
{
	error_exit(data, ERR_TEXTURE, details);
}

void	error_color(t_data *data, const char *details)
{
	error_exit(data, ERR_COLOR, details);
}

void	error_map(t_data *data, const char *details)
{
	error_exit(data, ERR_MAP, details);
}

/*
** ============================================================================
** FONCTIONS SÉCURISÉES
** ============================================================================
*/

void	*safe_malloc(t_data *data, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		error_memory(data, "Failed to allocate memory");
	return (ptr);
}

void	*safe_calloc(t_data *data, size_t count, size_t size)
{
	void	*ptr;

	ptr = calloc(count, size);
	if (!ptr)
		error_memory(data, "Failed to allocate zeroed memory");
	return (ptr);
}

char	*safe_strdup(t_data *data, const char *str)
{
	char	*dup;

	if (!str)
		error_memory(data, "Cannot duplicate NULL string");
	dup = strdup(str);
	if (!dup)
		error_memory(data, "Failed to duplicate string");
	return (dup);
}

/*
** ============================================================================
** FONCTIONS DE TEST
** ============================================================================
*/

void	test_safe_malloc(t_data *data)
{
	char	*ptr;

	printf("Testing safe_malloc...\n");
	ptr = safe_malloc(data, 1024);
	printf("✓ safe_malloc successful: %p\n", ptr);
	free(ptr);
}

void	test_safe_strdup(t_data *data)
{
	char	*dup;

	printf("Testing safe_strdup...\n");
	dup = safe_strdup(data, "Hello World");
	printf("✓ safe_strdup successful: %s\n", dup);
	free(dup);
}

void	test_error_memory(t_data *data)
{
	printf("Testing error_memory (this will exit)...\n");
	error_memory(data, "This is a test memory error");
}

/*
** ============================================================================
** FONCTION PRINCIPALE DE TEST
** ============================================================================
*/

int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	data.colors.floor_r = -1;
	data.colors.ceiling_r = -1;
	printf("=== TEST DU SYSTÈME D'ERREUR ===\n");
	if (argc > 1 && strcmp(argv[1], "--test-error") == 0)
	{
		printf("Allocation de test...\n");
		data.textures.north_path = safe_strdup(&data, "test_texture.xpm");
		data.map.grid = safe_malloc(&data, sizeof(char *) * 10);
		printf("✓ Allocations réussies\n");
		printf("Déclenchement d'une erreur volontaire...\n");
		test_error_memory(&data);
	}
	else
	{
		printf("Tests des fonctions sécurisées...\n");
		test_safe_malloc(&data);
		test_safe_strdup(&data);
		printf("✓ Tous les tests passés\n");
		printf("Usage: %s --test-error (pour tester le nettoyage)\n", argv[0]);
	}
	cleanup_all_resources(&data);
	return (0);
}

/*
** ============================================================================
** EXEMPLE D'UTILISATION
** ============================================================================
**
** void assign_texture_path(t_data *data, char *id, char *path)
** {
**     if (ft_strncmp(id, "NO", 2) == 0)
**     {
**         if (data->textures.north_path)
**             error_texture(data, "Duplicate NO texture definition");
**         data->textures.north_path = safe_strdup(data, path);
**         // Si safe_strdup échoue, error_memory() va :
**         // 1. Afficher "Error\nMemory allocation failed: Failed to duplicate string"
**         // 2. Libérer toute la mémoire déjà allouée
**         // 3. Exit(1)
**     }
**     // ... autres textures
** }
**
** AVANTAGES :
** - Pas de fuites mémoire en cas d'erreur
** - Messages d'erreur standardisés
** - Nettoyage automatique des ressources
** - Code plus sûr et plus maintenable
*/