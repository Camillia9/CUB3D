/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:28:45 by camansou          #+#    #+#             */
/*   Updated: 2024/11/14 16:37:13 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	unsigned long	i;
	int				len;

	len = 0;
	while (src[len])
		len++;
	if (siz == 0)
		return (len);
	i = 0;
	while (src[i] && i < siz - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}
/*
#include <stdio.h>
int	main(void)
{
	char src[] = "Hello";
	char dest[3];
	int len;
	
	len = strlcpy(dest, src, 3);
	printf("%s\n%d\n", dest, len);
	return 0;
}*/