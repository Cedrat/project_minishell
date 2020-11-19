/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:21:37 by dchampda          #+#    #+#             */
/*   Updated: 2020/05/13 12:21:38 by dchampda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char		*gnl_strndup(char *str, int len)
{
	char	*copy;
	int		i;

	i = 0;
	if (!(copy = malloc(sizeof(char) * len + 1)))
		return (copy);
	while (str[i] != '\0' && i < len)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int			find_n(char *buffer, char c)
{
	int		i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char		*copy_after_n(char *str, int start)
{
	int		i;
	int		len;
	char	*tmp;

	len = ft_strlen(str);
	i = 0;
	if (!str || (!(tmp = (char *)malloc(len - start + 1))))
		return (NULL);
	while (str[start])
	{
		tmp[i] = str[start];
		start++;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
