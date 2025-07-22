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

void	init_direction(t_player *player, t_map *map)
{
	if (map->player_dir == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
	if (map->player_dir == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = +1.0;
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
	if (map->player_dir == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = -0.66;
	}
	if (map->player_dir == 'E')
	{
		player->dir_x = +1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = 0.66;
	}
}

//void init_map(t_data *data)
//{
//	// Initialisation manuelle de la position du joueur
//	data->map.player_x = 7;  // Position X du 'W' dans votre carte
//	data->map.player_y = 2;  // Position Y du 'W' dans votre carte  
//	data->map.player_dir = 'E';
//}

void	init_player(t_player *player, t_map *map)
{
	// Position de départ (centre de la case où est P)
	// ,5 pour qu'ils sit bien au milieu 
	player->x = map->player_x + 0.5;
	player->y = map->player_y + 0.5;
	
	init_direction(player, map);
	// Vitesse
	player->move_speed = 0.05;
	player->rot_speed = 0.03;
}


int game_loop(t_data *data)
{
	handle_mouvement(data);
	handle_mouvement_2(data);
	return (0);
}
