#include "../header/minishell.h"

int		ft_env(char **argenv)
{
	while (*argenv)
	{
		if (*argenv[0] != 0)
		{
			ft_putstr(*argenv);
			ft_putstr("\n");
		}
		argenv++;
	}
	return (1);
}
