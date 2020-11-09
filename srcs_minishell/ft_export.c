#include "../header/minishell.h"

size_t sizeofenv(char **argenv)
{
	size_t i;

	i = 0;
	while (argenv[i])
		i++;
	return (i);
}

void export_env(char *argv,char **argenv)
{
	size_t i;
	char **new_argenv;
	size_t p = 0;

	i = sizeofenv(argenv);
	new_argenv = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (argenv[i])
	{
		new_argenv[i] = ft_strdup(argenv[i]);
		i++;
	}

	new_argenv[i] = ft_strdup(argv);
	ft_putstr(new_argenv[i]);
	new_argenv[i + 1] = 0;
	argenv = new_argenv;
}

int		ft_export(char **argv, char **argenv)
{
	ft_tri_tab_str(argenv);
	int i = 0;
	char **stop;
	while (argv[i + 1])
	{
		if (!(ft_isalpha(argv[i + 1][0])))
		{
			ft_putstr("minishell: export: « ");
			ft_putstr(argv[i + 1]);
			ft_putstr(" » : bad variable name\n");
		}
		else
		{
			export_env(argv[i + 1], argenv);
		}
		i++;
	}
	if (i != 0)
		return (1);
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
