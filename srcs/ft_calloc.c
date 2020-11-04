/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:42:15 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:16:47 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (!(str = malloc(size * count)))
		return (0);
	ft_memset(str, 0, size * count);
	return (str);
}
