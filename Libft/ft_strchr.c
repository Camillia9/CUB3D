/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:28:53 by camansou          #+#    #+#             */
/*   Updated: 2024/11/19 17:24:49 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>
// int	main(int ac, char **av)

// {
// 	if (ac != 3)
// 		return (0);

// 	printf("%s\n", strchr(av[1], av[2][0]));
// 	printf("%s\n", ft_strchr(av[1], av[2][0]));
// }
// // int	main(void)
// 	// char s[] = "tripouille";
//         //check(ft_strchr(s, 't' + 256) == s); showLeaks();
// 	// printf("%s", strchr(s, 't' + 256));
// 	// printf("%s"`, ft_strchr(s, 't' + 256));

// 	return (0);
