#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include <stddef.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <limits.h>


pid_t 	pid; //variable globale pid
int 	prompt;

/*-----------------------------*/
/*------Structure fct echo-----*/
/*-----------------------------*/
typedef	struct	s_echo
{
	int		token; //0 = none, 1 = single quote, 2 = double quote
	int		sg_qt;
	int		db_qt;
	int		backslash;
	char 	*var_name;		//HOME=, OLDPWD= etc...  -> Nom de la variable + '=''
	char 	*var_path;		///home/diane, /bin/...  -> Adresse correspondant au nom de la var
	int 	option_n;
	int 	signal;
}				t_echo;



/*-----------------------------*/
/*------Structure generale-----*/
/*-----------------------------*/
typedef	struct	s_shell
{
	char 	**args;
	char 	**args_line;
	char 	**argenv;

	char 	*commands[7];
	int		(*function[7])();

	int		signal;		//Return value of the last built-in used
	int 	nb_error;
	char 	*home_path;
	int		fd;

	t_echo	*echo;		//A voir si on la garde dedans ou si on laisse séparé ?

	int		newline;
	pid_t	pid;

}				t_shell;


/*-----------------------------*/
/*----------Prototypes---------*/
/*-----------------------------*/

int		ft_charispresent(const char* str, char lett);
int 	ft_nopipes(char **args);
int		ft_strcmp(const char *s1, const char *s2);
void 	ft_tri_tab_str(char** str);
void 	ft_putstr(char *word);
int ft_str_is_present(char **tab, char *str);

char 	**ft_parser(char *str, t_shell *shell);
void 	ft_free_tab(char **tab);

void	ft_get_command(t_shell *shell);
int		ft_echo();
int		ft_cd();
int		ft_pwd();
int  	ft_export();
int		ft_unset();
int		ft_env();
int		ft_exit();
int		ft_exec(t_shell *shell, char *arg);

char	*ft_extract_var_name(char *arg, int *j);
char	*ft_get_var(char **argenv, char *tofind);
void 	export_env(t_shell *env, char *arg);


char **ft_dup_arg(char **arg);

void	ft_no_qt(t_echo *config, char *args, char **argenv, t_shell *shell);
void	ft_double_qt(t_echo *config, char *args, char **argenv, t_shell *shell);
void	ft_single_qt(t_echo *config, char *args, char **argenv, t_shell *shell);


void ft_beautifull_export(char *str, int is_export, int fd);
char *ft_str_treatement(char *str);

void ft_choose_fd(t_shell *shell);
int ft_str_is_number(char *str);
void ft_strndup(char **dest, char *src, size_t start, size_t end);
char **ft_args(char *str);
int ft_semi_colon(char *str);
char **ft_remove_in_tab(char **tab, char* str);
int ft_give_to_pipe(t_shell *shell);
char ***ft_args_pipe(char **args);
char *ft_file_to_str(char *path);
char **add_env(char **arg, char *str);
void ft_recursives_pipes(char **args_pipes, int i, int *fd, int *fd2, t_shell *shell);

void    sig_handler(int signum);
char **ft_divide_to_pipe(char **split);

char	*ft_strjoin_freeone(char const *s1, char const *s2);
char	*ft_strjoin_freetwo(char const *s1, char const *s2);
char	*ft_strjoin_freeall(char const *s1, char const *s2);

void 	free_shell_commands(t_shell *shell);

void	ft_errors(int error, t_shell *shell);
void	ft_free_all(t_shell *shell);
#endif
