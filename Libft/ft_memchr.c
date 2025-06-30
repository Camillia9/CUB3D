/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:02:05 by camansou          #+#    #+#             */
/*   Updated: 2024/11/14 16:21:54 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*src = (const unsigned char *)s;
	unsigned char		ct;
	size_t				i;

	ct = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (src[i] == ct)
			return ((void *)&src[i]);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// int	main(void)
// {
// 	char s[] = "Camillia";
// 	int c = 'a';
// 	int n = 3;
// 	char *mem;

// 	char s1[] = "Camillia";
// 	int c1 = 'a';
// 	int n1 = 3;
// 	char *ftmem;

// 	mem = memchr(s, c, n);
// 	ftmem = ft_memchr(s1, c1, n1);

// 	printf("%s\n", mem);
// 	printf("%s\n", ftmem);
// }

// int main(int ac, char **av)
// {
// 	if (ac != 4)
// 		return 0;

// 	// char s;
// 	// int c;
// 	// int n;

// 	printf("%s", memchr(av[1], av[2], atoi(av[3])));
// }
