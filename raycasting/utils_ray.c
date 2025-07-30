#include "../includes/cub3d.h"

int	is_wall(t_data *data, int x, int y)
{
	if ((x < 0) || (x >= data->map.width) || (y < 0) || (y >= data->map.height))
		return (1);
	if (data->map.grid[y][x] == '1')
		return (1);
	return (0);
}

t_texture	*select_wall_texture(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (&data->textures.east);
		else
			return (&data->textures.west);
	}
	else
	{
		if (ray->dir_x > 0)
			return (&data->textures.south);
		else
			return (&data->textures.north);
	}
}

int	calcul_tex_x(t_ray *ray, t_texture *texture, double start_x,
		double start_y)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = start_y + ray->distance * ray->dir_y;
	else
		wall_x = start_x + ray->distance * ray->dir_x;
	wall_x = (wall_x - 1) * -1;
	wall_x = wall_x - floor(wall_x);
	tex_x = (int)(wall_x * texture->width);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1
			&& ray->dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

int	calculate_tex_y(t_ray *ray, t_data *data, int y, t_texture *texture)
{
	int	real_wall_height;
	int	real_draw_start;
	int	tex_y;

	real_wall_height = (int)(data->screen_height / ray->perp_wall_dist);
	real_draw_start = (data->screen_height / 2) - (real_wall_height / 2);
	tex_y = ((y - real_draw_start) * texture->height) / real_wall_height;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	return (tex_y);
}
