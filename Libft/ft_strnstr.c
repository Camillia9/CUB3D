/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:47:15 by camansou          #+#    #+#             */
/*   Updated: 2024/11/18 17:45:01 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!little[0])
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] && i + j < len)
			j++;
		if (!little[j])
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
/*


#include <bsd/string.h>
#include <stdio.h>

int	main(void)
{
	// char *big;
	// char *little;
	// int len;

	const char big[] = "Hello World Mcv";
	const char little[] = "World";
	// int len = 3;


	printf("strnstr: %s\n", strnstr(big, little, 11));
	printf("ft_strnstr: %s\n", ft_strnstr(big, little, 11));
}*/