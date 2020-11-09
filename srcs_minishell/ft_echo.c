#include "../header/minishell.h"

void	ft_echo_config(t_echo *config, char *args)
{
	int		i;

	config->token = 0;
	config->sg_qt = 0;
	config->db_qt = 0;
	config->backslash = 0;
	i = 0;
	while (args[i] != '\0')
	{
		if (args[i] == '\\')
			config->backslash++;
		if (args[i] == '\'')
		{
			if (config->sg_qt == 0 && config->db_qt == 0)
				config->token = 1;
			config->sg_qt++;
		}
		else if ((args[i] == '\"' && args[i - 1] != '\\')
		|| (args[i] == '\"' && args[i - 1] == '\\' && config->backslash % 2 == 0))
		{
			if (config->sg_qt == 0 && config->db_qt == 0)
				config->token = 2;
			config->db_qt++;
		}
		i++;
	}
//Test des variables
//printf("%d %d %d %s\n", config->sg_qt, config->db_qt, config->first_token, config->token);
}


void	ft_single_qt(t_echo *config, char *args)
{
	int 	i;
	int		j;
	char	*str;

	i = 0;
	while (args[i] != '\0')
	{
		if (args[i] != '\'')
			ft_putchar_fd(args[i], 1);
		if (args[i] == '|' || args[i] == ';') //Gestion future
			return ;
		i++;
	}
}



<<<<<<< HEAD
void	ft_double_qt(t_echo *config, char *args, char **argenv, int signal)
=======
void	ft_double_qt(t_echo *config, char *args, char **argenv)
>>>>>>> 65d886d1e94c08551b59d230a3bb8b0cb19f106e
{
	int 	i;

	i = 0;
	while (args[i] != '\0')
	{
		if (args[i] == '|' || args[i] == ';') //Gestion future
			return ;
		if (args[i] == '\"')
			config->db_qt--;
		if (config->db_qt == 0 && args[i + 1] == '\'')
<<<<<<< HEAD
		{
			ft_single_qt(config, &args[i + 1]);
			return ;
		}
		else if (args[i] == '$' && args[i + 1] == '?')
		{
			ft_putnbr_fd(signal, 1); //Doit renvoyer signal emit par derniere commande
			i += 2;			 //0=reussite, -1 = echec. Et on avance jusqu'à après le '?'
		}
=======
		{
			ft_single_qt(config, &args[i + 1]);
			return ;
		}
		/*else if (args[i][j] == '$' && args[i][j + 1] == '?')
		{
			ft_get_signal(); //Doit renvoyer signal emit par derniere commande
			j += 2;			 //0=reussite, -1 = echec. Et on avance jusqu'à après le '?'
		}*/
>>>>>>> 65d886d1e94c08551b59d230a3bb8b0cb19f106e
		if (args[i] == '$' && !ft_strchr(" \"\\\'\0\n", args[i + 1]))
		{
			config->var_name = ft_extract_var_name(args, &i);
			config->var_path = ft_get_var(argenv, config->var_name);
			if (config->var_path)
				ft_putstr(config->var_path);
		}
		else if (args[i] == '\\' && args[i + 1] == '\\' && args[i + 2] != '\\')
			i++;
		else if (args[i] == '\\' && args[i + 1] == '\"')
			i++;
		if (args[i] != '\"')
			ft_putchar_fd(args[i], 1);
		i++;
	}
}


void	ft_no_qt(t_echo *config, char *args, char **argenv)
{

}



int		ft_echo(t_shell *shell)
{
	t_echo	config;
	int 	i;

	i = 1;
	while (shell->args[i])
	{
		ft_echo_config(&config, shell->args[i]);
		//Gestion d'erreurs
		if ((config.token == 1 && (config.sg_qt % 2 != 0)) 
			|| (config.token == 2 && (config.db_qt % 2 != 0))) //Nombre impair de quotes
		{
			ft_putstr("Wrong number of quotes :");
			return (-2);
		}
<<<<<<< HEAD
		if (config.token == 1)  //Gestion avec ''
			ft_single_qt(&config, shell->args[i]);
		else if (config.token == 2)  //Gestion avec ""
			ft_double_qt(&config, shell->args[i], shell->argenv, shell->signal);
		else if (config.token == 0)  //Gestion sans quotes
=======

		//Gestion avec ''
		if (config.token == 1)
			ft_single_qt(&config, shell->args[i]);
		//Gestion avec ""
		else if (config.token == 2)
			ft_double_qt(&config, shell->args[i], shell->argenv);
		//Gestion sans quotes
		else if (config.token == 0)
>>>>>>> 65d886d1e94c08551b59d230a3bb8b0cb19f106e
		{
		//A gerer : else if (args[i][j] == '~')
					//ft_putstr(getcwd(str, 256));
		}
		else
<<<<<<< HEAD
			return (shell->signal = -1); //Pas de token = erreur
		ft_putstr(" ");
		i++;
	}
	return (shell->signal = 1);
=======
			return (-1); //Pas de token = erreur
		ft_putstr(" ");
		i++;
	}
	return (1);
>>>>>>> 65d886d1e94c08551b59d230a3bb8b0cb19f106e
}