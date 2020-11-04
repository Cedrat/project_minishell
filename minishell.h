#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


char			**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int ft_strlen(const char *word);

#endif
