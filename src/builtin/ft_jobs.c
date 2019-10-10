/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_jobs.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 11:08:12 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 12:44:36 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void			print_status_job(char status)
{
	if (status == 'f')
		ft_printf("Done	");
	else if (status == 's')
		ft_printf("Stopped	");
	else
		ft_printf("Running	");
}

int				ft_jobs_option(char **cmd, int *i)
{
	int			j;
	int			ret;

	ret = 0;
	while (cmd[*i] && cmd[*i][0] == '-')
	{
		j = 1;
		if (ft_strcmp(cmd[*i], "--") == 0)
			return (ret);
		while (cmd[*i][j])
		{
			if (cmd[*i][j] == 'p')
				ret = 'p';
			else if (cmd[*i][j] == 'l')
				ret = 'l';
			else
				return (cmd[*i][j]);
			j++;
		}
		*i += 1;
	}
	return (ret);
}

void			print_current_job(t_job_list *j, int option, char *name)
{
	if (option != 'p')
		ft_printf("[%d]%c ", j->j->id, 'x');
	if (option == 'p' || option == 'l')
		ft_printf("%d ", j->j->pgid);
	if (option != 'p')
	{
		print_status_job(j->j->status);
		ft_printf("%s", name);
	}
	ft_putchar ('\n');
}

char			*built_job_name(t_job_list *j, char *name)
{
	int			i;

	i = 0;
	while (j->j->p->cmd[i])
	{
		name = ft_strjoinf(name, j->j->p->cmd[i], 1);
		if (j->j->p->cmd[i + 1])
			name = ft_strjoinf(name, " ", 1);
		i++;
	}
	return (name);
}

void			print_all_jobs(t_job_list *j, int option)
{
	char		*name;

	name = ft_strnew(0);
	while (j)
	{
		name = built_job_name(j, name);
		print_current_job(j, option, name);
		j = j->next;
		ft_strdel(&name);
		if (j)
			name = ft_strnew(0);
	}
}

void			print_selected_jobs(t_job_list *j, int option, char *arg)
{
	char		*name;
	int			check;

	check = 0;
	name = ft_strnew(0);
	while (j)
	{
		name = built_job_name(j, name);
		if (ft_strncmp(name, arg, ft_strlen(arg)) == 0 || j->j->id == ft_atoi(arg))
		{
			print_current_job(j, option, name);
			check += 1;
		}
		j = j->next;
		ft_strdel(&name);
		if (j)
			name = ft_strnew(0);
	}
	if (!check)
		ft_printf_err("42sh: jobs: %s: no such job\n", arg);
}

int				ft_jobs(t_process *p, t_var **var)
{
	t_job_list	*job_list;
	int			option;
	int			i;

	(void)var;
	i = 1;
	option = ft_jobs_option(p->cmd, &i);
	if (option != 'l' && option != 'p' && option != 0)
	{
		ft_printf_err("42sh: jobs: -%c: invalid option\n", option);
		ft_printf_err("jobs: usage: jobs [-l|-p] [job_id...]\n");
		return (2);
	}
	job_list = stock(NULL, 10);
	if (p->cmd[i] == NULL)
		print_all_jobs(job_list, option);
	while (p->cmd[i])
		print_selected_jobs(job_list, option, p->cmd[i++]);
	return (0);
}
