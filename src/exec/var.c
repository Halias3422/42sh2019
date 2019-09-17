/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   var.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/16 14:49:17 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 17:57:34 by mjalenqu    ###    #+. /#+    ###.fr     */
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
	printf("type = %d\n", type);
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
		printf("res[%d] = %s\n", k, res[k]);
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
	while (*var)
	{
		if (ft_strcmp(name, (*var)->name) == 0)
			break ;
		prev = (*var);
		(*var) = (*var)->next;
	}
	if (!(*var))
	{
		(*var) = malloc(sizeof(t_var));
		prev->next = (*var);
		(*var)->next = NULL;
		(*var)->name = name;
		(*var)->data = init_data(str);
		(*var)->type = LOCAL;
		return ;
	}
	ft_strdel(&(*var)->data);
	ft_strdel(&name);
	(*var)->data = init_data(str);
}

char		**check_exec_var(char **cmd, t_var **var)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	while (cmd[i])
	{
		if (cmd[i] && find_equal(cmd[i]))
		{
			if (check_cmd(cmd) == 1)
			{
				add_env_temp(var, cmd[i], TEMP);
				tmp = remove_tab(cmd, i);
			}
			else
				add_env(var, cmd[i]);
		}
		i++;
	}
	if (tmp != NULL)
	{
		ft_free_tab(cmd);
		return (tmp);
	}
	return (cmd);
}
