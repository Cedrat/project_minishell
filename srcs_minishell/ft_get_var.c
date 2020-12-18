/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:19:21 by dchampda          #+#    #+#             */
/*   Updated: 2020/12/18 20:25:31 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ft_strndupl(const char *s, int len)
{
	char	*copy;
	int		count;

	count = 0;
	if (!(copy = malloc(sizeof(char) * (len + 1))))
		return (0);
	while (count <= len)
	{
		copy[count] = s[count];
		count++;
	}
	return (copy);
}

char	*ft_extract_var_name(char *arg, int *j)
{
	int		i;
	char	*str;

	*j += 1;
	i = *j;
	while (!ft_strchr("$ \"\\\'\0", arg[i]))
		i++;
	if (!(str = malloc(sizeof(char) * (i - *j) + 2)))
		return (NULL);
	i = 0;
	while (!ft_strchr("$ \"\\\'\0", arg[*j]))
	{
		str[i] = arg[*j];
		*j += 1;
		i++;
	}
	str[i] = '=';
	str[i + 1] = '\0';
	return (str);
}

char	*ft_get_var(char **argenv, char *tofind)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (argenv[i])
	{
		if (ft_strncmp(argenv[i], tofind, ft_strlen(tofind)) == 0)
		{
			while (argenv[i][j] && argenv[i][j] != '=')
				j++;
			j++;
			path = ft_strndupl(&argenv[i][j], (ft_strlen(argenv[i]) - j));
			return (path);
		}
		i++;
	}
	return (ft_strdup(""));
}

char	*ft_get_var_free(char **argenv, char *tofind)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (argenv[i])
	{
		if (ft_strncmp(argenv[i], tofind, ft_strlen(tofind)) == 0)
		{
			while (argenv[i][j] && argenv[i][j] != '=')
				j++;
			j++;
			path = ft_strndupl(&argenv[i][j], (ft_strlen(argenv[i]) - j));
			free(tofind);
			return (path);
		}
		i++;
	}
	free(tofind);
	return (ft_strdup(""));
}
