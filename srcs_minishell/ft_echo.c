#include "../header/minishell.h"
#include <stdio.h>

void	ft_echo_config(t_echo *config, char **args)
{
	int		i;
	int		j;

	config->sg_qt = 0;
	config->db_qt = 0;
	config->first_token = 0;
	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			if (args[i][j] == '\'') //Single qupte
			{
				config->token = ft_strdup("sg_qt");
				if (config->sg_qt == 0 && config->db_qt == 0)
					config->first_token = 1;
				config->sg_qt++;
			}
			else if (args[i][j] == '\"') //double quote
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



int		ft_echo(char **args, char **argenv, int signal)
{
	t_echo	config;

	ft_echo_config(&config, args);
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
	{
		//ft_strtrim pour retirer les quotes ?
	}

	//Gestion avec ""
		//Parser en enlevant les quotes, sauf si précédées de backslash
	else if (ft_strcmp(config.token, "db_qt") == 0)
	{
		
	}

	//Gestion sans 
	else if (ft_strcmp(config.token, "none") == 0)
	{
		
	}

	else
		return (-1); //Pas de token = erreur
	return (1);
}