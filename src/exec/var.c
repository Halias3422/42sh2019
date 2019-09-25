/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   var.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/16 14:49:17 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/25 10:30:11 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lexeur.h"
#include "exec.h"

void		add_env_temp(t_var **var, char *str, int type)
{
	t_var	*start;

	start = malloc(sizeof(t_var));
	start->name = init_name(str);
	start->data = init_data(str);
	start->type = type;
	start->next = (*var);
	(*var) = start;
}

char		**remove_tab(char **src, int j)
{
	char	**res;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (src[i])
		i++;
	res = malloc(sizeof(char*) * i);
	i = 0;
	while (src[i])
	{
		if (i == j)
			i++;
		res[k] = ft_strdup(src[i]);
		i++;
		k++;
	}
	res[k] = NULL;
	return (res);
}

void		add_env(t_var **var, char *str)
{
	t_var	*prev;
	char	*name;

	name = init_name(str);
	if (!(*var))
	{
		add_env_temp(var, str, LOCAL);
		stock(*var, 5);
		return ;
	}
	while (*var)
	{
		if (ft_strcmp(name, (*var)->name) == 0)
			break ;
		prev = (*var);
		(*var) = (*var)->next;
	}
	if (!(*var))
	{
		add_local(var, str, prev);
		return ;
	}
	ft_strdel(&(*var)->data);
	ft_strdel(&name);
	(*var)->data = init_data(str);
}

int			local_or_env(t_var **var, char **cmd, int i, char ***tmp)
{
	if (cmd[i] && find_equal(cmd[i]))
	{
		if (check_cmd(cmd) == 1)
		{
			add_env_temp(var, cmd[i], TEMP);
			*tmp = remove_tab(cmd, i);
		}
		else
		{
			add_env(var, cmd[i]);
			ft_free_tab(cmd);
			return (-1);
		}
	}
	return (0);
}

char		**check_exec_var(char **cmd, t_var **var)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	while (cmd[i])
	{
		if (local_or_env(var, cmd, i, &tmp) == -1)
			return (NULL);
		i++;
	}
	if (tmp != NULL)
	{
		ft_free_tab(cmd);
		return (tmp);
	}
	return (cmd);
}
