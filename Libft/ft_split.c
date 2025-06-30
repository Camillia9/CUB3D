/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:53:19 by camansou          #+#    #+#             */
/*   Updated: 2024/11/19 18:03:47 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free(char **str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

int	count_words(char const *s, char c)
{
	int	i;
	int	count_word;

	i = 0;
	count_word = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count_word++;
		i++;
	}
	return (count_word);
}

static char	*get_words(char const *s, char c, int *i)
{
	int		len;
	int		j;
	char	*str;

	len = 0;
	while (s[*i + len] && s[*i + len] != c)
		len++;
	str = (char *)malloc((sizeof(char) * len + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (j < len)
	{
		str[j] = s[*i + j];
		j++;
	}
	str[j] = '\0';
	*i += len;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		i;
	int		j;

	dst = (char **)malloc((sizeof(char *)) * (count_words(s, c) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			dst[j] = get_words(s, c, &i);
			if (dst[j] == NULL)
				return (ft_free(dst, j));
			j++;
		}
	}
	dst[j] = NULL;
	return (dst);
}

// int	main(void)
// {
// 	int i;
// 	char **result;

// 	result = ft_split("Hello, world!", ',');
// 	i = 0;
// 	while (result[i])
// 	{
// 		printf("%s\n", result[i]);
// 		i++;
// 	}
// 	free(result);
// }