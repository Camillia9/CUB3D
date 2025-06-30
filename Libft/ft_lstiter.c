/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:33:53 by camansou          #+#    #+#             */
/*   Updated: 2024/11/18 15:30:29 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// void to_upper(void *content)
//     char *str = (char *)content;
//     int i = 0;

//     while (str[i])
//     {
//         if (str[i] >= 'a' && str[i] <= 'z')
//             str[i] = str[i] - 32;
//         i++;
//     }
// }

// int main(void)
// {
//     t_list *list = ft_lstnew(ft_strdup("hello"));
//     list->next = ft_lstnew(ft_strdup("world"));
//     list->next->next = ft_lstnew(ft_strdup("42"));

//     printf("Before ft_lstiter:\n");
//     t_list *temp = list;
//     while (temp)
//     {
//         printf("%s ", (char *)temp->content);
//         temp = temp->next;
//     }
//     printf("\n");

//     ft_lstiter(list, &to_upper);

//     printf("After ft_lstiter:\n");
//     temp = list;
//     while (temp)
//     {
//         printf("%s ", (char *)temp->content);
//         temp = temp->next;
//     }
//     printf("\n");

//     while (list)
//     {
//         t_list *next = list->next;
//         free(list->content);
//         free(list);
//         list = next;
//     }

//     return (0);
// }