/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 16:37:33 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:16:44 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*node;

	node = *alst;
	if (node == NULL)
	{
		*alst = new;
		return ;
	}
	while (node->next)
		node = node->next;
	node->next = new;
}
