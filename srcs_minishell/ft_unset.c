/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:53:39 by dchampda          #+#    #+#             */
/*   Updated: 2020/12/16 19:39:55 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static	void	check_syntax(char **arg_tab)
{
	size_t	o;
	char	*str;

	o = 0;
	while (arg_tab[o + 1])
	{
		str = ft_str_treatement(arg_tab[o + 1]);
		if (!(ft_is_varenv(str)) || (ft_charispresent(arg_tab[o + 1], '=')))
			ft_strcat_fd("minishell: env: « ", arg_tab[o + 1],
												" » : bad variable name\n", 2);
		free(str);
		o++;
	}
}

static	size_t	length_before_equal(char *str)
{
	size_t p;

	p = 0;
	while (str[p] && str[p] != '=')
		p++;
	return (p);
}

char			**ft_malloc_tab(char **tab)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab[i])
		i++;
	if (!(new_tab = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	return (new_tab);
}

char			**ft_remove_in_tab(char **tab, char *str)
{
	size_t	i;
	size_t	p;
	char	**new_tab;
	size_t	found;

	i = 0;
	found = 0;
	if (!(new_tab = ft_malloc_tab(tab)))
		return (NULL);
	while (tab[i + found])
	{
		p = 0;
		while (str[p] && str[p] != '=')
			p++;
		if (found != 1 && (!(ft_strncmp(tab[i + found], str, p))))
			found++;
		else
		{
			new_tab[i] = ft_strdup(tab[i + found]);
			i++;
		}
	}
	ft_free_tab(tab);
	new_tab[i] = 0;
	return (new_tab);
}

int				ft_unset(t_shell *shell)
{
	size_t	i;
	char	*str;
	size_t	p;
	size_t	o;

	check_syntax(shell->args);
	o = 0;
	while (shell->args[o])
	{
		i = 0;
		while (shell->argenv[i])
		{
			str = shell->argenv[i];
			p = length_before_equal(str);
			if (!(ft_strncmp(shell->args[o], str, p)))
			{
				shell->argenv = ft_remove_in_tab(shell->argenv, shell->args[o]);
				break ;
			}
			i++;
		}
		o++;
	}
	return (shell->signal = 0);
}
