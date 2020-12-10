/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:48:44 by lnoaille          #+#    #+#             */
/*   Updated: 2020/12/10 03:22:48 by lnoaille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


int		iterate_word(char *str, size_t *i, size_t p);

void	ft_strndup(char **dest, char *src, size_t start, size_t end)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char) * (end - start + 1));
	while (start < end && src[start])
	{
		str[i] = src[start];
		start++;
		i++;
	}
	str[i] = '\0';
	*dest = str;
}

int		not_a_sep(char letter)
{
	if (letter == ';' || letter == '>' || letter == '<' || letter == '|' )
		return (0);
	return (1);
}

int		ft_is_not_space(char *str, size_t *i)
{
	while (not_a_sep(str[*i]) && str[*i] && str[*i] != ' ')
	{
		if (str[*i] == '"')
			iterate_word(str, i, 0);
		if (str[*i])
			*i += 1;
	}
	return (*i);
}

int		ft_is_space(char *str, size_t *i)
{
	while (str[*i] == ' ')
		*i += 1;
	return (*i);
}

int		iterate_word(char *str, size_t *i, size_t p)
{
	char sep;

	sep = str[*i];
	while ((str[*i] == '"' || str[*i] == '\'') && str[*i])
	{
		if (str[*i] == sep)
			p++;
		(*i)++;
	}
	if (p > 1 && p % 2 == 0)
		return (*i);
	while ((str[*i] != '"' && str[*i] != '\'' && str[*i]))
	{
		(*i)++;
	}
	while ((str[*i] == '"' || str[*i] == '\'') && str[*i] && p % 2 != 0)
	{
		if (str[*i] == sep)
			p++;
		(*i)++;
	}
	if (((str[*i] != ' ' && not_a_sep(str[*i])) || (p % 2 != 0)) && str[*i])
		iterate_word(str, i, p);
	return (*i);
}

size_t	count_tokens(char *str)
{
	size_t i;
	size_t j;
	size_t p;
	size_t d;

	i = 0;
	p = 0;
	while (str[i])
	{
		j = ft_is_space(str, &i);
		if (str[i] == '\'' || str[i] == '"')
			d = iterate_word(str, &i, 0);
		else
			d = ft_is_not_space(str, &i);
		if (str[i] == '>' && str[i + 1] == '>')
		{
			i += 1;
			p++;
		}
		else if (!not_a_sep(str[i]) || j != d)
			p++;
		if (!not_a_sep(str[i]))
			p++;
		if (str[i])
			i++;
	}
	return (p);
}

char	*ft_cut_replace(char *str, t_shell *shell, int j)
{
	char	*pt1;
	char	*pt2;
	char	*pt3;
	int		len;

	pt1 = ft_substr(str, 0, j);
	pt2 = ft_itoa(shell->signal);
	if (str[j + 2] && (ft_strlen(str) > j + 2))
		pt3 = ft_substr(str, j + 2, ft_strlen(str) - (j + 2));
	else
		pt3 = ft_strdup("");
	free(str);
	str = ft_strjoin_freeall(pt1, pt2);
	str = ft_strjoin_freeall(str, pt3);
	return (str);
}

char	*ft_replace_var(t_shell *shell, char *arg)
{
	char	*tmp;
	char	*var_path;
	int 	i;
	char 	**tab;

	i = 0;
	tmp = arg;
	var_path = ft_extract_var_name(arg, &i);
	if (var_path[1])
	{
		free(arg);
		arg = ft_get_var(shell->argenv, var_path);
	}
	free(var_path);
	return (arg);
}

int		ft_check_doll(char *tab)
{
	int	j;

	j = 0;
	while (tab[j])
	{
		if ((tab[j + 1] && tab[j] == '$' && tab[j + 1] == '?')
			|| (tab[j + 1] && tab[j] == '$' && tab[j + 1] == '?'))
			return (j);
		j++;
	}
	return (j = -1);
}

char**	ft_dollar(char **tab, t_shell *shell)
{
	int i;
	int j;


	i = 0;
	while (tab[i])
	{
		if ((i == 0 && ft_strcmp(tab[i], "$?") == 0)
			|| (ft_strcmp(tab[i], "$?") == 0
				&& ft_strcmp(tab[i - 1], "echo") != 0))
		{
			free(tab[i]);
			tab[i] = ft_itoa(shell->signal);
		}
		else
		{
			if (tab[i][0] == '\'')
				break;
			if ((i == 0 && (j = ft_check_doll(tab[i]) > 0))
				|| ((j = ft_check_doll(tab[i]) > 0)
					&& ft_strcmp(tab[i - 1], "echo") != 0))
				tab[i] = ft_cut_replace(tab[i], shell, j);
				if (tab[i][j] == '$' && tab[i][j + 1] && tab[i][j + 1] != '?')
				{
					tab[i] = ft_replace_var(shell, tab[i]);
					tab = add_split_arg(tab, &i);
				}
		}
		i++;
	}
	return (tab);
}

void	ft_parser_2(char *str, char **tab, size_t *i, size_t *p)
{
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		ft_strndup(&tab[*p], str, *i, *i + 2);
		*i += 1;
		*p += 1;
	}
	else if (str[*i] != ' ' && !not_a_sep(str[*i]))
	{
		ft_strndup(&tab[*p], str, *i, *i + 1);
		*p += 1;
	}
	if (str[*i])
		*i += 1;
}

char	**ft_parser(char *str, t_shell *shell)
{
	char	**tab;
	size_t	i;
	size_t	j;
	size_t	p;
	size_t	d;

	tab = malloc(sizeof(char *) * (count_tokens(str) + 2));
	i = 0;
	p = 0;
	while (str[i])
	{
		j = ft_is_space(str, &i);
		if (str[i] == '\'' || str[i] == '"')
			d = iterate_word(str, &i, 0);
		d = ft_is_not_space(str, &i);
		if (j != d)
		{
			ft_strndup(&tab[p], str, j, i);
			p++;
		}
		ft_parser_2(str, tab, &i, &p);
	}
	tab[p] = NULL;
	tab = ft_dollar(tab, shell);
	return (tab);
}
