/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:46:20 by dchampda          #+#    #+#             */
/*   Updated: 2020/12/03 16:46:21 by dchampda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	display_export(char **char_list, int fd)
{
	char	**temp_tab_char;
	char	*str;
	size_t	i;

	i = 0;
	temp_tab_char = ft_dup_arg(char_list);
	ft_tri_tab_str(temp_tab_char);
	while (temp_tab_char[i])
	{
		ft_putstr_fd("declare -x ", fd);
		str = temp_tab_char[i];
		while (*str != '=' && *str)
		{
			ft_putchar_fd(*str, fd);
			str++;
		}
		if (*str == '=')
		{
			ft_putchar_fd(*str, fd);
			str++;
			ft_putstr_fd("\"", fd);
			while (*str)
			{
				if (*str == '"')
					ft_putchar_fd('\\', fd);
				ft_putchar_fd(*str, fd);
				str++;
			}
			ft_putstr_fd("\"", fd);
		}
		ft_putchar_fd('\n', fd);
		i++;
	}
	ft_free_tab(temp_tab_char);
}

size_t	sizeofenv(char **argenv)
{
	size_t	i;

	i = 0;
	while (argenv[i])
		i++;
	return (i);
}

int		ft_is_varenv(char *env)
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

int		env_exist(char **env, char *arg)
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

char	**add_env(char **arg, char *str)
{
	char	**new_tab;
	size_t	i;

	i = 0;
	while (arg[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (arg[i])
	{
		new_tab[i] = ft_strdup(arg[i]);
		i++;
	}
	new_tab[i] = str;
	new_tab[i + 1] = 0;
	ft_free_tab(arg);
	return (new_tab);
}

void	modify_env(char **argenv, char *str)
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
			argenv[p] = str;
		p++;
	}
}

void	export_env(t_shell *shell, char *arg)
{
	if (env_exist(shell->argenv, arg) && ft_charispresent(arg, '='))
		modify_env(shell->argenv, arg);
	else if (env_exist(shell->argenv, arg))
		return ;
	else
		shell->argenv = add_env(shell->argenv, arg);
}

int		ft_export(t_shell *shell)
{
	int		i;
	char	*str;

	i = 0;
	while (shell->args[i + 1])
	{
		str = ft_str_treatement(shell->args[i + 1]);
		if (!(ft_is_varenv(str)))
		{
			ft_putstr("minishell: export: « ");
			ft_putstr(shell->args[i + 1]);
			ft_putstr(" » : bad variable name\n");
			free(str);
		}
		else
			export_env(shell, str);
		i++;
	}
	if (shell->args[1] == 0)
		display_export(shell->argenv, shell->fd);
	return (shell->signal = 0);
}
