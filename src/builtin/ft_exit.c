
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

void	free_hist(t_hist *hist)
{
	t_hist *tmp;

	tmp = hist;
	while (hist)
	{
		tmp = hist->next;
		ft_strdel(&hist->cmd);
		free(hist);
		hist = tmp;
	}
	hist = NULL;
}

int		ft_exit(t_process *p, t_var **var)
{
	t_hist	*tmp;
	t_hist	*hist;
	int	status;

	hist = stock(NULL, 8);
	tmp = hist;
	write_alias_on_exit(*var);
	free_pos();
	status = ft_atoi(p->cmd[1]);
	if (status < 0)
		ft_printf_err("42sh: exit: %s: numeric argument required\n", p->cmd[1]);
	else
	{
		while (hist)
		{
			tmp = hist;
			printf("%s\n", hist->cmd);
			ft_strdel(&hist->cmd);
			hist = hist->next;
			free(tmp);
		}
		// free_t_hist(*ghist);
		// free_env(*var);
		free_hash_table();
		ft_printf("exit\n");
	}
	exit(status);
}
