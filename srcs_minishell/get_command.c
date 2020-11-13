#include "../header/minishell.h"

void	ft_init_commands(t_shell *shell)
{
	shell->echo = malloc(sizeof(t_echo));
	shell->commands[0] = ft_strdup("echo");
	shell->commands[1] = ft_strdup("cd");
	shell->commands[2] = ft_strdup("pwd");
	shell->commands[3] = ft_strdup("export");
	shell->commands[4] = ft_strdup("unset");
	shell->commands[5] = ft_strdup("env");
	shell->commands[6] = ft_strdup("exit");
	shell->newline = 0;
	shell->signal= 0;
}

void	ft_init_functions(t_shell *shell)
{
	shell->function[0] = &ft_echo;
	shell->function[1] = &ft_cd;
	shell->function[2] = &ft_pwd;
	shell->function[3] = &ft_export;
	shell->function[4] = &ft_unset;
	shell->function[5] = &ft_env;
	shell->function[6] = &ft_exit;
}

void	ft_get_command(t_shell *shell)
{
	int 	i;
	int 	j;
	int		found; //0 = success, -1 = command not found, -2 = wrong path/file, -3 = trop d'args

	ft_init_commands(shell);
	ft_init_functions(shell);
	shell->home_path = ft_get_var(shell->argenv, "HOME="); //On recupere le path du home

	i = 0;
	found = 0;

	while (shell->args[i] && found == 0)
	{
		j = 0;
		while (j < 7 && found == 0)
		{
			if (ft_strcmp(shell->args[i], shell->commands[j]) == 0 && ft_nopipes(shell->args))
				found = shell->function[j](shell);
			j++;
		}
		i++;
	}

	//Gestion des erreurs (a mettre dans une autre fonction qui reprendra errno ?)
	if (found == -1)
	{
		ft_putstr("Command not found : ");
		if (shell->args[0])
			ft_putstr(shell->args[0]);
	}
	else if (found == -2)
	{
		ft_putstr(shell->args[1]);
		ft_putstr(" : No file or folder of this type ");
	}
	else if (found == -3)
	{
		ft_putstr(" Too many/few arguments ");
	}
	if (shell->echo->option_n == 0 && shell->newline == 0)
		ft_putstr("\n");
}
