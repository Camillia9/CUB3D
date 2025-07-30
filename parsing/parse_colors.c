#include "../includes/cub3d.h"

/**
 * Parse une valeur RGB (0-255)
 * Ignorer les espaces
 * Parser le nombre
 */
int	parse_rgb_value(char **str)
{
	int	value;
	int	digits;

	value = 0;
	digits = 0;
	while (**str && (**str == ' ' || **str == '\t'))
		(*str)++;
	while (**str && **str >= '0' && **str <= '9')
	{
		value = value * 10 + (**str - '0');
		(*str)++;
		digits++;
	}
	if (digits == 0 || value > 255)
		return (-1);
	return (value);
}

/**
 * Identifie le type de couleur et vérifie les doublons
 */
int	identify_color_type(char *line, t_data *data)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (data->colors.floor_r != -1)
			print_error("Duplicate Floor color", data);
		return (1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (data->colors.ceiling_r != -1)
			print_error("Duplicate Ceiling color", data);
		return (2);
	}
	return (0);
}

/**
 * Parse les 3 valeurs RGB d'une couleur
 * Vérifier qu'il n'y a pas de caractères supplémentaires après les valeurs RGB
 */
void	parse_rgb_values(char *color_start, t_data *data, int color_type)
{
	int		rgb_values[3];
	int		i;
	char	*remaining;

	i = 0;
	while (i < 3)
	{
		rgb_values[i] = parse_rgb_value(&color_start);
		if (rgb_values[i] == -1)
			print_error("Invalid RGB value", data);
		if (i < 2)
		{
			if (*color_start != ',')
				print_error("Missing comma in RGB values", data);
			color_start++;
		}
		i++;
	}
	remaining = skip_whitespace(color_start);
	if (*remaining && *remaining != '\n')
		print_error("Invalid syntax: extra characters after RGB values", data);
	assign_rgb_values(data, rgb_values, color_type);
}

/**
 * Parse une ligne de couleur (F ou C)
 */
int	parse_color_line(char *line, t_data *data)
{
	char	*trimmed;
	char	*color_start;
	int		color_type;

	trimmed = skip_whitespace(line);
	color_type = identify_color_type(trimmed, data);
	if (color_type == 0)
		return (0);
	color_start = skip_whitespace(trimmed + 1);
	parse_rgb_values(color_start, data, color_type);
	return (1);
}
