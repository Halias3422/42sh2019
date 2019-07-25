/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job_controll.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: husahuc <husahuc@student.42.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 14:45:30 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/21 16:38:33 by husahuc     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

void		wait_job()
{
	int status;

	waitpid(WAIT_ANY, &status, WUNTRACED);
}

void		put_foreground(t_job *j, int cont)
{
	//tcsetpgrp(STDIN_FILENO, j->pgid);

	if (cont)
		kill(-j->pgid, SIGCONT);

	//wait_job();
	int status;
	waitpid(WAIT_ANY, &status, WUNTRACED);
}

void		put_background(t_job *j, int cont)
{
	if (cont)
		kill(j->pgid, SIGCONT);
	//printf("%d\n", j->pgid);
	//kill(j->pgid, SIGSTOP);
}
