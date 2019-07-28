#include "../../includes/termcaps.h"

int				ft_fg(t_process *p, t_var **var)
{
	pid_t	pid;

	pid = ft_atoi(p->cmd[1]);
	printf("|%d|\n", pid);
	kill(-pid, SIGCONT);
	var = NULL;
	return (0);
}
