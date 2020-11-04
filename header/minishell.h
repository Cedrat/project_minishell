#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

int		ft_charispresent(const char* str, char lett);
int 	ft_nopipes(char **args);
int		ft_strcmp(const char *s1, const char *s2);

#endif
