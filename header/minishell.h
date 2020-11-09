#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

int		ft_charispresent(const char* str, char lett);
int 	ft_nopipes(char **args);
int		ft_strcmp(const char *s1, const char *s2);
void 	ft_tri_tab_str(char** str);
void 	ft_putstr(char *word);

char	*ft_get_var(char **argenv, char *tofind);

int  	ft_export(char **argv, char **argenv);
char 	**ft_parser(char *str);
void 	ft_free_tab_made_by_parser(char **tab);
void	ft_get_command(char **args, char **argenv);
int		ft_echo();
int		ft_cd();
int		ft_pwd();
int		ft_unset();
int		ft_env();
int		ft_exit();



/*-----------------------------*/
/*------Structure fct echo-----*/
/*-----------------------------*/
typedef	struct	s_echo
{
	char	*token; //'none', 'sg_qt', 'db_qt'
	int		sg_qt;
	int		db_qt;
	int		backslash;
	int		first_token; //0 = none, 1 = single quote, 2 = double quote
	char 	*var_name;		//HOME=, OLDPWD= etc...  -> Nom de la variable + '=''
	char 	*var_path;		///home/diane, /bin/...  -> Adresse correspondant au nom de la var
}				t_echo;



/*-----------------------------*/
/*------Structure generale-----*/
/*-----------------------------*/
typedef	struct	s_shell
{
	int		signal;		//Return value of the last built-in used
	
	t_echo	*echo;



}				t_shell;



#endif
