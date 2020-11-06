#include "../header/minishell.h"

char	*ft_strncpy(char *src, char *dest, int len)
{
	int i;

	i = 0;
	while (src[i] != '\0' && len > 0)
	{
		dest[i] = src[i];
		i++;
		len--;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_home_path(char **argenv)
{
	char	*path;
	int 	i;
	int		j;

	i = 0;
	j = 0;
	while (argenv[i])
	{
		if (ft_strncmp(argenv[i], "HOME=", 5) == 0)
		{
			while (argenv[i][j] != '=')
				j++;
			j++;
			path = malloc(sizeof(char) * ft_strlen(argenv[i]) - j);
			ft_strncpy(&argenv[i][j], path, ft_strlen(argenv[i]) - j);
			break;
		}
		i++;
	}
	return (path);
}


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

	int 	i;
	int 	j;
	int		found; //1 = success, 0 = command not found, -1 = wrong path/file, -2 = trop d'args
	char	*home_path;

	home_path = ft_home_path(argenv);
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
						found = function[j](args, home_path);
					else if (j == 3)
						found = function[j](args, argenv);
					else
						found = function[j](argenv);
				}
			j++;
		}
		j = 0;
		i++;
	}
	if (found == 0)
	{
		ft_putstr("Command not found : ");
		if (args[0])
			ft_putstr(args[0]);
	}
	else if (found == -1)
	{
		ft_putstr(args[1]);
		ft_putstr(" : No file or folder of this type ");
	}
	else if (found == -2)
	{
		ft_putstr(" Too many arguments ");
	}
	ft_putstr("\n");
	// for (int i = 0; args[i]; i++)
    //     {
    //         ft_putstr(args[i]);
    //         ft_putstr("\n");
    //     }
}
