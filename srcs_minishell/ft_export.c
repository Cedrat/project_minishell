#include "../header/minishell.h"

size_t sizeofenv(char **argenv)
{
	size_t i;

	i = 0;
	while (argenv[i])
		i++;
	return (i);
}

void export_env(t_shell *shell)
{
	size_t i;
	char **new_argenv;
	size_t p = 0;

	i = sizeofenv(shell->argenv);
	new_argenv = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (shell->argenv[i])
	{
		new_argenv[i] = ft_strdup(shell->argenv[i]);
		i++;
	}

	new_argenv[i] = ft_strdup(shell->args[1]);
	ft_putstr(new_argenv[i]);
	new_argenv[i + 1] = 0;
	shell->argenv = new_argenv;
}
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
		else
		{
			export_env(shell);
		}
		i++;
	}
	while (shell->argenv[i])
	{
		ft_putstr("declare -x ");
		ft_putstr(shell->argenv[i]);
		i++;
		if (shell->argenv[i])
			ft_putstr("\n");
	}
	return (shell->signal = 1);
}
