/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 17:01:14 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/17 17:55:15 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int				ft_count_doll(char *arg)
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

char			*ft_replace_var(t_shell *shell, char *arg, int i)
{
	char	**var_path;
	int		j;
	int		count;

	count = ft_count_doll(arg);
	if (!(var_path = malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	j = 0;
	while (count > 0)
	{
		var_path[j] = ft_extract_var_name(arg, &i);
		if (var_path[j][1])
			var_path[j] = ft_get_var_free(shell->argenv, var_path[j]);
		j++;
		count--;
	}
	var_path[j] = NULL;
	j = 0;
	free(arg);
	arg = ft_strdup("");
	while (var_path[j])
	{
		arg = ft_strjoin_freeall(arg, var_path[j]);
		j++;
	}
	free(var_path);
	return (arg);
}

static	char	*ft_cut_replace(char *str, t_shell *shell, int j)
{
	char	*pt1;
	char	*pt2;
	char	*pt3;

	pt1 = ft_substr(str, 0, j);
	pt2 = ft_itoa(shell->signal);
	if (str[j + 2] && ((int)ft_strlen(str) > j + 2))
		pt3 = ft_substr(str, j + 2, (int)ft_strlen(str) - (j + 2));
	else
		pt3 = ft_strdup("");
	free(str);
	str = ft_strjoin_freeall(pt1, pt2);
	str = ft_strjoin_freeall(str, pt3);
	return (str);
}

static	int		ft_check_doll(char *tab)
{
	int	j;

	j = 0;
	while (tab[j])
	{
		if (tab[j + 1] && tab[j] == '$' && tab[j + 1] == '?')
			return (j);
		j++;
	}
	return (j = 0);
}

char			**ft_dollar(char **tab, t_shell *shell)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		if ((i > 0 && ft_strcmp(tab[i - 1], "echo") == 0)
			|| ((tab[i][0] == '\'')))
			break ;
		if (ft_strcmp(tab[i], "$?") == 0)
		{
			free(tab[i]);
			tab[i] = ft_itoa(shell->signal);
		}
		if ((j = ft_check_doll(tab[i])) > 0)
			tab[i] = ft_cut_replace(tab[i], shell, j);
		if (tab[i][j] == '$' && tab[i][j + 1] && tab[i][j + 1] != '?')
		{
			tab[i] = ft_replace_var(shell, tab[i], j);
			tab = add_split_arg(tab, &i);
		}
		i++;
	}
	return (tab);
}
