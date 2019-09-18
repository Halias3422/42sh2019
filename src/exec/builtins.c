/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/02 11:06:30 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/18 10:03:23 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/builtin.h"
#include "../../includes/termcaps.h"

/*
** TODO faire en sorte qu'on puisse exec un builtins au milieu d'autres
** comme ls.
*/

const t_builtin	g_builtin_list[LEN_BUILTIN_LIST] =
{
	{"test", &ft_test},
	{"alias", &main_alias},
	{"unalias", &main_unalias},
	{"set", &ft_set},
	{"echo", &ft_echo},
	{"cd", &ft_cd},
	{"type", &ft_type},
	{"export", &ft_export},
	{"unset", &ft_unset},
	{"fc", &ft_fc},
	{"fg", &ft_fg},
	{"jobs", &ft_jobs},
	{"exit", &ft_exit},
	{"hash", &ft_hash},
	{"setenv", &ft_setenv},
	{"unsetenv", &ft_unsetenv},
	{"env", &ft_env}
};

int		find_builtins(t_process *p, t_var *var)
{
	int i;

	i = -1;
	if (!p->cmd[0])
		return (0);
	while (++i < LEN_BUILTIN_LIST)
	{
		if (ft_strcmp(p->cmd[0], g_builtin_list[i].name) == 0)
		{
			p->ret = g_builtin_list[i].ptr_builtin(p, &var);
			return (1);
		}
	}
	return (0);
}

int		test_builtin(t_process *p)
{
	int i;

	i = -1;
	if (!p->cmd[0])
		return (0);
	while (++i < LEN_BUILTIN_LIST)
	{
		if (ft_strcmp(p->cmd[0], g_builtin_list[i].name) == 0)
			return (1);
	}
	return (0);
}
