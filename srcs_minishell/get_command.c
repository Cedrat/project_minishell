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
	shell->echo->option_n = 1;
}

void	ft_get_command(t_shell *shell)
{
	int 	i;
	int 	j;
	int		found;

	ft_init_commands(shell);
	shell->home_path = ft_get_var(shell->argenv, "HOME=");
	i = 0;
	found = -1;
	while (shell->args[i] && found == -1)
	{
		j = 0;
		while (j < 7 && found == -1)
		{
			if (ft_strcmp(shell->args[i], shell->commands[j]) == 0 
				&& ft_nopipes(shell->args))
				found = shell->function[j](shell);
			j++;
		}
		if (found == -1)
			found = ft_exec(shell, shell->args[i]);
		i++;
	}
	ft_errors(found, shell);
	if (shell->echo->option_n == 0 && shell->newline == 0)
		ft_putstr_fd("\n", shell->fd);
}
