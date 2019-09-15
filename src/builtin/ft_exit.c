
#include "../../includes/builtin.h"
#include "../../includes/exec.h"

static void	 write_alias(t_var *var)
{
	t_pos *p;

	p = stock(NULL, 1);
	chdir(p->path);
	p->alias = open("./.aliases", O_WRONLY | O_TRUNC | O_CREAT , 0664);
	while (var)
	{
		if (var->type == 2)
		{
			write(p->alias, var->name, ft_strlen(var->name));
			write(p->alias, "=", 1);
			write(p->alias, var->data, ft_strlen(var->data));
			write(p->alias, "\n", 1);
		}
		var = var->next;
	}
}

int		ft_exit(t_process *p, t_var **var)
{
	int	status;

	write_alias(*var);
	if (p->next != NULL)
		return (0);
	status = ft_atoi(p->cmd[1]);
	if (status < 0)
		ft_printf_err("42sh: exit: %s: numeric argument required\n", p->cmd[1]);
	else
		ft_printf("exit\n");
	exit(status);
}
