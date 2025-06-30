/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 20:41:49 by camansou          #+#    #+#             */
/*   Updated: 2024/11/17 21:09:35 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
// int	main(void)
// {
// 	int size;
// 	t_list lst1;
// 	t_list lst2;
// 	t_list lst3;

// 	lst1.next = &lst2;
// 	lst2.next = &lst3;
// 	lst3.next = NULL;

// 	size = ft_lstsize(&lst1);

// 	printf("%d\n", size);
// }