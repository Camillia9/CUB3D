#include "../includes/cub3d.h"

/**
 * Affiche la configuration parsée (pour debug)
 */
void	print_config_data(t_data *data)
{
	printf("=== CONFIGURATION PARSED ===\n");
	printf("North texture: %s\n", data->textures.north_path);
	printf("South texture: %s\n", data->textures.south_path);
	printf("West texture: %s\n", data->textures.west_path);
	printf("East texture: %s\n", data->textures.east_path);
	printf("Floor color: RGB(%d,%d,%d) [0x%06X]\n",
		data->colors.floor_r, data->colors.floor_g, data->colors.floor_b,
		data->colors.floor_color);
	printf("Ceiling color: RGB(%d,%d,%d) [0x%06X]\n",
		data->colors.ceiling_r, data->colors.ceiling_g, data->colors.ceiling_b,
		data->colors.ceiling_color);
	printf("Screen size: %dx%d\n", data->screen_width, data->screen_height);
	printf("height = %d\n", data->map.height);
	printf("width = %d\n", data->map.width);
	printf("file : \n");
	print_map(data->file_content);
	printf("map : \n");
	print_map(data->map.grid);
	printf("============================\n");
}

void	print_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			write(1, &map[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
