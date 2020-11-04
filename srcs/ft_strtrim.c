/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 16:17:40 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 18:15:48 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	count;
	size_t	len_s1;
	char	*trimmed;

	len_s1 = ft_strlen(s1);
	count = 0;
	while (ft_strchr(set, s1[count]) && s1[count])
		count++;
	while (ft_strchr(set, s1[len_s1 - 1]) && len_s1 > count)
		len_s1--;
	trimmed = ft_substr((char *)s1, count, (len_s1 - count));
	return (trimmed);
}
