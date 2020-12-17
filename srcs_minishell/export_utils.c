/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 16:53:52 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/17 16:56:59 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

size_t			sizeofenv(char **argenv)
{
	size_t	i;

	i = 0;
	while (argenv[i])
		i++;
	return (i);
}

int				ft_is_varenv(char *env)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(env[i]) && env[i] != '_')
		return (0);
	i++;
	while (env[i] != '=' && env[i])
	{
		if (!(ft_isalnum(env[i])))
			return (0);
		i++;
	}
	return (1);
}

int				env_exist(char **env, char *arg)
{
	size_t	i;
	char	*str;

	i = 0;
	while (arg[i] != '=' && arg[i])
		i++;
	while (*env)
	{
		i = 0;
		str = *env;
		while (str[i] != '=' && str[i])
			i++;
		if (!(ft_strncmp(arg, str, i)))
			return (1);
		env++;
	}
	return (0);
}

char			**add_env(char **arg, char *str)
{
	char	**new_tab;
	size_t	i;

	i = 0;
	while (arg[i])
		i++;
	if (!(new_tab = malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = 0;
	while (arg[i])
	{
		new_tab[i] = ft_strdup(arg[i]);
		i++;
	}
	new_tab[i] = ft_strdup(str);
	free(str);
	new_tab[i + 1] = 0;
	ft_free_tab(arg);
	return (new_tab);
}

void			modify_env(char **argenv, char *str)
{
	size_t	i;
	size_t	p;

	i = 0;
	p = 0;
	while (argenv[p])
	{
		i = 0;
		while (argenv[p][i] != '=' && argenv[p][i])
			i++;
		if (!(ft_strncmp(str, argenv[p], i)))
		{
			free(argenv[p]);
			argenv[p] = str;
		}
		p++;
	}
}
