/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirection.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/04 12:19:21 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/18 07:06:42 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
/*
void		test_pipe(t_process *p, t_var *var)
{
	int pid;
	int pfd[2];
	int fd_in = 0;

	while (p)
	{
		pipe(pfd);
		if ((pid = fork()) < 0)
		{
			return ;
		}
		if (pid == 0)
		{
			dup2(fd_in, 0);
			if (p->next != NULL)
				dup2(pfd[1], 1);
			close(pfd[0]);
			execve(p->cmd[0], p->cmd, NULL);
			return;
		}
		else
		{
			wait(NULL);
			close(pfd[1]);
			fd_in = pfd[0];
			p=p->next;
		}
	}
	var = NULL;
}

void		redirection_pipe(t_process *p, t_var *var, t_job *j)
{
	//int pid;
	int	pfd[2];

	pipe(pfd);

	printf("%s\n", "oui1");
	if ((pid = fork()) < 0)
		return ;
	if (pid == 0)
	{
		printf("%s\n", "oui2");
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd[0]);
		printf("%s\n", "oui3");
		main_exec_while(p->next, var);
		return;
	}
	else
	{
		printf("%s\n", "oui4");
		close(pfd[0]);
		dup2(pfd[1], 1);
		close(pfd[1]);
		printf("%s\n", "oui5");
		main_exec_while(p, var);
		return ;
	}
	pipe(pfd);
	printf("%s\n", "oui1");
	close(pfd[0]);
	printf("%s\n", "oui1.5");
	dup2(pfd[1], 1);
	printf("%s\n", "oui1.6");
	close(pfd[1]);
	printf("%s\n", "oui2");
	main_exec_while(p, var, j);
	printf("%s\n", "oui3");
	close(pfd[1]);
	dup2(pfd[0], 0);
	close(pfd[0]);
	printf("%s\n", "oui4");
	main_exec_while(p->next, var, j);
	printf("%s\n", "oui5");
}

void		redirection(t_process *p, t_var *var, t_job *j)
{
	test_pipe(p, var);
	while (p)
	{
		if (p->split == 'P')
		{
			//redirection_pipe(p, var, j);
			test_pipe(p, var);
		}
		p = p->next;
	}
}
*/