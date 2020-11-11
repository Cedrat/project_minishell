#include "../header/minishell.h"

void display_export(t_list *char_list)
{

	char *str;

	while (char_list)
	{
		ft_putstr("declare -x ");
		str = char_list->content;
		while (*str != '=' && *str)
		{
			ft_putchar_fd(*str, 1);
			str++;
		}
		if (*str == '=')
		{
			ft_putchar_fd(*str, 1);
			str++;
			ft_putstr("\"");
			while (*str)
			{
				ft_putchar_fd(*str, 1);
				str++;
			}
			ft_putstr("\"");
		}
		char_list = char_list->next;
		ft_putstr("\n");
	}
}

size_t sizeofenv(char **argenv)
{
	size_t i;

	i = 0;
	while (argenv[i])
		i++;
	return (i);
}

int env_exist(t_list *env, char *arg)
{
	size_t i;

	i = 0;
	while (arg[i] != '=' && arg[i])
		i++;

	while(env)
	{
		i = 0;
		while (arg[i] != '=' && arg[i])
			i++;
		if (!(ft_strncmp(arg, env->content, i)))
			return (1);
		env = env->next;
	}
	return (0);
}

void ft_modify_list(t_list **envs, char *str)
{
	t_list *new;
	t_list *temp;
	t_list *save;
	size_t i;
	void *head;

	temp = *envs;
	head = temp;

	while(temp)
	{
		i = 0;
		while (str[i] != '=' && str[i])
			i++;
		if (!(ft_strncmp(str, temp->content, i)))
		{
			new = ft_lstnew(str);
			break;
		}
		save = temp;
		temp = temp->next;
	}
	save->next = temp->next;
	ft_lstadd_back(envs, new);
	free(temp);
}

void export_env(t_list **envs, char *arg)
{
	t_list *new;
	if (!(env_exist(*envs, arg)))
	{
		new = ft_lstnew(arg);
		ft_lstadd_back(envs, new);
	}
	else if (ft_charispresent(arg, '='))
		ft_modify_list(envs, arg);
}

int		ft_export(t_shell *shell)
{
	ft_tri_tab_str(shell->argenv);
	int i = 0;
	while (shell->args[i+ 1])
	{
		if (!(ft_isalpha(shell->args[i + 1][0])))
		{
			ft_putstr("minishell: export: « ");
			ft_putstr(shell->args[i + 1]);
			ft_putstr(" » : bad variable name");
			if (shell->args[i + 2])
				ft_putstr("\n");
		}
		else
		{
			export_env(&shell->argenvs, shell->args[i + 1]);
		}
		i++;
	}
	if (shell->args[1] == 0)
		display_export(shell->argenvs);
	return (shell->signal = 1);
}
