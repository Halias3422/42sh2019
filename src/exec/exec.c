/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/18 13:43:41 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/18 11:18:56 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/lexeur.h"
#include "../../includes/alias.h"

void		replace_job(t_process **p, t_var *var)
{
	t_alias		*al;
	t_replace	*r;

	if (!(*p) || !((*p)->cmd))
		return ;
	al = make_ar_to_list((*p)->cmd);
	if (!al)
		return ;
	init_replace(&r);
	r->name = ft_strdup(al->data);
	while (1)
	{
		if (remove_env_while(al, var, r) == 0)
			break ;
	}
	(*p)->cmd = make_list_to_ar(al);
	del_back_slash(&(*p)->cmd);
	remoove_quote(&(*p)->cmd);
	del_back_slash_end(&(*p)->cmd);
	free_replace(r);
	free_alias(al);
}

void		save_spe_param(char **cmd, t_var *var, int i)
{
	if (var == NULL || !cmd)
		return ;
	while (cmd[i])
		i++;
	while (var && var->next)
	{
		if (var->type == SPE && ft_strcmp(var->name, "_") == 0)
			break ;
		var = var->next;
	}
	if (var && !(var->next) && ft_strcmp("_", var->name) != 0)
	{
		var->next = malloc(sizeof(t_var));
		var = var->next;
		var->name = ft_strdup("_");
		var->data = NULL;
		var->type = SPE;
		var->next = NULL;
	}
	else
		ft_strdel(&var->data);
	if (!(cmd) || !(cmd[0]))
		var->data = ft_strdup("");
	else
		var->data = ft_strdup(cmd[i - 1]);
}

t_job		*make_job(t_lexeur **res)
{
	t_job	*j;
	t_job	*tmp;
	t_pos	*pos;

	pos = to_stock(NULL, 1);
	j = malloc(sizeof(t_job));
	j->pgid = 0;
	init_job(j);
	fill_job(j, res);
	fill_process(j, res);
	tmp = j;
	pos->last_cmd_on_bg = 0;
	while (tmp)
	{
		if (tmp->split == '&')
			pos->last_cmd_on_bg = 1;
		tmp = tmp->next;
	}
	free_lexeur(res);
	return (j);
}

int			return_freed_re(t_lexeur **res)
{
	free(res);
	return (0);
}

int			start_exec(t_lexeur **res, t_var *var)
{
	t_job		*j;
	t_process	*tmp;
	t_job		*next;

	if (!res[0])
		return (return_freed_re(res));
	j = make_job(res);
	while (j)
	{
		var = stock(NULL, 6);
		j->pgid = 0;
		next = j->next;
		tmp = j->p;
		while (tmp)
		{
			replace_job(&tmp, var);
			tmp = tmp->next;
		}
		save_spe_param(j->p->cmd, var, 0);
		launch_job(j, var);
		j = next;
	}
	return (0);
}
