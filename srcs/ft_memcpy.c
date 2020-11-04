/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 14:52:34 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:16:22 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t count;

	if (dst == NULL && src == NULL)
		return (NULL);
	count = 0;
	while (count < n)
	{
		*(unsigned char*)dst = *(unsigned char*)src;
		dst++;
		src++;
		count++;
	}
	return (dst - count);
}
