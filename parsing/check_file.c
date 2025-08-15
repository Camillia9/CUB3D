/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:06:29 by camansou          #+#    #+#             */
/*   Updated: 2025/08/15 16:06:31 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Affiche un message d'erreur formaté et termine le programme
 */
void	print_error(char *message, t_data *data)
{
	printf("Error\n%s\n", message);
	free_data(data);
	exit(1);
}

/**
 * Vérifie que le fichier a l'extension .cub
 */
static int	check_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strcmp(filename + len - 4, ".cub") != 0)
		return (0);
	return (1);
}

/**
 * Vérifie que le fichier existe et est lisible
 */
int	check_file_access(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

/**
 * Valide les arguments passés au programme
 */
void	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		print_error("Usage: ./cub3d <map.cub>", NULL);
	}
	if (!check_file_extension(argv[1]))
	{
		print_error("Map file must have .cub extension", NULL);
	}
	if (!check_file_access(argv[1]))
	{
		print_error("Cannot open map file: file does not exist "
			"or is not readable", NULL);
	}
}
