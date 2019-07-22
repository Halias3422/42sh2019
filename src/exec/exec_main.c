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

int		fork_simple(t_process *p, t_var *var)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
		ft_execute_test(p, var);
	else
		wait(&pid);
	return (1);
}

int		fork_pipe(t_process *p, t_var *var)
{
	pid_t pfd[2];
	pid_t pid;

	pipe(pfd);
	pid = fork();
	if (pid == 0)
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd[0]);
		ft_execute_test(p->next, var);
	}
	else
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		close(pfd[1]);
		ft_execute_test(p, var);
	}
	return (0);
}

int		fork_redirect(t_process *p, t_var *var)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (p->next)
	{
		printf("%s\n", p->next->cmd[0]);
		fd = open(p->next->cmd[0], O_CREAT);
	}
	if (pid == 0)
	{
		ft_execute_test(p, var);
	}
	else
		wait(&pid);
	return (1);
}

void		process_test(t_process *p, t_var *var)
{
	t_process *tmp;

	tmp = p;

	// ici pour redirection
	while (tmp)
	{
		/*if (tmp->split == 'P')
		{
			fork_pipe(p, var);
		}*/
		fork_redirect(tmp, var);
		tmp = tmp->next;
	}
}

void		main_exec(t_job *j, t_var *var)
{
	while (j)
	{
		process_test(j->p, var);
		j = j->next;
	}
}
