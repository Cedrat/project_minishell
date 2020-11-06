#include "../header/minishell.h"

int		ft_export(char **argv, char **argenv)
{
	ft_tri_tab_str(argenv);
	int i = 0;
	if (argv[1])
	{
		if (!(ft_isalpha(argv[1][0])))
		{
			ft_putstr("minishell: export: « ");
			ft_putstr(argv[1]);
			ft_putstr(" » : bad variable name");
		}
		return (1);
	}
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
