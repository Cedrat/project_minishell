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

int		ft_count_quotes(char *arg)
{
	int	i;
	int	sg_qt;
	int	db_qt;

	i = 0;
	sg_qt = 0;
	db_qt = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' && db_qt % 2 == 0)
			sg_qt++;
		else if (arg[i] == '\"' && sg_qt % 2 == 0)
			db_qt++;
		i++;
	}
	if (sg_qt % 2 != 0)
		sg_qt--;
	if (db_qt % 2 != 0)
		db_qt--;
	return (sg_qt + db_qt);
}

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
	count += ft_count_quotes(arg);
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
