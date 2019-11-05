/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_jobs_print.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 11:02:51 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:19 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void			print_status_job(char status)
{
	if (status == 'f')
		ft_printf_fd("Done	");
	else if (status == 's')
		ft_printf_fd("Stopped	");
	else
		ft_printf_fd("Running	");
}

void			print_current_job(t_job_list *j, int option, char *name)
{
	if (option != 'p')
		ft_printf_fd("[%d]%c ", j->j->id, j->j->current);
	if (option == 'p' || option == 'l')
		ft_printf_fd("%d ", j->j->pgid);
	if (option != 'p')
	{
		print_status_job(j->j->status);
		ft_printf_fd("%s", name);
	}
	ft_putchar('\n');
}

void			print_all_jobs(t_job_list *j, int option)
{
	char		*name;

	if (j)
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
		if (ft_strncmp(name, arg, ft_strlen(arg)) == 0
		|| j->j->id == ft_atoi(arg))
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
		ft_printf_err_fd("21sh: jobs: %s: no such job\n", arg);
}
