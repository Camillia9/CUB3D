#include "../includes/cub3d.h"

int close_game(t_data *data)
{
    printf("Game closed\n");
    
    if (data->mlx.img)
        mlx_destroy_image(data->mlx.mlx, data->mlx.img);
    if (data->mlx.win)
        mlx_destroy_window(data->mlx.mlx, data->mlx.win);
    if (data->mlx.mlx)
    {
        mlx_destroy_display(data->mlx.mlx);
        free(data->mlx.mlx);
    }
    exit(0);
}

void free_texture(t_data *data, t_texture *texture)
{
	if (texture->img)
	{
		mlx_destroy_image(data->mlx.mlx, texture->img);
		texture->img = NULL;
	}
}

void free_all_textures(t_data *data)
{
	free_texture(data, &data->textures.north);
	free_texture(data, &data->textures.south);
	free_texture(data, &data->textures.west);
	free_texture(data, &data->textures.east);
}
