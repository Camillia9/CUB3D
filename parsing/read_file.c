#include "../includes/cub3d.h"
#include "../Libft/get_next_line/get_next_line.h"

/**
 * Lit toutes les lignes et les stocke dans une liste
 */
static t_list	*read_lines_to_list(int fd)
{
	t_list	*temp_lines;
	char	*line;

	temp_lines = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_lstadd_back(&temp_lines, ft_lstnew(line));
		line = get_next_line(fd);
	}
	return (temp_lines);
}

/**
 * Convertit la liste en tableau de strings
 */
static char	**convert_list_to_array(t_list *temp_lines, int line_count, t_data *data)
{
	char	**file_content;
	t_list	*current;
	int		i;

	file_content = malloc(sizeof(char *) * (line_count + 1));
	if (!file_content)
		print_error("Memory allocation failed", NULL);
	current = temp_lines;
	i = 0;
	while (current && i < line_count)
	{
		file_content[i] = ft_strdup((char *)current->content);
		if (!file_content[i])
			print_error("Memory allocation failed for file content", data);
		current = current->next;
		i++;
	}
	file_content[i] = NULL;
	return (file_content);
}

/**
 * Lit entièrement le fichier et retourne un tableau de lignes
 */
char	**read_entire_file(char *filename, t_data *data)
{
	int		fd;
	t_list	*temp_lines;
	char	**file_content;
	int		line_count;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_error("Cannot open configuration file", data);
	temp_lines = read_lines_to_list(fd);
	close(fd);
	if (!temp_lines)
		print_error("Empty or invalid file", data);
	line_count = ft_lstsize(temp_lines);
	file_content = convert_list_to_array(temp_lines, line_count, data);
	ft_lstclear(&temp_lines, free);
	return (file_content);
}

/**
 * Libère le contenu du fichier
 */
void	free_file_content(char **file_content)
{
	int	i;

	if (!file_content)
		return ;
	i = 0;
	while (file_content[i])
	{
		free(file_content[i]);
		i++;
	}
	free(file_content);
}
