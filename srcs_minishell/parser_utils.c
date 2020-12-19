/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 17:01:14 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/19 16:08:13 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static	char	*join_all_args(char **var_path, char *arg)
{
	int	j;

	j = 0;
	while (var_path[j])
	{
		arg = ft_strjoin_freeall(arg, var_path[j]);
		j++;
	}
	return (arg);
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
		var_path[j] = ft_extract_vars(arg, &i);
		if (var_path[j][0])
			var_path[j] = ft_get_var_free(shell->argenv, var_path[j]);
		j++;
		count--;
	}
	var_path[j] = NULL;
	free(arg);
	arg = ft_strdup("");
	arg = join_all_args(var_path, arg);
	if (ft_strcmp("", arg) == 0)
		shell->is_command = 0;
	free(var_path);
	return (arg);
}

static	char	*ft_cut_replace(char *str, t_shell *shell, size_t j)
{
	char	*pt1;
	char	*pt2;
	char	*pt3;

	pt1 = ft_substr(str, 0, j);
	pt2 = ft_itoa(shell->signal);
	if (str[j + 2] && ((int)ft_strlen(str) > (int)j + 2))
		pt3 = ft_substr(str, j + 2, (int)ft_strlen(str) - (j + 2));
	else
		pt3 = ft_strdup("");
	free(str);
	str = ft_strjoin_freeall(pt1, pt2);
	str = ft_strjoin_freeall(str, pt3);
	return (str);
}

static	char	*ft_get_doll(char *tab, t_shell *shell, size_t *j)
{
	char	*str;

	str = ft_str_treatement(tab);
	free(tab);
	*j = 0;
	while (str[*j])
	{
		if (str[*j + 1] && str[*j] == '$' && str[*j + 1] == '?')
			str = ft_cut_replace(str, shell, *j);
		*j += 1;
	}
	tab = ft_strdup(str);
	free(str);
	return (tab);
}

char			**ft_dollar(char **tab, t_shell *shell)
{
	size_t i;
	size_t j;

	ft_init(&i, &j);
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
		if (found_doll_signal(tab[i]))
			tab[i] = ft_get_doll(tab[i], shell, &j);
		else if (found_doll_var(tab[i]))
		{
			tab[i] = ft_replace_var(shell, tab[i], (int)j);
			tab = check_arg_value(tab, shell, &i);
		}
		i++;
	}
	return (tab);
}
