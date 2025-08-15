/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:06:05 by camansou          #+#    #+#             */
/*   Updated: 2025/08/15 16:06:07 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x + data->player.dir_x * data->player.move_speed;
	new_y = data->player.y + data->player.dir_y * data->player.move_speed;
	if (!is_wall(data, (int)new_x, (int)data->player.y))
		data->player.x = new_x;
	if (!is_wall(data, (int)data->player.x, (int)new_y))
		data->player.y = new_y;
}

void	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x - data->player.dir_x * data->player.move_speed;
	new_y = data->player.y - data->player.dir_y * data->player.move_speed;
	if (!is_wall(data, (int)new_x, (int)data->player.y))
		data->player.x = new_x;
	if (!is_wall(data, (int)data->player.x, (int)new_y))
		data->player.y = new_y;
}

void	move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x + data->player.dir_y * data->player.move_speed;
	new_y = data->player.y - data->player.dir_x * data->player.move_speed;
	if (!is_wall(data, (int)new_x, (int)data->player.y))
		data->player.x = new_x;
	if (!is_wall(data, (int)data->player.x, (int)new_y))
		data->player.y = new_y;
}

void	move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x - data->player.dir_y * data->player.move_speed;
	new_y = data->player.y - (-data->player.dir_x) * data->player.move_speed;
	if (!is_wall(data, (int)new_x, (int)data->player.y))
		data->player.x = new_x;
	if (!is_wall(data, (int)data->player.x, (int)new_y))
		data->player.y = new_y;
}
