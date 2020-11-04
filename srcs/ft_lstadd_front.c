/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 14:10:26 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:16:43 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	t_list *node;
	t_list *tmp;

	tmp = new;
	node = *alst;
	if (node == NULL)
	{
		*alst = tmp;
		return ;
	}
	new->next = node;
	*alst = new;
	new = tmp;
}
