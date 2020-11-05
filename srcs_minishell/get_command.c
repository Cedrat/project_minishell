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
	int	found; //1 = success, 0 = command not found, -1 = wrong path/file

	i = 0;
	j = 0;
	found = 0;

	while (args[i] && found == 0)
	{
		while (j < 7 && found == 0)
		{
			if (ft_strcmp(args[i], commands[j]) == 0 && ft_nopipes(args))
				{
					if (j == 1)
						found = function[j](args[1]);
					else
						found = function[j](argenv);
				}
			j++;
		}
		j = 0;
		i++;
	}
	if (found == 0)
		ft_putstr("Command not found : ");
	else if (found == -1)
	{
		ft_putstr(args[1]);
		ft_putstr(" : No file or folder of this type");
	}
}
