/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 14:56:34 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:15:35 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*copy;
	int		count;

	if (!(copy = ft_strdup(s)))
		return (0);
	count = 0;
	while (copy[count])
	{
		copy[count] = (*f)(count, s[count]);
		count++;
	}
	return (copy);
}
