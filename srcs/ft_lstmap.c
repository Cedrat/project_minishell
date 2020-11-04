/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:56:31 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:16:36 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*new;
	t_list	*lstadd;
	void	*newelem;

	lstadd = NULL;
	temp = lst;
	while (temp)
	{
		if (!(newelem = (*f)(temp->content)))
			ft_lstdelone(lst, (*del));
		if (!(new = ft_lstnew(newelem)))
			return (0);
		if (newelem)
			ft_lstadd_back(&lstadd, new);
		temp = temp->next;
		lst = lst->next;
	}
	return (lstadd);
}
