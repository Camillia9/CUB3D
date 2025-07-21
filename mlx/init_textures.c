#include "../includes/cub3d.h"

int	load_texture(t_data *data, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(data->mlx.mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
	{
		printf("Error\nCannot load texture: %s\n", path);
		return (0);
	}
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_length, &texture->endian);
	if (!texture->data)
	{
		printf("Error\nCannot get texture data: %s\n", path);
		mlx_destroy_image(data->mlx.mlx, texture->img);
		return (0);
	}
	texture->path = path;
	return (1);
}

int load_all_textures(t_data *data)
{
	if (!load_texture(data, &data->textures.north, data->textures.north_path))
		return (0);
	if (!load_texture(data, &data->textures.south, "textures/south.xmp"))
		return (0);
	if (!load_texture(data, &data->textures.west, "textures/west.xpm"))
		return (0);
	if (!load_texture(data, &data->textures.east, "textures/east.xpm"))
		return (0);
	printf("All textures loaded successfully!\n");
	return (1);
}

