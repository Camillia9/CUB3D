/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:07:34 by camansou          #+#    #+#             */
/*   Updated: 2025/08/15 16:07:35 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_ray(t_ray *ray, t_ray_params *params)
{
	ray->map_x = (int)params->start_x;
	ray->map_y = (int)params->start_y;
	ray->dir_x = params->dir_x;
	ray->dir_y = params->dir_y;
	ray->hit_wall = 0;
	ray->side = 0;
}

static void	calculate_delta_distance(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
}

static void	step_and_side(t_ray *ray, t_ray_params *params)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (params->start_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - params->start_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (params->start_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - params->start_y)
			* ray->delta_dist_y;
	}
}

static void	algo_dda(t_ray *ray, t_data *data)
{
	while (ray->hit_wall == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (is_wall(data, ray->map_x, ray->map_y))
			ray->hit_wall = 1;
	}
}

void	cast_ray(t_ray *ray, t_ray_params *params, t_data *data)
{
	init_ray(ray, params);
	calculate_delta_distance(ray);
	step_and_side(ray, params);
	algo_dda(ray, data);
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - params->start_x
				+ (1 - ray->step_x) / 2)
			/ ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - params->start_y
				+ (1 - ray->step_y) / 2)
			/ ray->dir_y;
	if (ray->perp_wall_dist <= 0.001)
		ray->perp_wall_dist = 0.001;
	ray->distance = ray->perp_wall_dist;
	ray->wall_x = ray->map_x;
	ray->wall_y = ray->map_y;
}
