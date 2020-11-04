/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 15:18:33 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:16:21 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	size_t			count;
	unsigned char	*word;

	word = s;
	count = 0;
	while (count < len)
	{
		word[count] = c;
		count++;
	}
	return (s);
}
