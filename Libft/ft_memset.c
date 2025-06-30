/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:08:03 by camansou          #+#    #+#             */
/*   Updated: 2025/05/22 20:45:53 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>

int	main(int ac, char **av)
{
	if (ac != 4)
		return (1);

	printf("Avant: %s\n", av[1]);
	ft_memset(av[1], av[2][0], atoi(av[3]));
	printf("Apres: %s\n", av[1]);
}*/
