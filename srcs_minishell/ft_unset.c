#include "../header/minishell.h"

int		ft_unset(t_shell *shell)
{
	
	return (shell->signal = 1);
}
