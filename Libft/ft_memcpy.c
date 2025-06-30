/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:26:50 by camansou          #+#    #+#             */
/*   Updated: 2024/11/18 17:35:14 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*source;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	dst = (unsigned char *)dest;
	source = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst[i] = source[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char dest[] = "Hello";
	char src[] = "Mangera";
	int n = 3;
	char *res_mem;

	char dest2[] = "Hello";
	char src2[] = "Mangera";
	int n2 = 3;
	char *res_ftmem;

	res_mem = memcpy(dest, src, n);
	res_ftmem = ft_memcpy(dest2, src2, n2);

	printf("%s\n", res_mem);
	printf("%s\n", res_ftmem);
}*/