/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/18 13:43:41 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/07 10:54:53 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/lexeur.h"
#include "../../includes/alias.h"

void		init_job(t_job *j)
{
	j->split = '\0';
	j->status = '\0';
}

void		fill_job(t_job *j, t_lexeur **res)
{
	int			i;

	i = 0;
	while (res[i])
	{
		if (res[i]->token == 1 || res[i]->token == 10)
		{
			if (res[i]->token == 1)
				j->split = '&';
			else
				j->split = ';';
			if (res[i + 1])
			{
				j->next = malloc(sizeof(t_job));
				j = j->next;
				init_job(j);
			}
		}
		if (res[i])
			i++;
	}
	j->next = NULL;
}

void		free_lexeur(t_lexeur **res)
{
	int		i;

	i = 0;
	while (res[i])
	{
		ft_strdel(&res[i]->word);
		ft_strdel(&res[i]->redirection);
		ft_strdel(&res[i]->fd_in);
		ft_strdel(&res[i]->fd_out);
		free(res[i]);
		i++;
	}
	free(res);
}

// void		free_parseur(t_job *j)
// {
// 	t_redirect	*red_tmp;
// 	t_process	*pro_tmp;
// 	t_job		*j_tmp;

// 	while (j)
// 	{
// 		while (j->p)
// 		{
// 			while (j->p->redirect)
// 			{
// 				ft_strdel(&j->p->redirect->fd_in);
// 				ft_strdel(&j->p->redirect->fd_out);
// 				ft_strdel(&j->p->redirect->token);
// 				red_tmp = j->p->redirect;
// 				j->p->redirect = j->p->redirect->next;
// 				free(red_tmp);
// 			}
// 			ft_free_tab(j->p->cmd);
// 			pro_tmp = j->p;
// 			j->p = j->p->next;
// 			free(pro_tmp);
// 		}
// 		free(pro_tmp);
// 		j_tmp = j;
// 		j = j->next;
// 		free(j_tmp);
// 	}
// 	free(j_tmp);
// }

void		print_j(t_job *j)
{
	t_job	*jt;
	t_process *pt;
	int			i;

	jt = j;
	puts("------------------------");
	while (jt)
	{
		pt = j->p;
		while (pt)
		{
			i = 0;
			if (pt->cmd)
			{
				while (pt->cmd[i])
				{
					printf("cmd[%d]: _%s_\n", i, pt->cmd[i]);
					i++;
				}
			}
			while (pt->redirect)
			{
				printf("fd: %d\n", pt->redirect->fd);
				printf("content: _%s_\n", pt->redirect->heredoc_content);
				printf("token : _%s_\n", pt->redirect->token);
				pt->redirect = pt->redirect->next;
			}
			pt = pt->next;
		}
		jt = jt->next;
	}
	puts("------------------------");
}

void		free_jobs(t_job *j)
{
	t_job		*job;
	t_process	*pro;
	t_redirect	*red;

	while (j)
	{
		while (j->p)
		{
			while (j->p->redirect)
			{
				ft_strdel(&j->p->redirect->fd_out);
				ft_strdel(&j->p->redirect->fd_in);
				ft_strdel(&j->p->redirect->token);
				red = j->p->redirect;
				j->p->redirect = j->p->redirect->next;
				free(red);
			}
			ft_free_tab(j->p->cmd);
			pro = j->p;
			j->p = j->p->next;
			free(pro);
		}
		job = j;
		j = j->next;
		free(job);
	}
}

void		replace_job(t_process **p, t_var *var)
{
	t_alias		*al;
	t_replace	*r;

	init_replace(&r);
	if (!(*p) || !((*p)->cmd))
		return ;
	al = make_ar_to_list((*p)->cmd);
	if (!al)
		return ;
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

void		save_spe_param(char **cmd, t_var *var)
{
	int	i;

	i = 0;
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
		var->next = NULL;
	}
	else
		ft_strdel(&var->data);
	if (!(cmd) || !(cmd[0]))
		var->data = ft_strdup("");
	else
		var->data = ft_strdup(cmd[i - 1]);
}

int			start_exec(t_lexeur **res, t_var *var)
{
	t_job		*j;
	t_job		*start;
	t_process	*tmp;
	t_job		*next;

	if (!res[0])
	{
		free(res);
		return (0);
	}
	j = malloc(sizeof(t_job));
	start = j;
	j->pgid = 0;
	init_job(j);
	fill_job(j, res);
	fill_process(j, res);
//	print_j(j);
	free_lexeur(res);
	while (j)
	{
		j->pgid = 0;
		next = j->next;
		tmp = j->p;
		while (tmp)
		{
			replace_job(&tmp, var);
			tmp = tmp->next;
		}
		save_spe_param(j->p->cmd, var);
		launch_job(j, var);
		j = next;
	}
	// free_parseur(j);
	// free_jobs(start);
	return (0);
}
