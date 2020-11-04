/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:59:10 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:59:51 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t pos;

	pos = 0;
	while (s1[pos] && s2[pos] && s1[pos] == s2[pos])
		pos++;
	return ((unsigned char)s1[pos] - (unsigned char)s2[pos]);
}
