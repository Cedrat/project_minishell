/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:28:37 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/19 16:09:22 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int		ft_count_doll(char *arg)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	**check_arg_value(char **tab, t_shell *shell, size_t *i)
{
	if (ft_strcmp("", tab[*i]) != 0)
		tab = add_split_arg(tab, (int *)i);
	else if (tab[*i + 1])
	{
		tab = ft_remove_in_tab(tab, "");
		shell->is_command = 1;
		(*i)--;
	}
	return (tab);
}
