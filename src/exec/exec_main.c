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
	//if (find_builtins(p, var) == 0)
	//{
		if (ft_strchr(p->cmd[0], '/') != 0)
		{
			ft_execute_function(p->cmd[0], p->cmd, var);
		}
		else
		{
			if (ft_test_path(p, var) == -1)
				printf("42sh: command not found: %s\n", p->cmd[0]);
		}
	//}
	//exit(0);
	return (0);
}

int			launch_process(t_process *p, t_var *var, int infile, int outfile, int errfile)
{
	pid_t		pid;

	pid = getpid();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, &signal_handler);
	signal(SIGCHLD, SIG_IGN);
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
	exit(1);
	//return (1);
}

int			fork_simple(t_job *j, t_process *p, t_var *var, int infile, int outfile, int errfile)
{
	pid_t		pid;
	if (find_builtins(p, var) != 0)
		return (1);

	pid = fork();
	if (pid == 0)
		launch_process(p, var, infile, outfile, errfile);
	else
	{
		p->pid = pid;
		if (j->pgid == 0)
			j->pgid = pid;
		setpgid(pid, j->pgid);
		if (j->split != '&')
		{
			tcsetpgrp(0, j->pgid);
			wait_process(j->pgid);
			signal(SIGTTOU, SIG_IGN);
			tcsetpgrp(0, getpid());
			signal(SIGTTOU, SIG_DFL);
		}
	}
	return (1);
}

t_process	*get_and_or(t_process *p)
{
	t_process	*p_next;

	if (p->ret == 0 && p->split == '|')
		return (p->next->next);
	else if (p->ret != 0 && p->split == '&')
		return (p->next->next);
	return (p->next);
	p_next = p;
	while (p_next)
	{
		if (p->split == '|' && p_next->split == '&')
			return (p_next);
		else if (p->split == '&' && p_next->split == '|')
			return (p_next);
		p_next = p_next->next;
	}
	return (NULL);
}

void		launch_job(t_job *j, t_var *var)
{
	t_process	*tmp;
	int			infile;
	int			outfile;
	int			mypipe[2];

	infile = 0;
	tmp = j->p;
	add_job(j);
	j->status = 'r';
	while (tmp)
	{
		if (tmp->split == 'P')
		{
			pipe(mypipe);
			outfile = mypipe[1];
		}
		else
			outfile = 1;
		fork_simple(j, tmp, var, infile, outfile, 2);
		if (infile != STDIN_FILENO)
			close(infile);
		if (outfile != STDOUT_FILENO)
			close(outfile);
		infile = mypipe[0];
		tmp = get_and_or(tmp);
	}
	if (j->split == '&')
		print_start_process(j);
	else if (job_is_stoped(j))
		j->notified = 1;
	else
		remove_job(j->id);
}

void		main_exec(t_job *j, t_var *var)
{
	while (j)
	{
		launch_job(j, var);
		j = j->next;
	}
}
