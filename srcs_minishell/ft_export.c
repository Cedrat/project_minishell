#include "../header/minishell.h"

int		ft_export(char **argenv)
{
	ft_tri_tab_str(argenv);
	int i = 0;
	while (argenv[i])
	{
		ft_putstr("declare -x ");
		ft_putstr(argenv[i]);
		i++;
		if (argenv[i])
			ft_putstr("\n");
	}
	return (1);
}
