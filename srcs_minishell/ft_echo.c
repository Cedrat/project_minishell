#include "../header/minishell.h"

void	ft_init_echo(t_echo *config, int *i, char **args)
{
	config->token = 0;
	config->sg_qt = 0;
	config->db_qt = 0;
	config->backslash = 0;
	config->option_n = 0;
	if (ft_strcmp(args[1], "-n") == 0)
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
		if (arg[i] == '\'')
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
		if ((i == 0 && arg[i] == '\"') || (arg[i] == '\"' && arg[i - 1] != '\\')
			|| (arg[i] == '\"' && arg[i - 1] == '\\' && config->backslash % 2 == 0))
		{
			if (config->sg_qt == 0 && config->db_qt == 0)
				config->token = 2;
			config->db_qt++;
		}
		if (config->db_qt % 2 == 0)
			return (i);
		i++;
	}
	return (i);
}

void	ft_echo_config(t_echo *config, char **args)
{
	int		i;
	int 	j;

	ft_init_echo(config, &i, args);
	while (args[i])
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			if (args[i][j] == '\\')
				config->backslash++;
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

int	ft_dollar_sign(char *args, t_shell *shell, int *i, int fd)
{
	if (args[*i] == '$' &&  args[*i + 1] && args[*i + 1] == '?')
	{
		ft_putnbr_fd(shell->echo->signal, fd);
		*i = *i + 2;
		return (1);
	}
	else if (args[*i] == '$' &&  args[*i + 1] &&
		!ft_strchr(" \"\\\'\0\n", args[*i + 1]))
	{
		shell->echo->var_name = ft_extract_var_name(args, i);
		shell->echo->var_path = ft_get_var(shell->argenv,
									shell->echo->var_name);
		if (shell->echo->var_path)
			ft_putstr(shell->echo->var_path);
		free(shell->echo->var_path);
		free(shell->echo->var_name);
		return (1);
	}
	return (0);
}

void	ft_single_qt(t_echo *config, char *args, char **argenv, t_shell *shell)
{
	int 	i;
	int		j;

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
	int 	i;

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
				|| (args[i] == '\\' && args[i + 1] == '\"'))
			i++;
		if ((args[i] != '\"') || (args[i] == '\"' && i >= 2 
			&& args[i - 1] == '\\' && args[i - 2] != '\\'))
			ft_putchar_fd(args[i], shell->fd);
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
	int 	i;

	i = 0;
	while (args[i] != '\0')
	{
		if (args[i] == '$' && (ft_dollar_sign(args, shell, &i, shell->fd)))
				break;
		else if (i == 0 && args[i] == '~' && !args[i + 1]
			|| args[i] == '~' && !args[i + 1] && !args[i - 1])
			ft_echo_pwd(shell, &i);
		else if (args[i] == '\'' || args[i] == '\"')
		{
			if (args[i] == '\'')
				ft_single_qt(config, &args[i], argenv, shell);
			else if (args[i] == '\"')
				ft_double_qt(config, &args[i], argenv, shell);
			return ;
		}
		else if ((args[i] == '\\' && args[i + 1] == '\\')
				|| (args[i] == '\\' && args[i + 1] == '\"'))
			i++;
		ft_putchar_fd(args[i], shell->fd);
		if (args[i])
			i++;
	}
}

int		ft_echo(t_shell *shell)
{
	int 	i;

	if (!shell->args[1])
		return (0);
	shell->echo->signal = shell->signal;
	ft_echo_config(shell->echo, shell->args);
	if (shell->echo->sg_qt % 2 != 0 || shell->echo->db_qt % 2 != 0)
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
