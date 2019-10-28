/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_process.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/24 08:57:55 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 09:57:44 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

int			finish_process(t_process *p, t_var *var, char *path)
{
	if (test_builtin(p) != 1)
		get_all_redirections_done(p);
	if (p->exec_builtin == 0)
		exit(1);
	if (find_builtins(p, &var) != 0)
		exit(p->ret);
	if (path == NULL)
	{
		if (p->hash_error)
			ft_printf_err_fd("%s", p->hash_error);
		exit(127);
	}
	ft_execute_function(path, p->cmd, var);
	exit(127);
}

int			launch_process(t_process *p, t_var *var, char *path)
{
	int	ret;

	ret = 0;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, &signal_handler);
	signal(SIGCHLD, SIG_IGN);
/*	if (p->fd_in != STDIN_FILENO)
	{
		ret = dup2(p->fd_in, STDIN_FILENO);
		close(p->fd_in);
	}
	if (p->fd_out != STDOUT_FILENO)
	{
		ret = dup2(p->fd_out, STDOUT_FILENO);
		close(p->fd_out);
	}
*/	finish_process(p, var, path);
	return (0);
}
