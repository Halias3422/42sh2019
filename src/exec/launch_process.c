/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launch_process.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/29 18:55:27 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/08 08:18:18 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

int			ft_execute_function(char *path, char **arg, t_var *var)
{
	char		**tab_var;

	tab_var = split_env(var);
	if (execve(path, arg, tab_var) == -1)
		return (-1);
	return (0);
}

int			launch_process(t_process *p, t_var *var, char *path)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, &signal_handler);
	signal(SIGCHLD, SIG_IGN);
	//tcsetpgrp(0, p->pid);
	if (p->fd_in != STDIN_FILENO)
	{
		dup2(p->fd_in, STDIN_FILENO);
		close(p->fd_in);
	}
	if (p->fd_out != STDOUT_FILENO)
	{
		dup2(p->fd_out, STDOUT_FILENO);
		close(p->fd_out);
	}
	if (!launch_redirection(p))
		exit(1);
	if (find_builtins(p, &var) != 0)
		exit(p->ret);
	// if (path == NULL)
	// 	ft_printf("42sh: %s: command not found\n", p->cmd[0]);
	ft_execute_function(path, p->cmd, var);
	exit(127);
}

void		update_pid(t_process *p, t_job *j, pid_t pid, t_var **var)
{
	int status;

	p->pid = pid;
	if (j->pgid == 0)
		j->pgid = pid;
	setpgid(pid, j->pgid);
	p->ret = 0;
	if (p->split != 'P' && j->split != '&')
	{
		tcsetpgrp(0, j->pgid);
		wait_process_pid(p->pid, var);
		signal(SIGTTOU, SIG_IGN);
		tcsetpgrp(0, getpid());
		signal(SIGTTOU, SIG_DFL);
		if (p->fd_in != 0)
		{
			waitpid(WAIT_ANY, &status, WNOHANG);
			close(p->fd_in);
		}
	}
}

int			fork_simple(t_job *j, t_process *p, t_var **var)
{
	pid_t		pid;
	char		*cmd_path;

	cmd_path = NULL;
	if (!p || !p->cmd || !p->cmd[0])
		return (-1);
	p->background = j->split == '&' ? 1 : 0;
	if (j->split != '&' && is_builtin_modify(p))
	{
		if (find_builtins(p, var) != 0)
			return (1);
	}
	cmd_path = check_path_hash(var, p->cmd, -1, NULL);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
		launch_process(p, *var, cmd_path);
	else
		update_pid(p, j, pid, var);
//	ft_strdel(&cmd_path);
	return (1);
}
