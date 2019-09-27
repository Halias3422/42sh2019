
#include "../../includes/builtin.h"
#include "../../includes/exec.h"

static void	 write_alias_on_exit(t_var *var)
{
	t_pos *p;

	p = stock(NULL, 1);
	chdir(p->path);
	p->alias = open("./.aliases", O_WRONLY | O_TRUNC | O_CREAT , 0664);
	while (var)
	{
		if (var->type == ALIAS)
		{
			write(p->alias, var->name, ft_strlen(var->name));
			write(p->alias, "=", 1);
			write(p->alias, var->data, ft_strlen(var->data));
			write(p->alias, "\n", 1);
		}
		var = var->next;
	}
}

void			free_pos()
{
	t_pos *pos;

	pos = stock(NULL, 1);
	ft_strdel(&pos->prompt);
	ft_strdel(&pos->path);
	ft_strdel(&pos->ctrl_hist_cmd);
	ft_strdel(&pos->saved_ans);
}

int		error_exit(int i)
{
	if (i == 1)
		ft_printf_err("42sh: exit: {B.T.red.}error{eoc}: Too many arguments\n");
	return (1);
}

int		ft_exit(t_process *p, t_var **var)
{
	int	status;

	status = ft_atoi(p->cmd[1]);
	if (p->cmd && p->cmd[1] && p->cmd[2])
		return (error_exit(1));		
	if (p->split == 'P' || p->fd_in != STDIN_FILENO)
		return (status);
	if (status < 0)
		ft_printf_err("42sh: exit: %s: numeric argument required\n", p->cmd[1]);
	else
	{
		free_hash_table();
		ft_printf("exit\n");
	}
	write_alias_on_exit(*var);
	free_pos();
	exit(status);
}
