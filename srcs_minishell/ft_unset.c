#include "../header/minishell.h"

char **ft_remove_in_tab(char **tab, char* str)
{
	size_t i = 0;
	size_t p;
	char **new_tab;
	size_t found;

	found = 0;
	while (tab[i])
	{
		i++;
	}
	new_tab = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tab[i + found])
	{
		p = 0;
		while (str[p] != '=' && str[p])
			p++;
		if (!(ft_strncmp(tab[i + found], str, p)))
			found++;
		else
		{
			new_tab[i] = tab[i + found];
			i++;
		}
	}
	new_tab[i] = 0;
	return (new_tab);
}

int		ft_unset(t_shell *shell)
{
	size_t i;
	char *str;
	size_t p;
	size_t o;

	o = 1;

	while (shell->args[o])
	{
		i = 0;
		while (shell->argenv[i])
		{
			p = 0;
			str = shell->argenv[i];
			while (str[p] != '=' && str[p])
				p++;
			if (!(ft_strncmp(shell->args[o], str, p)))
				  shell->argenv = ft_remove_in_tab(shell->argenv, shell->args[o]);
			i++;
		}
		o++;
	}
	return (shell->signal = 0);
}
