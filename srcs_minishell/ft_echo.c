#include "../header/minishell.h"

void	ft_echo_config(t_echo *config, char **args)
{
	int		i;
	int		j;

	config->sg_qt = 0;
	config->db_qt = 0;
	config->backslash = 0;
	config->first_token = 0;
	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			if (args[i][j] == '\\')
				config->backslash++;
			if (args[i][j] == '\'') //Single qupte
			{
				config->token = ft_strdup("sg_qt");
				if (config->sg_qt == 0 && config->db_qt == 0)
					config->first_token = 1;
				config->sg_qt++;
			}
			else if ((args[i][j] == '\"' && args[i][j - 1] != '\\')
			|| (args[i][j] == '\"' && args[i][j - 1] == '\\' && config->backslash % 2 == 0)) //double quote
			{
				config->token = ft_strdup("db_qt");
				if (config->sg_qt == 0 && config->db_qt == 0)
					config->first_token = 2;
				config->db_qt++;
			}
			j++;
		}
		i++;
	}
	if (config->sg_qt == 0 && config->db_qt == 0)
		config->token = ft_strdup("none");
//Test des variables
//printf("%d %d %d %s\n", config->sg_qt, config->db_qt, config->first_token, config->token);
}



void	ft_single_qt(t_echo *config, char **args)
{
	int 	i;
	int		j;
	char	*str;

	i = 1;
	while (args[i])
	{
		j = 0;
		while(args[i][j] != '\0')
		{
			if (args[i][j] == '|' || args[i][j] == ';') //Gestion future
				return ;
			j++;
		}
		str = ft_strtrim(args[i], "\'");  //Espace entre "'aa' 'bb'" pas encore geres
		ft_putstr(str);
		free(str);
		i++;
	}
}



void	ft_double_qt(t_echo *config, char **args, char **argenv)
{
	int 	i;
	int		j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while(args[i][j] != '\0')
		{
			if (args[i][j] == '|' || args[i][j] == ';')
				return ;
			if (args[i][j] == '\"')
				j++;
			/*else if (args[i][j] == '$' && args[i][j + 1] == '?')
			{
				ft_get_signal(); //Doit renvoyer signal emit par derniere commande
				j += 2;			 //0=reussite, -1 = echec. Et on avance jusqu'à après le '?'
			}*/
			if (args[i][j] == '$' && !ft_strchr(" \"\\\'\0\n", args[i][j + 1]))
			{
				config->var_name = ft_extract_var_name(args[i], &j);
				config->var_path = ft_get_var(argenv, config->var_name);
				if (config->var_path)
					ft_putstr(config->var_path);
			}
			else if (args[i][j] == '\\' && args[i][j + 1] == '\\' && args[i][j + 2] != '\\')
				j++;
			else if (args[i][j] == '\\' && args[i][j + 1] == '\"')
				j++;
			ft_putchar_fd(args[i][j], 1);
			j++;
		}
		i++;
	}
}


void	ft_no_qt(t_echo *config, char **args, char **argenv)
{

}



int		ft_echo(t_shell *shell)
{
	t_echo	config;

	ft_echo_config(&config, shell->args);
	//Gestion d'erreurs
	if ((ft_strcmp(config.token, "sg_qt") == 0 && (config.sg_qt % 2 != 0)) 
		|| (ft_strcmp(config.token, "db_qt") == 0 && (config.db_qt % 2 != 0))) //Nombre impair de quotes
	{
		ft_putstr("Wrong number of quotes :");
		return (-2);
	}



	//----------------------------------------------------//
	//Gestion de l'affichage en fonction des tokens

	//Gestion avec ''
		//Parser en enlevant les quotes
	if (ft_strcmp(config.token, "sg_qt") == 0)
		ft_single_qt(&config, shell->args);


	//Gestion avec ""
		//Parser en enlevant les quotes, sauf si précédées de backslash
	else if (ft_strcmp(config.token, "db_qt") == 0)
		ft_double_qt(&config, shell->args, shell->argenv);

	//Gestion sans 
	else if (ft_strcmp(config.token, "none") == 0)
	{
		//else if (args[i][j] == '~')
			//ft_putstr(getcwd(str, 256));
	}

	else
		return (-1); //Pas de token = erreur
	return (1);
}