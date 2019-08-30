
#include "../../includes/builtin.h"
#include "../../includes/exec.h"

int		ft_exit(t_process *p, t_var **var)
{
	int	status;

	if (p->next != NULL)
		return (0);
	var = NULL;
	status = ft_atoi(p->cmd[1]);
	if (status < 0)
		ft_printf_err("42sh: exit: %s: numeric argument required\n", p->cmd[1]);
	else
		ft_printf("exit\n");
	exit(status);
}
