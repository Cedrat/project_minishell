#include "../header/minishell.h"

void	ft_free_all(t_shell *shell)
{
	int i;

	i = 0;
	while (i < 7)
	{
		free(shell->commands[i]);
		i++;
	}
	free(shell->echo);
	free(shell->home_path);
	ft_free_tab(shell->args);
	ft_free_tab(shell->args_line);
	ft_free_tab(shell->argenv);

}

int		ft_exit(t_shell *shell)
{
	char *str;
	int nb;

	nb = 0;
	if (shell->args[1])
	{
		str = ft_str_treatement(shell->args[1]);
		if (ft_str_is_number(str))
			nb = ft_atoi(str);
		else
		{
			ft_putstr("minishell: exit : Illegal number: ");
			ft_putstr(str);
			ft_putstr("\n");
			return (0);
		}
	}
	nb = nb%256;
	write(1, "Bye ! \n", 7);
	ft_free_all(shell);
	exit(nb);
}
