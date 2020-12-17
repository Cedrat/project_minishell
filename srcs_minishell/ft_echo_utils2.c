/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:18:08 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/17 18:27:23 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int		ft_count_bs(char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i] == '\\')
		i++;
	while (i >= 0)
	{
		if (arg[i] == '\\')
			count++;
		i--;
	}
	return (count);
}

int		ft_check_bs(char *arg, int *i, t_echo *config)
{
	int	count;

	count = 0;
	while (arg[*i] == '\\')
	{
		if (arg[*i] == '\\')
			count++;
		if (*i > 0 && arg[*i + 1] && count % 2 != 0 && arg[*i] == '\\'
			&& arg[*i + 1] == '\"' && arg[*i + 2] != '\"')
			return (-1);
		else if (arg[*i] == '\\' && !arg[*i + 1] && count % 2 != 0)
			return (-1);
		*i += 1;
	}
	return (config->backslash = count);
}
