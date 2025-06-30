/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:43:01 by camansou          #+#    #+#             */
/*   Updated: 2024/11/18 15:38:05 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*
#include <stdio.h>
int main(int ac, char **av)
{
	if (ac != 3)
		return 1;

	printf("Avant: %s\n", av[1]);
	ft_bzero(av[1], atoi(av[2]));
	printf ("Apres: %s\n", av[1]);
}*/