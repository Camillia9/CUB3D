/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:56:42 by camansou          #+#    #+#             */
/*   Updated: 2024/11/19 15:44:03 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list) * 1);
	if (list == NULL)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

// int	main(void)
// {
// 	t_list	*list;

// 	list = ft_lstnew((void *)42);
// 	printf("%ld\n", (long int)list->content);
// 	free(list);

// 	list = ft_lstnew("HELLO");
// 	printf("%s\n", (char *)list->content);
// 	free(list);
// }