#include "../header/minishell.h"

void	ft_init_echo(t_echo *config)
{
	config->token = 0;
	config->sg_qt = 0;
	config->db_qt = 0;
	config->backslash = 0;
	config->option_n = 0;
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
		if ((arg[i] == '\"' && arg[i - 1] != '\\')
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

	ft_init_echo(config);
	if (ft_strcmp(args[1], "-n") == 0)
	{
		i = 2;
		config->option_n = 1;
	}
	else
		i = 1;
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
			j++;
		}
		i++;
	}
//Test des variables
//printf("%d %d %d\n", config->sg_qt, config->db_qt, config->token);
}



void	ft_dollar_sign(char *args, char **argenv, t_echo *config, int *i)
{
	if (args[*i] == '$' && args[*i + 1] == '?')
	{
		ft_putnbr_fd(config->signal, 1);
		*i += 2;
	}
	if (args[*i] == '$' && !ft_strchr(" \"\\\'\0\n", args[*i + 1]))
	{
		config->var_name = ft_extract_var_name(args, i);
		config->var_path = ft_get_var(argenv, config->var_name);
		if (config->var_path)
			ft_putstr(config->var_path);
	}
}

void	ft_single_qt(t_echo *config, char *args, char **argenv)
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
				ft_double_qt(config, &args[i + 1], argenv);
			else if (args[i + 1] != '\0')
				ft_no_qt(config, &args[i + 1], argenv);
			return ;
		}
		if (args[i] != '\'')
			ft_putchar_fd(args[i], 1);
		i++;
	}
}

void	ft_double_qt(t_echo *config, char *args, char **argenv)
{
	int 	i;

	i = 0;
	while (args[i] != '\0')
	{
		if (args[i] == '$')
			ft_dollar_sign(args, argenv, config, &i);
		if (args[i] == '\"')
			config->db_qt--;
		if (config->db_qt % 2 == 0)
		{
			if (args[i + 1] == '\'')
				ft_single_qt(config, &args[i + 1], argenv);
			else if (args[i + 1] != '\0')
				ft_no_qt(config, &args[i + 1], argenv);
			return ;
		}
		else if ((args[i] == '\\' && args[i + 1] == '\\')
				|| (args[i] == '\\' && args[i + 1] == '\"'))
			i++;
		if ((args[i] != '\"')
			|| (args[i] == '\"' && args[i - 1] == '\\' && args[i - 2] != '\\'))
			ft_putchar_fd(args[i], 1);
		i++;
	}
}

void	ft_no_qt(t_echo *config, char *args, char **argenv)
{
	int 	i;
	char	str[256];

	i = 0;
	while (args[i] != '\0')
	{
		if (args[i] == '|' || args[i] == ';') 	//Gestion future
			break ;								//Gestion future
		if (args[i] == '$')
			ft_dollar_sign(args, argenv, config, &i);
		else if (args[i] == '~' && !args[i + 1] && !args[i - 1])
		{
			ft_putstr(getcwd(str, 256));
			i++;
		}
		else if (args[i] == '\'' || args[i] == '\"')
		{
			if (args[i] == '\'')
				ft_single_qt(config, &args[i], argenv);
			else if (args[i] == '\"')
				ft_double_qt(config, &args[i], argenv);
			return ;
		}
		else if ((args[i] == '\\' && args[i + 1] == '\\')
				|| (args[i] == '\\' && args[i + 1] == '\"'))
			i++;
		ft_putchar_fd(args[i], 1);
		i++;
	}
}

int		ft_echo(t_shell *shell)
{
	int 	i;

	//shell->echo.signal = shell->signal;
	//Gestion d'erreurs
	ft_echo_config(shell->echo, shell->args);
	if (shell->echo->sg_qt % 2 != 0 || shell->echo->db_qt % 2 != 0) //Nombre impair de quotes
	{
		ft_putstr("Wrong number of quotes :");
		return (-2);
	}

	if (shell->echo->option_n == 1)
		i = 2;
	else
		i = 1;

	//Gestion affichage
	while (shell->args[i])
	{
		if (shell->echo->token == 1 && shell->args[i][0] == '\'')  		//Gestion avec ''
			ft_single_qt(shell->echo, shell->args[i], shell->argenv);
		else if (shell->echo->token == 2 && shell->args[i][0] == '\"')  	//Gestion avec ""
			ft_double_qt(shell->echo, shell->args[i], shell->argenv);
		else
			ft_no_qt(shell->echo, shell->args[i], shell->argenv);
		if (shell->args[i + 1])
			ft_putstr(" ");
		i++;
	}
	return (shell->signal = 1);
}
