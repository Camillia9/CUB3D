/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2024/11/15 12:46:33 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_len;
	char	*str;
	size_t	i;

	total_len = nmemb * size;
	if (size != 0 && total_len / size != nmemb)
		return (NULL);
	str = malloc(total_len);
	if (!str)
		return (NULL);
	i = 0;
	while (i < total_len)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

/*#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	void *ptr1;
	void *ptr2;
	size_t num;
	size_t size;
	
	if (ac != 3)
		return 0;

	num = atoi(av[1]);
	size = atoi(av[2]);
	
	ptr1 = calloc(num, size);
	ptr2 = ft_calloc(num, size);
	
	printf("calloc: %p\n", ptr1);
	printf("ft_calloc: %p\n", ptr2);
}*/