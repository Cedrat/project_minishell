#include "../header/minishell.h"

void	ft_get_command(char **args, char **argenv)
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
				found = function[j](argenv);
			j++;
		}
		j = 0;
		i++;
	}
	if (found == 0)
		ft_putstr("Command not found : ");
}
