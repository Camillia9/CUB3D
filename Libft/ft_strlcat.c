/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:28:34 by camansou          #+#    #+#             */
/*   Updated: 2024/11/11 15:56:20 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (siz <= dst_len)
		return (src_len + siz);
	i = 0;
	while (src[i] && i < siz - dst_len - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
/*
#include <bsd/string.h>
#include <stdio.h>

int	main(void)
{
	char src[] = "bonjour";
	char dst[] = "ahah";
	char src2[] = "bonjour";
	char dst2[] = "ahah";

	printf("strlen\n%zu\n%s\n", strlcat(dst, src, 6), dst);
	printf("ft_strlen\n%zu\n%s\n", ft_strlcat(dst2, src2, 6), dst);
}
*/