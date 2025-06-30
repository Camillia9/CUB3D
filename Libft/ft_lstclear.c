/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:01:31 by camansou          #+#    #+#             */
/*   Updated: 2024/11/18 14:32:54 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !*lst || !del)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
}

// void delete_content(void *content)
// {
//     free(content);
// }

// int main(void)
// {
//     t_list *list = ft_lstnew(ft_strdup("1"));
//     list->next = ft_lstnew(ft_strdup("2"));
//     list->next->next = ft_lstnew(ft_strdup("3"));

//     t_list *temp = list;
//     printf("Liste:\n");
//     while (temp)
//     {
//         printf("%s\n", (char *)temp->content);
//         temp = temp->next;
//     }

//     ft_lstclear(&list, delete_content);

//     if (list == NULL)
//         printf("\nDeleted\n");

//     return (0);
// }