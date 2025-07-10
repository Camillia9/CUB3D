#include "../includes/cub3d.h"

static void	calculate_ray_direction(t_data *data, int x, double *dir_x, double *dir_y)
{
	double camera_x;

	camera_x = 2.0 * x / (double)data->screen_width - 1.0;
	*dir_x = data->player.dir_x + data->player.plane_x * camera_x;
	*dir_y = data->player.dir_y + data->player.plane_y * camera_x;
}

static void	calculate_wall_height(t_ray *ray, int screen_height, int *draw_start, int *draw_end)
{
	int	wall_height;
	int	screen_center;

	wall_height = (int)(screen_height / ray->distance);
	screen_center = screen_height / 2;

	*draw_start = screen_center - wall_height / 2;
	*draw_end = screen_center + wall_height / 2;
	
	if (*draw_start < 0)
		*draw_start = 0;
	if (*draw_end >= screen_height)
		*draw_end = screen_height - 1;
}

static int	get_wall_color(t_ray *ray)
{
	if (ray->side == 0)
		return (0xFF0000);
	else
		return (0x800000);
}

static void	draw_column(t_data *data, int x, int draw_start, int draw_end, t_ray *ray)
{
	int y;

	y = 0;
	while (y < data->screen_height)
	{
		int 	color;
		char	*pixel;

		if (y < draw_start)
			color = 0x87CEEB;
		else if (y <= draw_end)
			color = get_wall_color(ray);
		else
			color = 0x228B22;
		
		pixel = data->mlx.img_data + (y * data->mlx.line_length + x * (data->mlx.bpp / 8));
		*(unsigned int*)pixel = color;
		y++;
	}
}

void	render_scene(t_data *data)
{
	int x;

	x = 0;
	while (x < data->screen_width)
	{
		double 	dir_x;
		double	dir_y;
		int		draw_start;
		int		draw_end;

		calculate_ray_direction(data, x, &dir_x, &dir_y);
		cast_ray(&data->ray, data->player.x, data->player.y, dir_x, dir_y);
		calculate_wall_height(&data->ray, data->screen_height, &draw_start, &draw_end);
		draw_column(data, x, draw_start, draw_end, &data->ray);
		x++;
	}
}

