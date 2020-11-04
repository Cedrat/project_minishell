/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 13:48:10 by lnoaille          #+#    #+#             */
/*   Updated: 2020/11/04 17:13:39 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subcopy;
	size_t	count;

	count = 0;
	if (!(subcopy = malloc(sizeof(char) * (len + 1))))
		return (0);
	if (start > ft_strlen(s))
		len = 0;
	while (count < len)
	{
		subcopy[count] = s[count + start];
		count++;
	}
	subcopy[count] = '\0';
	return (subcopy);
}
