/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:19:21 by dchampda          #+#    #+#             */
/*   Updated: 2020/11/09 16:19:24 by dchampda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ft_strncpy(char *src, char *dest, int len)
{
	int i;

	i = 0;
	while (src[i] != '\0' && len > 0)
	{
		dest[i] = src[i];
		i++;
		len--;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_extract_var_name(char *arg, int *j)
{
	int 	i;
	char	*str;

	*j += 1;
	i = *j;
	while (!ft_strchr(" \"\\\'\0", arg[i]))
		i++;
	str = malloc(sizeof(char) * (i - *j) + 2);
	i = 0;
	while (!ft_strchr(" \"\\\'\0", arg[*j]))
	{
		str[i] = arg[*j];
		*j += 1;
		i++;
	}
	str[i] = '=';
	str[i + 1] = '\0';
	*j += 1;
	return (str);
}

char	*ft_get_var(char **argenv, char *tofind)
{
	char	*path;
	int 	i;
	int		j;

	i = 0;
	j = 0;
	while (argenv[i])
	{
		if (ft_strncmp(argenv[i], tofind, ft_strlen(tofind)) == 0)
		{
			while (argenv[i][j] != '=')
				j++;
			j++;
			path = malloc(sizeof(char) * ft_strlen(argenv[i]) - j);
			ft_strncpy(&argenv[i][j], path, ft_strlen(argenv[i]) - j);
			return (path);
		}
		i++;
	}
	return ("");
}