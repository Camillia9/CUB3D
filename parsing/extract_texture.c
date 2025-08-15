/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:06:38 by camansou          #+#    #+#             */
/*   Updated: 2025/08/15 16:06:43 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Trouve la fin du chemin de texture
 */
static char	*find_path_end(char *start)
{
	char	*end;

	end = start;
	while (*end && *end != '\n' && *end != ' ' && *end != '\t')
		end++;
	return (end);
}

/**
 * Valide qu'il n'y a pas de caractères après le chemin
 */
static void	validate_path_syntax(char *path_end, t_data *data)
{
	char	*remaining;

	remaining = skip_whitespace(path_end);
	if (*remaining && *remaining != '\n')
		print_error("Invalid syntax: extra characters after texture path",
			data);
}

/**
 * Crée une copie du chemin extrait
 */
static char	*create_path_copy(char *start, char *end, t_data *data)
{
	char	*path;
	int		len;
	int		i;

	len = end - start;
	if (len == 0)
		print_error("Missing texture path", data);
	path = safe_malloc(data, len + 1);
	i = 0;
	while (i < len)
	{
		path[i] = start[i];
		i++;
	}
	path[i] = '\0';
	return (path);
}

/**
 * Extrait le chemin de la texture depuis la ligne
 */
char	*extract_texture_path(char *line, t_data *data)
{
	char	*path_start;
	char	*path_end;

	path_start = skip_whitespace(line + 2);
	path_end = find_path_end(path_start);
	validate_path_syntax(path_end, data);
	return (create_path_copy(path_start, path_end, data));
}
