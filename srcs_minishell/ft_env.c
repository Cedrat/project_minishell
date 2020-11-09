#include "../header/minishell.h"

int		ft_env(t_shell *shell)
{
	while (*shell->argenv)
	{
		if (*shell->argenv[0] != 0)
		{
			ft_putstr(*shell->argenv);
			ft_putstr("\n");
		}
		shell->argenv++;
	}
	return (1);
}
