/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_extract_vars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <dchampda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 16:57:01 by user42            #+#    #+#             */
/*   Updated: 2020/12/19 16:57:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*treat_db_qt(char *arg, int *j)
{
	int		i;
	char	*str;

	*j += 1;
	i = *j;
	while (!ft_strchr("$ \"\\\0", arg[i]))
		i++;
	if (!(str = malloc(sizeof(char) * (i - *j) + 2)))
		return (NULL);
	i = 0;
	while (!ft_strchr("$ \"\\\0", arg[*j]))
	{
		str[i] = arg[*j];
		*j += 1;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*treat_sg_qt(char *arg, int *j)
{
	int		i;
	char	*str;

	*j += 1;
	i = *j;
	while (!ft_strchr("$ \\\'\0", arg[i]))
		i++;
	if (!(str = malloc(sizeof(char) * (i - *j) + 2)))
		return (NULL);
	i = 0;
	while (!ft_strchr("$ \\\'\0", arg[*j]))
	{
		str[i] = arg[*j];
		*j += 1;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*treat_var(char *arg, int *j)
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

char	*ft_extract_vars(char *arg, int *j)
{
	char	*str;

	if (arg[*j] == '\'')
		str = treat_sg_qt(arg, j);
	else if (arg[*j] == '\"')
		str = treat_db_qt(arg, j);
	else
		str = treat_var(arg, j);
	return (str);
}
