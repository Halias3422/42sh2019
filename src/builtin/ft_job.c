/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_job.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/17 04:49:29 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/18 07:08:15 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
/*
#include "../../includes/exec.h"
#include "../../includes/builtin.h"

char		*fill_str(t_process *p)
{
	int			i;
	char		*res;

	i = 0;
	res = ft_strdup(res);
	while (p->cmd[i])
	{
		ft_strjoin_free(res, p->cmd[i]);
		i++;
	}
	return (res);
}

int			ft_job(t_process *p, t_var *var, t_job *j)
{
	char	**res;
	char	*str;

	str = fill_str(p);
	res = ft_strsplit(str, ' ');

	return (0);
}
*/