/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/02 11:06:30 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/27 11:22:21 by mjalenqu    ###    #+. /#+    ###.fr     */
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
	{"test", &ft_test, 0},
	{"alias", &main_alias, 1},
	{"unalias", &main_unalias, 1},
	{"set", &ft_set, 1},
	{"echo", &ft_echo, 0},
	{"cd", &ft_cd, 1},
	{"type", &ft_type, 0},
	{"export", &ft_export, 1},
	{"unset", &ft_unset, 1},
	{"fc", &ft_fc, 1},
	{"fg", &ft_fg, 1},
	{"jobs", &ft_jobs, 1},
	{"exit", &ft_exit, 1},
	{"hash", &ft_hash, 1},
	{"setenv", &ft_setenv, 1},
	{"unsetenv", &ft_unsetenv, 1},
	{"env", &ft_env, 1}
};

/*void	builtin_redirection(t_process *p)
{
	t_redirect	*redirect;
	int			fd_in;
	int			fd_out;

	redirect = p->redirect;
	while (redirect)
	{
		fd_in = ft_atoi(redirect->fd_in);
		if (!redirect->fd_in)
			fd_in = 1;
		fd_out = ft_atoi(redirect->fd_out);
		if (ft_strcmp(redirect->token, ">") == 0)
			p->fd_out = p->file_out;
		if (ft_strcmp(redirect->token, ">>") == 0)
			p->fd_out = p->file_out;
		if (ft_strcmp(redirect->token, "<") == 0)
			p->fd_in = p->file_in;
		if (ft_strcmp(redirect->token, ">&") == 0)
		{
			if (ft_strcmp(redirect->fd_out, "-") == 0)
				p->fd_in = -1;
			else if (fd_in > 0 && fd_out > 0)
			{
				if (dup2(fd_out, fd_in) == -1)
					ft_printf_err("42sh: duplication not working\n");
			}
			else
				ft_printf_err("42sh: file number expected");
		}
		redirect = redirect->next;
	}
}*/

int		is_builtin_modify(t_process *p)
{
	int i;

	i = -1;
	if (!p->cmd[0])
		return (0);
	while (++i < LEN_BUILTIN_LIST)
	{
		if (ft_strcmp(p->cmd[0], g_builtin_list[i].name) == 0)
		{
			if (g_builtin_list[i].modify_data == 1)
				return (1);
			return (0);
		}
	}
	return (0);
}

int		find_builtins(t_process *p, t_var **var)
{
	int i;

	i = -1;
	if (!p->cmd[0])
		return (0);
	while (++i < LEN_BUILTIN_LIST)
	{
		if (ft_strcmp(p->cmd[0], g_builtin_list[i].name) == 0)
		{
			p->ret = g_builtin_list[i].ptr_builtin(p, var);
			add_list_env(var, LOCAL, ft_strdup("?"), ft_itoa(p->ret));
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
