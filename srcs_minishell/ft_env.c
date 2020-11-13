#include "../header/minishell.h"

int		ft_env(t_shell *shell)
{
	size_t i = 0;

	while (shell->argenv[i])
	{
		if (shell->argenv[0] != 0)
		{
			if (ft_charispresent(shell->argenv[i], '='))
			{
				ft_beautifull_export(shell->argenv[i], 0);
				ft_putstr("\n");
			}
		}
		i++;
	}
	return (shell->signal = 1);
}
