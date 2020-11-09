#include "../header/minishell.h"

int		ft_cd(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->args[i])
		i++;
	if (i == 2 && chdir(shell->args[1]) == 0)
		return (shell->signal = 1);
	else if (i == 1)
	{
		shell->signal=chdir(shell->home_path);
		return (shell->signal = 1);
	}
	else if (i > 2)
		return (shell->signal = -2);
	else
		return (shell->signal = -1);
}
