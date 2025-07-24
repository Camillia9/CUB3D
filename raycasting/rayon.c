#include "../includes/cub3d.h"

static void	calculate_ray_direction(t_data *data, int x, double *dir_x,
		double *dir_y)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)data->screen_width - 1.0;
	*dir_x = data->player.dir_x + data->player.plane_x * camera_x;
	*dir_y = data->player.dir_y + data->player.plane_y * camera_x;
}

static void	calculate_wall_height(t_ray *ray, int screen_height,
		int *draw_start, int *draw_end)
{
	int	wall_height;
	int	screen_center;

	if (ray->perp_wall_dist < 0.001)
		ray->perp_wall_dist = 0.001;
	wall_height = (int)(screen_height / ray->perp_wall_dist);
	if (wall_height > screen_height * 10)
		wall_height = screen_height * 10;
	screen_center = screen_height / 2;
	*draw_start = screen_center - wall_height / 2;
	*draw_end = screen_center + wall_height / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	if (*draw_end >= screen_height)
		*draw_end = screen_height - 1;
}

static int	get_wall_texture(t_ray *ray, t_data *data, int y, int draw_start)
{
	t_texture	*texture;
	int			tex_y;
	int			tex_x;
	char		*pixel;

	(void)draw_start;
	texture = select_wall_texture(ray, data);
	tex_y = calculate_tex_y(ray, data, y, texture);
	tex_x = calcul_tex_x(ray, texture, data->player.x, data->player.y);
	pixel = texture->data + (tex_y * texture->line_length + tex_x
			* (texture->bpp / 8));
	return (*(int *)pixel);
}

static void	draw_column(t_data *data, int x, int draw_start, int draw_end)
{
	int		y;
	int		color;
	char	*pixel;

	y = 0;
	while (y < data->screen_height)
	{
		if (y < draw_start)
			color = data->colors.ceiling_color;
		else if (y <= draw_end)
			color = get_wall_texture(&data->ray, data, y, draw_start);
		else
			color = data->colors.floor_color;
		pixel = data->mlx.img_data + (y * data->mlx.line_length + x
				* (data->mlx.bpp / 8));
		*(unsigned int *)pixel = color;
		y++;
	}
}

void	render_scene(t_data *data)
{
	int				x;
	double			dir_x;
	double			dir_y;
	t_draw_range	draw;
	t_ray_params	params;

	x = 0;
	while (x < data->screen_width)
	{
		calculate_ray_direction(data, x, &dir_x, &dir_y);
		params.start_x = data->player.x;
		params.start_y = data->player.y;
		params.dir_x = dir_x;
		params.dir_y = dir_y;
		cast_ray(&data->ray, &params, data);
		calculate_wall_height(&data->ray, data->screen_height, &draw.start,
			&draw.end);
		draw_column(data, x, draw.start, draw.end);
		x++;
	}
}
