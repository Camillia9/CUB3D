#include "../includes/cub3d.h"

/**
 * Supprime les espaces en début et fin de chaîne
 */
char	*trim_whitespace(char *str)
{
	char	*end;

	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '\0')
		return (str);
	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'
			|| *end == '\n' || *end == '\r'))
		end--;
	*(end + 1) = '\0';
	return (str);
}

/**
 * Ignore les espaces et tabulations au début d'une ligne
 */
char	*skip_whitespace(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (line);
}

/**
 * Vérifie si une ligne est vide ou ne contient que des espaces
 */
int	is_empty_line(char *line)
{
	char	*trimmed;

	trimmed = skip_whitespace(line);
	return (*trimmed == '\0' || *trimmed == '\n');
}

void	*safe_malloc(t_data *data, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		print_error("Failed to allocate memory", data);
	}
	return (ptr);
}
