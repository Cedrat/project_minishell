#include "../header/minishell.h"

void	ft_free_all(t_shell *shell)
{
	int i;

	i = 0;
	while (i < 7)
	{
		free(shell->commands[i]);
		i++;
	}
	free(shell->echo);
	free(shell->home_path);
}



int		ft_exit(t_shell *shell)
{
	write(1, "Bye ! \n", 7);
	ft_free_all(shell);
	exit(0);
}
