/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 17:45:20 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:17:08 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t pos;

	pos = 0;
	if (n == 0)
		return (0);
	while (s1[pos] && s2[pos] && pos < (n - 1) && s1[pos] == s2[pos])
		pos++;
	return ((unsigned char)s1[pos] - (unsigned char)s2[pos]);
}
