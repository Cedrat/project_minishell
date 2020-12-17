/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchampda <dchampda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:14:09 by dchampda          #+#    #+#             */
/*   Updated: 2020/12/17 18:17:17 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_single_qt(t_echo *config, char *args, char **argenv, t_shell *shell)
{
	int		i;

	i = 0;
	while (args[i] != '\0')
	{
		if (args[i] == '\'')
			config->sg_qt--;
		if (config->sg_qt % 2 == 0)
		{
			if (args[i + 1] == '\"')
				ft_double_qt(config, &args[i + 1], argenv, shell);
			else if (args[i + 1] != '\0')
				ft_no_qt(config, &args[i + 1], argenv, shell);
			return ;
		}
		if (args[i] != '\'')
			ft_putchar_fd(args[i], shell->fd);
		i++;
	}
}

void	ft_double_qt(t_echo *config, char *args, char **argenv, t_shell *shell)
{
	int		i;

	i = 0;
	while (args[i] != '\0')
	{
		if (args[i] == '$')
			ft_dollar_sign(args, shell, &i, shell->fd);
		if (args[i] == '\"')
			config->db_qt--;
		if (config->db_qt % 2 == 0)
		{
			if (args[i + 1] == '\'')
				ft_single_qt(config, &args[i + 1], argenv, shell);
			else if (args[i + 1] != '\0')
				ft_no_qt(config, &args[i + 1], argenv, shell);
			return ;
		}
		else if ((args[i] == '\\' && args[i + 1] == '\\')
			|| (args[i] == '\\' && ft_strchr("\"$", args[i + 1])))
			i++;
		if (args[i] != '\"' || (i > 0 && args[i - 1] == '\\'))
			ft_putchar_fd(args[i], shell->fd);
		if (args[i])
			i++;
	}
}

void	ft_echo_pwd(t_shell *shell, int *i)
{
	shell->newline = 1;
	ft_pwd(shell);
	shell->newline = 0;
	*i += 1;
}

void	ft_no_qt(t_echo *config, char *args, char **argenv, t_shell *shell)
{
	int		i;

	i = 0;
	while (args[i] != '\0')
	{
		if (args[i] == '$')
			ft_dollar_sign(args, shell, &i, shell->fd);
		else if ((i == 0 && args[i] == '~' && !args[i + 1])
			|| (args[i] == '~' && !args[i + 1] && !args[i - 1]))
			ft_echo_pwd(shell, &i);
		if (args[i] == '\'' || args[i] == '\"')
		{
			if (args[i] == '\'')
				ft_single_qt(config, &args[i], argenv, shell);
			else if (args[i] == '\"')
				ft_double_qt(config, &args[i], argenv, shell);
			return ;
		}
		else if ((args[i] == '\\' && args[i + 1] != '$')
			|| (args[i] == '\\' && ft_count_bs(&args[i]) % 2 != 0))
			i++;
		ft_putchar_fd(args[i], shell->fd);
		if (args[i])
			i++;
	}
}

int		ft_echo(t_shell *shell)
{
	int		i;

	if (!shell->args[1])
		return (-1);
	ft_echo_config(shell->echo, shell->args);
	if (shell->echo->sg_qt % 2 != 0 || shell->echo->db_qt % 2 != 0
		|| shell->echo->backslash == -1)
		return (shell->signal = -3);
	if (shell->echo->option_n == 1)
		i = 2;
	else
		i = 1;
	while (shell->args[i])
	{
		if (shell->echo->token == 1 && shell->args[i][0] == '\'')
			ft_single_qt(shell->echo, shell->args[i], shell->argenv, shell);
		else if (shell->echo->token == 2 && shell->args[i][0] == '\"')
			ft_double_qt(shell->echo, shell->args[i], shell->argenv, shell);
		else
			ft_no_qt(shell->echo, shell->args[i], shell->argenv, shell);
		if (shell->args[i + 1])
			ft_putstr_fd(" ", shell->fd);
		i++;
	}
	return (shell->signal = 0);
}
