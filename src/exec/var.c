/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   var.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/16 14:49:17 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/27 17:25:00 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"
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
	int		len;

	i = 0;
	k = 0;
	len = 0;
	while (src[len])
		len++;
	if (len == 1)
		return (NULL);
	res = malloc(sizeof(char*) * len);
	i = 0;
	while (src[i])
	{
		if (i == j)
			i++;
		if (i > len)
			break ;
		res[k] = ft_strdup(src[i]);
		i++;
		k++;
	}
	res[len - 1] = NULL;
	return (res);
}

void		add_env(t_var **var, char *str)
{
	t_var	*prev;
	char	*name;

	prev = NULL;
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

void		remoove_all_quote(char **str)
{
	char **al;
	
	al = malloc(sizeof(char *) * 3);
	al[2] = 0;
	al[0] = init_name(*str);
	al[1] = init_data(*str);
	remoove_quote(&al);
	ft_strdel(&(*str));
	(*str) = ft_strjoin(al[0], "=");
	ft_strjoin_free(str, al[1]);
}

int			local_or_env(t_var **var, char **cmd, int i, char ***tmp)
{
	if (cmd[i] && find_equal(cmd[i]))
	{
		remoove_all_quote(&cmd[i]);
		if (check_cmd(cmd) == 1)
		{
			add_env_temp(var, cmd[i], TEMP);
			*tmp = remove_tab(cmd, i);
		}
		else
		{
			while (cmd[i])
			{
				add_env(var, cmd[i]);
				i++;
			}
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
