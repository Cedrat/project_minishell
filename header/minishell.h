#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

int		ft_export(char **argenv);
int		ft_charispresent(const char* str, char lett);
int 	ft_nopipes(char **args);
int		ft_strcmp(const char *s1, const char *s2);
void ft_tri_tab_str(char** str);
void 	ft_putstr(char *word);

void	ft_get_command(char **args, char **argenv);
int		ft_echo();
int		ft_cd();
int		ft_pwd();
int		ft_export();
int		ft_unset();
int		ft_env();
int		ft_exit();

#endif
