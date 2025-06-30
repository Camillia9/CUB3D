/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:30:26 by camansou          #+#    #+#             */
/*   Updated: 2024/11/14 16:58:52 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	slen;
	size_t	i;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
	{
		new_str = malloc(1);
		if (!new_str)
			return (NULL);
		new_str[0] = '\0';
		return (new_str);
	}
	if (start + len > slen)
		len = slen - start;
	new_str = (char *)malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < len)
		new_str[i] = s[start + i];
	new_str[i] = '\0';
	return (new_str);
}

// int	main(void)
// {
// 	char *s = "Bonjour";
// 	int start = 2;
// 	size_t len = 3;

// 	printf("%s", ft_substr(s, start, len));
// }