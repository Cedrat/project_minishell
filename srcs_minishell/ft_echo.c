#include "../header/minishell.h"

void	ft_echo_config(t_echo *config, char **args)
{
	int		i;
	int 	j;

	config->token = 0;
	config->sg_qt = 0;
	config->db_qt = 0;
	config->backslash = 0;
	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			if (args[i][j] == '\\')
				config->backslash++;
			if (args[i][j] == '\'')
			{
				if (config->sg_qt == 0 && config->db_qt == 0)
					config->token = 1;
				config->sg_qt++;
			}
			else if ((args[i][j] == '\"' && args[i][j - 1] != '\\')
			|| (args[i][j] == '\"' && args[i][j - 1] == '\\' && config->backslash % 2 == 0))
			{
				if (config->sg_qt == 0 && config->db_qt == 0)
					config->token = 2;
				config->db_qt++;
			}
			j++;
		}
		i++;
	}
//Test des variables
//printf("%d %d %d %s\n", config->sg_qt, config->db_qt, config->first_token, config->token);
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
		if (config->sg_qt % 2 == 0 && args[i + 1] == '\"')
		{
			ft_double_qt(config, &args[i + 1], argenv);
				return ;
		}
		else if (config->sg_qt % 2 == 0 && args[i + 1] != '\0')
		{
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
		if (config->db_qt % 2 == 0 && args[i + 1] == '\'')
		{
			ft_single_qt(config, &args[i + 1], argenv);
			return ;
		}
		else if (config->db_qt == 0 && args[i + 1] != '\0')
		{
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
			break ;						//Gestion future
		if (args[i] == '$')
			ft_dollar_sign(args, argenv, config, &i);
		else if (args[i] == '~' && args[i + 1] == '\0' && !args[i - 1])
		{
			ft_putstr(getcwd(str, 256));
			i++;
		}
		if (args[i] == '\'')
		{
			ft_single_qt(config, &args[i], argenv);
			return ;
		}
		else if (args[i] == '\"')
		{
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
	t_echo	config;
	int 	i;

	i = 1;
	config.signal = shell->signal;
	//Gestion d'erreurs
	ft_echo_config(&config, shell->args);
	if ((config.token == 1 && (config.sg_qt % 2 != 0)) 
		|| (config.token == 2 && (config.db_qt % 2 != 0))) //Nombre impair de quotes
	{
		ft_putstr("Wrong number of quotes :");
		return (-2);
	}
	while (shell->args[i])
	{
		if (config.token == 1 && shell->args[i][0] == '\'')  //Gestion avec ''
			ft_single_qt(&config, shell->args[i], shell->argenv);
		else if (config.token == 2 && shell->args[i][0] == '\"')  //Gestion avec ""
			ft_double_qt(&config, shell->args[i], shell->argenv);
		else  //Gestion sans quotes
			ft_no_qt(&config, shell->args[i], shell->argenv);
		ft_putstr(" ");
		i++;
	}
	return (shell->signal = 1);
}