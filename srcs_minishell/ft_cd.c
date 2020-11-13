#include "../header/minishell.h"

int		ft_cd(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->args[i])
		i++;
	if (i == 2 && (shell->signal = chdir(shell->args[1])) == 0)
	{
		shell->newline = 1;
		return (shell->signal);
	}
	else if (i == 1)
	{
		shell->newline = 1;
		shell->signal = chdir(shell->home_path);
		return (shell->signal);
	}
	else if (i > 2)
		return (shell->signal = -3);
	else
		return (shell->signal = -2);
}
