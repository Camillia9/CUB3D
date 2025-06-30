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

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_game(data);
	return (0);
}

int	handle_mouvement(t_data *data)
{
	static int	color = 0x000000;
	
	if (data->keys[119])
		color = 0xFF0000;
	if (data->keys[115])   
        color = 0x00FF00;
    if (data->keys[97])  
        color = 0x0000FF;
    if (data->keys[100])
        color = 0xFFFF00;
}
int game_loop(t_data *data)
{
	handle_mouvement(data);
	clear_screen(data);
	//ray casting
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (0);
}