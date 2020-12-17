/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:46:20 by dchampda          #+#    #+#             */
/*   Updated: 2020/12/17 16:53:36 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static	void	print_export(char *str, int fd)
{
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
}

void			display_export(char **char_list, int fd)
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
		print_export(str, fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
	ft_free_tab(temp_tab_char);
}

void			export_env(t_shell *shell, char *arg)
{
	if (env_exist(shell->argenv, arg) && ft_charispresent(arg, '='))
		modify_env(shell->argenv, arg);
	else if (env_exist(shell->argenv, arg))
		return ;
	else
		shell->argenv = add_env(shell->argenv, arg);
}

int				ft_export(t_shell *shell)
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
