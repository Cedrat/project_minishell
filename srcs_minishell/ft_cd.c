#include "../header/minishell.h"

int		ft_cd(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->args[i])
		i++;
	if (i == 2 && chdir(shell->args[1]) == 0)
		return (1);
	else if (i == 1)
	{
		chdir(shell->home_path);
		return (1);
	}
	else if (i > 2)
		return (-2);
	else
		return (-1);
}
