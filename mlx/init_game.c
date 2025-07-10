#include "../includes/cub3d.h"

int	init_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		return (0);
	data->screen_width = 800;
	data->screen_height = 600;
	data->mlx.win = mlx_new_window(data->mlx.mlx, data->screen_width,
			data->screen_height, "CUB3D");
	if (!data->mlx.win)
	{
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
		return (0);
	}
	data->mlx.img = mlx_new_image(data->mlx.mlx, data->screen_width,
			data->screen_height);
	if (!data->mlx.img)
	{
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
		free(data->mlx.mlx);
		return (0);
	}
	data->mlx.img_data = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp,
			&data->mlx.line_length, &data->mlx.endian);
	return (1);
}

void	init_player(t_player *player)
{
	// Position de départ (centre de la case où est P)
	// ,5 pour qu'ils sit bien au milieu 
	player->x = 7.5;
	player->y = 2.5;

	// Il regardera vers le nord
	player->dir_x = 0.0;
	player->dir_y = -1.0;
	// Plan de projection (champ de vision ~60°)
	player->plane_x = 0.66;
	player->plane_y = 0.0;
	// Vitesse
	player->move_speed = 0.01;
	player->rot_speed = 0.01;
}

int game_loop(t_data *data)
{
	handle_mouvement(data);
	handle_mouvement_2(data);
	return (0);
}
