/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_givewithoutquote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:51:56 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/15 18:53:30 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ft_give_without_quote(char *str)
{
	size_t	nb_dq;
	size_t	nb_sq;
	char	first_quote;
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			first_quote = str[i];
		i++;
	}
}
