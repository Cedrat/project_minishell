#include "../header/minishell.h"
#include <stdio.h>
void	ft_get_command(char **args)
{
	char 	*commands[7] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit"
	};

	int		(*function[7])() ={ 
		&ft_echo,
		&ft_cd,
		&ft_pwd,
		&ft_export,
		&ft_unset,
		&ft_env,
		&ft_exit
	};

	int i;
	int j;
	int	found;

	i = 0;
	j = 0;
	found = 0;

	while (args[i] && found == 0)
	{
		while (j < 7 && found == 0)
		{
			if (ft_strcmp(args[i], commands[j]) == 0 && ft_nopipes(args))
				found = function[j]();
			j++;
		}
		j = 0;
		i++;
	}
	//ft_putstr("Sortie de boucle");
	if (found == 0)
	{
		ft_putstr("Command not found : ");
		return ;
	}
}