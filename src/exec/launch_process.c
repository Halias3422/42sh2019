/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launch_process.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/29 18:55:27 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/11 13:22:07 by mdelarbr    ###    #+. /#+    ###.fr     */
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

int			ft_test_path(t_process *p, t_var *var)
{
	char		**path;
	char		*path_env;
	char		*tmp;
	int			i;

	if ((path_env = ft_get_val("PATH", var, ENVIRONEMENT)) == NULL)
		return (-1);
	path = ft_strsplit(path_env, ':');
	i = 0;
	while (path[i])
	{
		tmp = strjoin_path(path[i], p->cmd[0]);
		if (ft_execute_function(tmp, p->cmd, var) == 0)
		{
			ft_tabfree(path);
			return (0);
		}
		i++;
		ft_strdel(&tmp);
	}
	ft_strdel(&tmp);
	ft_tabfree(path);
	return (-1);
}

int			ft_execute_test(t_process *p, t_var *var)
{
	if (p->cmd[0] && (ft_strchr(p->cmd[0], '/') != 0))
		ft_execute_function(p->cmd[0], p->cmd, var);
	else
	{
		if (ft_test_path(p, var) == -1)
			ft_printf("42sh: command not found: %s\n", p->cmd[0]);
	}
	return (0);
}

/*int			launch_duplication(t_process *p)
{
	int	fd_in;
	int	fd_out;

	while (p->redirect)
	{
		//printf("%s %s\n", p->redirect->fd_in, p->redirect->fd_out);
		fd_in = ft_atoi(p->redirect->fd_in);
		if (!p->redirect->fd_in)
			fd_in = 1;
		fd_out = ft_atoi(p->redirect->fd_out);
		if (ft_strcmp(p->redirect->token, ">&") == 0)
		{
			if (ft_strcmp(p->redirect->fd_out, "-") == 0)
				close(fd_in);
			else if (fd_in > 0 && fd_out > 0)
			{
				dup2(fd_out, fd_in);
				if (dup2(fd_out, fd_in) == -1)
					printf("%s\n", "cela ne marche pas");
			}
			else
				ft_printf_err("ceci ne marche pas");
		}
		else if (ft_strcmp(p->redirect->token, "<&") == 0)
		{
			if (ft_strcmp(p->redirect->fd_out, "-") == 0)
				close(fd_in);
			else if (fd_in > 0 && fd_out > 0)
			{
				if (dup2(fd_in, fd_out) == -1)
					printf("%s\n", "cela ne marche pas");
			}
			else
				ft_printf_err("ceci ne marche pas");
		}
		p->redirect = p->redirect->next;
	}
	return (0);
}*/

int			launch_process(t_process *p, t_var *var)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, &signal_handler);
	signal(SIGCHLD, SIG_IGN);
	tcsetpgrp(0, p->pid);
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
	if (p->fd_error != STDERR_FILENO)
	{
		dup2(p->fd_error, STDERR_FILENO);
		close(p->fd_error);
	}
	if (!p->cmd[0])
		exit(1);
	ft_execute_test(p, var);
	exit(1);
}

int			fork_simple(t_job *j, t_process *p, t_var *var)
{
	pid_t		pid;

	launch_redirection(p);
	if (find_builtins(p, var) != 0)
		return (1);
	pid = fork();
	if (pid == 0)
		launch_process(p, var);
	else
	{
		p->pid = pid;
		if (j->pgid == 0)
			j->pgid = pid;
		setpgid(pid, j->pgid);
		if (j->split != '&')
		{
			tcsetpgrp(0, j->pgid);
			wait_process(j->pgid, var);
			signal(SIGTTOU, SIG_IGN);
			tcsetpgrp(0, getpid());
			signal(SIGTTOU, SIG_DFL);
		}
	}
	return (1);
}
