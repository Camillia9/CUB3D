/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:19:03 by camansou          #+#    #+#             */
/*   Updated: 2024/11/18 17:49:29 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = -1;
	if (d < s)
	{
		while (++i < n)
			d[i] = s[i];
	}
	else
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char dest[] = "Hello";
	char src[] = "";
	int	n = 3;
	char *mem;

	char dest2[] = "Hello";
	char src2[] = "";
	int n2 = 3;
	char *ftmem;

	mem = memmove(dest, src, n);
	ftmem = ft_memmove(dest2, src2, n2);

	printf("memmove: %s\n", mem);
	printf("ft_memmove: %s\n", ftmem);
}*/