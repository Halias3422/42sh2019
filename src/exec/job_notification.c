#include "../../includes/exec.h"

int		mark_process_status(pid_t pid, int status)
{
	t_job_list	*job_list;
	t_process	*process;

	job_list = stock(NULL, 10);
	if (pid > 0)
	{
		while (job_list)
		{
			process = job_list->j->p;
			while (process)
			{
				if (process->pid == pid)
				{
					process->status = status;
					if (WIFSTOPPED(status))
					{
						printf("%s\n", "stoped wait");
						process->stoped = 1;
					}
					else
					{
						process->completed = FINISHED;
						printf("terminated :%d\n", pid);
						/*
						a revoir
						if (WIFSIGNALED(signal))
							ft_printf("%d: terminated by signal %d", pid, WTERMSIG(signal));
						*/
					}
				}
				process = process->next;
				return(0);
			}
			job_list = job_list->next;
		}
		return (-1);
	}
	else
		return(-1);
}

void		update_status(void)
{
	int		status;
	pid_t	pid;

	while (1)
	{
		pid = waitpid(WAIT_ANY, &status , WUNTRACED);
		if (mark_process_status(pid, status))
			break;
	}
}

void		job_notification(void)
{
	update_status();
}
