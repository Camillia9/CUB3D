#include "../includes/cub3d.h"

void fill_screen(t_data *data, int color)
{
	int y;
	int x;
	char *pixel;

	y = 0;
	while (y < data->screen_height)
	{
		x = 0;
		while (x < data->screen_width)
		{
			pixel = data->mlx.img_data + (y * data->mlx.line_length + x * (data->mlx.bpp / 8));
			* (unsigned int*)pixel = color;
			x++;
		}
		y++;
	}
}

void    render_frame(t_data *data)
{
    fill_screen(data, 0x000000);
    render_scene(data);
    mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
