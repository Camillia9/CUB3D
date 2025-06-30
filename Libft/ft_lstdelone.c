/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:50:57 by camansou          #+#    #+#             */
/*   Updated: 2024/11/18 14:32:29 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}

// void delete_content(void *content)
// {
//     free(content);
// }

// int main(void)
// {
//     char *str = ft_strdup("Hello World!");
//     if (!str)
//         return (1);

//     t_list *node = ft_lstnew(str);
//     if (!node)
//     {
//         free(str);
//         return (1);
//     }

//     printf("Content: %s\n", (char *)node->content);

//     ft_lstdelone(node, &delete_content);

//     return (0);
// }