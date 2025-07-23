#include "../includes/cub3d.h"

static void	calculate_ray_direction(t_data *data, int x,
		double *dir_x, double *dir_y)
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

static int	calcul_tex_x(t_ray *ray, t_texture *texture,
	double start_x, double start_y)
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
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

static int	get_wall_texture(t_ray *ray, t_data *data, int y, int draw_start, int draw_end)
{
	(void)draw_start;
	(void)draw_end;
	t_texture	*texture;
	int			tex_y;
	int			tex_x;
	int			color;
	//int			wall_height;

	if (ray->side == 0) // Mur vertical
	{
		if (ray->dir_x > 0)
			texture = &data->textures.east;
		else
			texture = &data->textures.west;
	}
	else // Mur horizontaux
	{
		if (ray->dir_y > 0)
			texture = &data->textures.south;
		else
			texture = &data->textures.north;
	}

    int real_wall_height = (int)(data->screen_height / ray->perp_wall_dist);
    int screen_center = data->screen_height / 2;
    int real_draw_start = screen_center - real_wall_height / 2;

	//tex_y = ((y - draw_start) * texture->height) / wall_height;
	tex_y = ((y - real_draw_start) * texture->height) / real_wall_height;

    if (tex_y < 0) tex_y = 0;
    if (tex_y >= texture->height) tex_y = texture->height - 1;

	tex_x = calcul_tex_x(ray, texture, data->player.x, data->player.y);

	char *pixel = texture->data + (tex_y * texture->line_length + tex_x * (texture->bpp / 8));
	color = *(int*)pixel;
	return (color);
}

static void	draw_column(t_data *data, int x, int draw_start, int draw_end, t_ray *ray)
{
	int		y;
	int		color;
	char	*pixel;

	y = 0;
	while (y < data->screen_height)
	{
		if (y < draw_start)
			color = 0x87CEEB;
		else if (y <= draw_end)
			color = get_wall_texture(ray, data, y, draw_start, draw_end);
		else
			color = 0x228B22;
		pixel = data->mlx.img_data + (y * data->mlx.line_length
				+ x * (data->mlx.bpp / 8));
		*(unsigned int *)pixel = color;
		y++;
	}
}

void	render_scene(t_data *data)
{
	int		x;
	double	dir_x;
	double	dir_y;
	int		draw_start;
	int		draw_end;

	x = 0;
	while (x < data->screen_width)
	{
		calculate_ray_direction(data, x, &dir_x, &dir_y);
		cast_ray(&data->ray, data->player.x, data->player.y,
			dir_x, dir_y, data);
		calculate_wall_height(&data->ray, data->screen_height,
			&draw_start, &draw_end);
		draw_column(data, x, draw_start, draw_end, &data->ray);
		x++;
	}
}
