/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:05:26 by camansou          #+#    #+#             */
/*   Updated: 2025/08/15 16:33:00 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

enum			e_texture_index
{
	NORTH = 1,
	SOUTH = 2,
	EAST = 3,
	WEST = 4
};

// Strcutures
typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			player_x;
	int			player_y;
	char		player_dir;
}				t_map;

typedef struct s_draw_range
{
	int			start;
	int			end;
}				t_draw_range;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
}				t_player;

typedef struct s_texture
{
	void		*img;
	char		*data;
	int			width;
	int			height;
	int			bpp;
	int			line_length;
	int			endian;
	char		*path;
}				t_texture;

typedef struct s_textures
{
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
	char		*north_path;
	char		*south_path;
	char		*east_path;
	char		*west_path;
}				t_textures;

typedef struct s_colors
{
	int			floor_r;
	int			floor_g;
	int			floor_b;
	int			ceiling_r;
	int			ceiling_b;
	int			ceiling_g;
	int			floor_color;
	int			ceiling_color;
}				t_colors;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_data;
	int			img_width;
	int			img_height;
	int			bpp;
	int			line_length;
	int			endian;
}				t_mlx;

typedef struct s_ray
{
	double		camera_x;
	double		dir_x;
	double		dir_y;

	int			map_x;
	int			map_y;

	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;

	int			step_x;
	int			step_y;

	int			hit_wall;
	int			side;
	double		perp_wall_dist;

	int			line_height;
	int			draw_start;
	int			draw_end;

	double		distance;
	int			wall_x;
	int			wall_y;
	int			tex_x;
	int			tex_num;
}				t_ray;

typedef struct s_ray_params
{
	double		start_x;
	double		start_y;
	double		dir_x;
	double		dir_y;
}				t_ray_params;

typedef struct s_data
{
	char		**file_content;
	t_map		map;
	t_player	player;
	t_textures	textures;
	t_colors	colors;
	t_mlx		mlx;
	t_ray		ray;

	int			screen_width;
	int			screen_height;
	int			keys[256];
	int			arrow_keys[10];
	int			running;
}				t_data;

#endif