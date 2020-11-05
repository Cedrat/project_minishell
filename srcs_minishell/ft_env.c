#include "../header/minishell.h"

int		ft_env(char **argenv)
{
	while (*argenv)
	{
		ft_putstr(*argenv);
		ft_putstr("\n");
		argenv++;
	}
	return (1);
}
