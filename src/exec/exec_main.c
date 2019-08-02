/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_main.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/30 11:29:02 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/08 14:23:01 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

void		ft_tabfree(char **res)
{
	int i;

	i = -1;
	while (res[++i])
		free(res[i]);
	free(res);
}

/*int			use_execve(char **res, t_var *l_var)
{
	char	**path;
	char	*tmp;
	int		i;
	t_var	*start;

	start = l_var;
	while (start->next && ft_strcmp(start->name, "PATH") != 0)
		start = start->next;
	if (!(start))
		return (-1);
	path = ft_strsplit(start->data, ':');
	i = 0;
	while (path[i])
	{
		tmp = strjoin_path(path[i], res[0]);
		if (use_execve_acces(tmp, res, l_var) == 0)
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

int			exec_path(char **res, t_var *var)
{
	if (access(res[0], F_OK) == 0)
		return (solve_execve(res[0], res, var));
	return (-1);
}

int			solve_execve(char *path, char **arg, t_var *var)
{
	char	**array;
	pid_t	pid;

	pid = fork();
	array = split_env(var);
	if (pid == 0)
	{
		if (execve(path, arg, array) == -1)
		{
			signal_list();
			ft_tabfree(array);
			return (-1);
		}
	}
	else
	{
		wait(&pid);
	}
	check_pid(pid);
	ft_tabfree(array);
	return (1);
}

int			main_exec_while(t_process *p, t_var *var)
{
	if (find_builtins(p, var) == 0)
	{
		if (ft_strchr(p->cmd[0], '/') != 0)
		{
			if (exec_path(p->cmd, var) != 1)
			{
				cnf_print_error(p->cmd[0]);
				return (-1);
			}
		}
		else
		{
			if (use_execve(p->cmd, var) == -1)
			{
				cnf_print_error(p->cmd[0]);
				return (-1);
			}
		}
	}
	return (0);
}*/

/*int		fork_pipe(t_process *p, t_var *var)
{
	pid_t pfd[2];
	pid_t pid;

	pipe(pfd);
	pid = fork();
	if (pid == 0)
	{
		close(pfd[1]);
		fork_simple(p->next, var, pfd[0], 1, 2, 0);
		close(pfd[0]);
	}
	else
	{
		close(pfd[0]);
		fork_simple(p, var, 0, pfd[1], 2, 0);
		close(pfd[1]);
	}
	exit (0);
}*/

// new proposition

int		ft_execute_function(char *path, char **arg, t_var *var)
{
	char **tab_var;

	tab_var = split_env(var);
	if (execve(path, arg, tab_var) == -1)
		return (-1);
	return (0);
}

int		ft_test_path(t_process *p, t_var *var)
{
	char	**path;
	char	*path_env;
	char	*tmp;
	int		i;

	if ((path_env = ft_get_val("PATH", var, ENVIRONEMENT)) == NULL)
	{
		return (-1);
	}
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

int		ft_execute_test(t_process *p, t_var *var)
{
	if (find_builtins(p, var) == 0)
	{
		if (ft_strchr(p->cmd[0], '/') != 0)
		{
			ft_execute_function(p->cmd[0], p->cmd, var);
		}
		else
		{
			if (ft_test_path(p, var) == -1)
				printf("42sh: command not found: %s\n", p->cmd[0]);
		}
	}
	return (0);
}

int			launch_process(t_process *p, t_var *var, int infile, int outfile, int errfile, int foreground)
{
	pid_t pid;

	pid = getpid();

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_DFL);
	foreground = 0;
	tcsetpgrp(0, p->pid);

	if (infile != STDIN_FILENO)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	if (errfile != STDERR_FILENO)
	{
		dup2(errfile, STDERR_FILENO);
		close(errfile);
	}
	ft_execute_test(p, var);
	exit (1);
}

int		fork_simple(t_job *j ,t_process *p, t_var *var, int infile, int outfile, int errfile, int foreground)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		launch_process(p, var, infile, outfile, errfile, foreground);
	}
	else
	{
		p->pid = pid;
		if (!j->pgid)
			j->pgid = pid;
		setpgid(pid, j->pgid);
		if (foreground == 0)
		{
			tcsetpgrp(0, j->pgid);
			wait_process(p->pid);
			signal(SIGTTOU, SIG_IGN);
			tcsetpgrp(0, getpid());
			signal(SIGTTOU, SIG_DFL);
		}
	}
	return (1);
}

void		launch_job(t_job *j, t_var *var, int foreground)
{
	t_process *tmp;
	int infile;
	int outfile;
	int mypipe[2];

	infile = 0;
	tmp = j->p;
	while (tmp)
	{
		if (tmp->split == 'P')
		{
			pipe(mypipe);
			outfile = mypipe[1];
		}
		else
			outfile = 1;
		fork_simple(j, tmp, var, infile, outfile, 2, foreground);
		tmp = tmp->next;
		if (infile != STDIN_FILENO)
			close(infile);
		if (outfile != STDOUT_FILENO)
			close(outfile);
		infile = mypipe[0];
	}
	if (j->split == '&')
		print_start_process(j);
}

void		main_exec(t_job *j, t_var *var)
{
	t_job *next;
	t_job *last;

	while (j)
	{
		next = j->next;
		if (j->split == '&')
			launch_job(j, var, 1);
		else
			launch_job(j, var, 0);
		last = j;
		j = next;
	}
}
