/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:21:42 by camansou          #+#    #+#             */
/*   Updated: 2024/11/18 15:31:18 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

// int	main(void)
// {
// 	int size;
// 	t_list *base = (t_list *)malloc(sizeof(t_list) * 1);
// 	base->content = "BASE";
// 	t_list lst2;
// 	lst2.content = "2";
// 	t_list lst3;
// 	lst3.content = "3";

// 	base->next = &lst2;
// 	lst2.next = &lst3;
// 	lst3.next = NULL;

// 	t_list lst_new;
// 	lst_new.content = "NEW";

// 	ft_lstadd_front(&base, &lst_new);
// 	while (base != NULL)
// 	{
// 		printf("%s\n", (char *)base->content);
// 		base = base->next;
// 	}
// }