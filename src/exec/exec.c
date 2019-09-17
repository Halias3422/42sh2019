/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/18 13:43:41 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 14:48:33 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/lexeur.h"

void		init_job(t_job *j)
{
	j->split = '\0';
	j->status = '\0';
}

void		fill_job(t_job *j, t_lexeur **res)
{
	int			i;
	int			k;

	i = 0;
	k = 0;
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

// void		print_exec(t_job *j)
// {
// 	t_job			*sj;
// 	t_process		*sp;
// 	int			i;

// 	sj = j;
// 	while (j)
// 	{
// 		sp = j->p;
// 		while (j->p)
// 		{
// 			i = 0;
// 			puts("-----------------------------------------------------------------------");
// 			while (j->p->cmd[i])
// 			{
// 				printf("cmd[%d]: _%s_\n", i, j->p->cmd[i]);
// 				i++;
// 			}
// 			if (j->p->redirect)
// 			{
// 				while (j->p->redirect)
// 				{
// 					printf("redirect fd_in : _%s_\tfd_out : _%s_\ttoken: _%s_\tfd %d\n", j->p->redirect->fd_in, j->p->redirect->fd_out, j->p->redirect->token, j->p->redirect->fd);
// 					j->p->redirect = j->p->redirect->next;
// 				}
// 			}
// 			puts("-----------------------------------------------------------------------");
// 			j->p = j->p->next;
// 		}
// 		j->p = sp;
// 		j = j->next;
// 	}
// 	j = sj;
// }

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

void		free_parseur(t_job *j)
{
	t_redirect	*red_tmp;
	t_process	*pro_tmp;
	t_job		*j_tmp;
	int			i;

	while (j)
	{
		while (j->p)
		{
			while (j->p->redirect)
			{
				ft_strdel(&j->p->redirect->fd_in);
				ft_strdel(&j->p->redirect->fd_out);
				ft_strdel(&j->p->redirect->token);
				red_tmp = j->p->redirect;
				j->p->redirect = j->p->redirect->next;
				free(red_tmp);
			}
			i = 0;
			while (j->p->cmd[i])
			{
				ft_strdel(&j->p->cmd[i]);
				i++;
			}
			free(j->p->cmd);
			pro_tmp = j->p;
			j->p = j->p->next;
			free(pro_tmp);
		}
		j_tmp = j;
		j = j->next;
		free(j_tmp);
	}
}

// static void		print_jobs(t_job *j)
// {
// 	int	i = 0;
// 	while (j->p->cmd[i])
// 	{
// 		printf("cmd[%d] = %s\n", i, j->p->cmd[i]);
// 		i++;
// 	}
// }

// void		print_env(t_var *var)
// {
// 	while (var)
// 	{
// 		printf("var = %s=%s\n", var->name, var->data);
// 		var = var->next;
// 	}
// }

int			start_exec(t_lexeur **res, t_var *var)
{
	t_job		*j;

	j = malloc(sizeof(t_job));
	j->pgid = 0;
	init_job(j);
	fill_job(j, res);
	fill_process(j, res);
	free_lexeur(res);
	while (j)
	{
		// print_jobs(j);
		// print_env(var);
		launch_job(j, var);
		j = j->next;
	}
	free_parseur(j);
	return (0);
}