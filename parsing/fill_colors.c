/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:06:44 by camansou          #+#    #+#             */
/*   Updated: 2025/08/15 16:06:48 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Assigne les valeurs RGB pour le sol (Floor)
 */
void	assign_floor_color(t_data *data, int rgb[3])
{
	data->colors.floor_r = rgb[0];
	data->colors.floor_g = rgb[1];
	data->colors.floor_b = rgb[2];
	data->colors.floor_color = encode_rgb_color(rgb[0], rgb[1], rgb[2]);
}

/**
 * Assigne les valeurs RGB pour le plafond (Ceiling)
 */
void	assign_ceiling_color(t_data *data, int rgb[3])
{
	data->colors.ceiling_r = rgb[0];
	data->colors.ceiling_g = rgb[1];
	data->colors.ceiling_b = rgb[2];
	data->colors.ceiling_color = encode_rgb_color(rgb[0], rgb[1], rgb[2]);
}

/**
 * Assigne les valeurs RGB selon le type
 */
void	assign_rgb_values(t_data *data, int rgb[3], int color_type)
{
	if (color_type == 1)
		assign_floor_color(data, rgb);
	else if (color_type == 2)
		assign_ceiling_color(data, rgb);
}

/**
 * Encode une couleur RGB en entier (format 0xRRGGBB)
 */
int	encode_rgb_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
