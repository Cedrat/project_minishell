#include "../header/minishell.h"

int		ft_export(t_shell *shell)
{
	ft_tri_tab_str(shell->argenv);
	int i = 0;
	if (shell->args[1])
	{
		if (!(ft_isalpha(shell->args[1][0])))
		{
			ft_putstr("minishell: export: « ");
			ft_putstr(shell->args[1]);
			ft_putstr(" » : bad variable name");
		}
		return (1);
	}
	while (shell->argenv[i])
	{
		ft_putstr("declare -x ");
		ft_putstr(shell->argenv[i]);
		i++;
		if (shell->argenv[i])
			ft_putstr("\n");
	}
	return (1);
}
