#include "../header/minishell.h"

int		ft_pwd(t_shell *shell)
{
	char	str[255];

	//Inclure une fonction pour gérer automatiquement la longueur de la string ?
	//Avec du malloc, et on rajoute de la memoire si la string est trop grande ?
	ft_putstr(getcwd(str, 256));
	return (shell->signal = 1);
}