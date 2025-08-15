/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:06:13 by camansou          #+#    #+#             */
/*   Updated: 2025/08/15 16:06:15 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	normalisation(t_data *data)
{
	double	dir_length;
	double	plane_length;

	dir_length = sqrt(data->player.dir_x * data->player.dir_x
			+ data->player.dir_y * data->player.dir_y);
	if (dir_length > 0)
	{
		data->player.dir_x /= dir_length;
		data->player.dir_y /= dir_length;
	}
	plane_length = sqrt(data->player.plane_x * data->player.plane_x
			+ data->player.plane_y * data->player.plane_y);
	if (plane_length > 0)
	{
		data->player.plane_x = (data->player.plane_x / plane_length) * 0.66;
		data->player.plane_y = (data->player.plane_y / plane_length) * 0.66;
	}
}

void	rotate_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	cos_rot = cos(-data->player.rot_speed);
	sin_rot = sin(-data->player.rot_speed);
	data->player.dir_x = data->player.dir_x * cos_rot
		- data->player.dir_y * sin_rot;
	data->player.dir_y = old_dir_x * sin_rot
		+ data->player.dir_y * cos_rot;
	data->player.plane_x = data->player.plane_x * cos_rot
		- data->player.plane_y * sin_rot;
	data->player.plane_y = old_plane_x * sin_rot
		+ data->player.plane_y * cos_rot;
	normalisation(data);
}

void	rotate_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	cos_rot = cos (data->player.rot_speed);
	sin_rot = sin (data->player.rot_speed);
	data->player.dir_x = data->player.dir_x * cos_rot
		- data->player.dir_y * sin_rot;
	data->player.dir_y = old_dir_x * sin_rot
		+ data->player.dir_y * cos_rot;
	data->player.plane_x = data->player.plane_x * cos_rot
		- data->player.plane_y * sin_rot;
	data->player.plane_y = old_plane_x * sin_rot
		+ data->player.plane_y * cos_rot;
	normalisation(data);
}
