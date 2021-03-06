/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 16:44:36 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/17 18:18:48 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_init_echo(t_echo *config, int *i, char **args)
{
	config->token = 0;
	config->sg_qt = 0;
	config->db_qt = 0;
	config->backslash = 0;
	config->option_n = 0;
	if (ft_strcmp(args[1], "-n") == 0 || ft_strcmp(args[1], "'-n'") == 0
		|| ft_strcmp(args[1], "\"-n\"") == 0)
	{
		*i = 2;
		config->option_n = 1;
	}
	else
		*i = 1;
}

int		ft_config_single_qt(t_echo *config, char *arg, int i)
{
	while (arg[i] != '\0')
	{
		if ((i > 0 && arg[i - 1] != '\\' && arg[i] == '\''
				&& config->sg_qt % 2 == 0)
			|| (i > 0 && arg[i - 1] != '\\' && arg[i] == '\''
				&& config->sg_qt % 2 != 0)
			|| (i > 0 && arg[i - 1] == '\\' && arg[i] == '\''
				&& config->sg_qt % 2 != 0)
			|| (i > 0 && arg[i - 1] == '\\' && arg[i] == '\''
				&& config->sg_qt % 2 == 0 && config->backslash % 2 == 0)
			|| (i == 0 && arg[i] == '\''))
		{
			if (config->sg_qt == 0 && config->db_qt == 0)
				config->token = 1;
			config->sg_qt++;
		}
		if (config->sg_qt % 2 == 0)
			return (i);
		i++;
	}
	return (i);
}

int		ft_config_double_qt(t_echo *config, char *arg, int i)
{
	while (arg[i] != '\0')
	{
		if (arg[i] == '\\')
		{
			if (ft_check_bs(arg, &i, config) == -1)
				config->backslash = -1;
		}
		if ((i > 1 && arg[i - 1] != '\\' && arg[i] == '\"')
			|| (i == 0 && arg[i] == '\"')
			|| (arg[i] == '\"' && config->backslash % 2 == 0))
		{
			if (config->sg_qt == 0 && config->db_qt == 0)
				config->token = 2;
			config->db_qt++;
		}
		if (config->db_qt % 2 == 0)
			return (i);
		if (arg[i])
			i++;
	}
	config->db_qt = -1;
	return (i);
}

void	ft_echo_config(t_echo *config, char **args)
{
	int		i;
	int		j;

	ft_init_echo(config, &i, args);
	while (args[i])
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			if (args[i][j] == '\\')
				config->backslash++;
			if (ft_check_bs(args[i], &j, config) == -1)
			{
				config->backslash = -1;
				break ;
			}
			if (args[i][j] == '\'')
				j = ft_config_single_qt(config, args[i], j);
			else if (args[i][j] == '\"')
				j = ft_config_double_qt(config, args[i], j);
			if (args[i][j])
				j++;
		}
		i++;
	}
}

int		ft_dollar_sign(char *args, t_shell *shell, int *i, int fd)
{
	if ((!args[*i + 1]) || (args[*i + 1] == '\"') || (args[*i + 1] == '$')
		|| (*i > 0 && args[*i - 1] == '\\' && ft_count_bs(args) % 2 != 0)
		|| (args[*i] == '$' && args[*i + 1] && args[*i + 1] == ' '))
		return (*i);
	if (args[*i] == '$' && args[*i + 1] && args[*i + 1] == '?')
	{
		ft_putnbr_fd(shell->signal, fd);
		*i = *i + 2;
	}
	else if (args[*i] == '$' && ft_strchr("0123456789", args[*i + 1]))
		*i = *i + 2;
	else if (args[*i] == '$' && args[*i + 1] &&
		!ft_strchr(" \"\\\'\0\n", args[*i + 1]))
	{
		shell->echo->var_name = ft_extract_var_name(args, i);
		shell->echo->var_path = ft_get_var(shell->argenv,
									shell->echo->var_name);
		if (shell->echo->var_path)
			ft_putstr(shell->echo->var_path);
		free(shell->echo->var_path);
		free(shell->echo->var_name);
	}
	else
		*i = *i + 2;
	return (1);
}
