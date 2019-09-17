#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

/*int			launch_redirection(t_process *p)
{
	t_redirect	*redirect;
	int			fd_in;
	int			fd_out;

	redirect = p->redirect;
	while (redirect)
	{
		fd_in = ft_atoi(p->redirect->fd_in);
		if (!p->redirect->fd_in)
			fd_in = 1;
		fd_out = ft_atoi(p->redirect->fd_out);
		if (ft_strcmp(redirect->token, ">") == 0)
		{
			dup2(p->fd_out = open(redirect->fd_out, O_CREAT | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH), STDOUT_FILENO);
		}
		else if (ft_strcmp(redirect->token, ">>") == 0)
		{
			dup2(p->fd_out = open(redirect->fd_out, O_CREAT | O_WRONLY | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH), STDOUT_FILENO);
		}
		else if (ft_strcmp(redirect->token, "<") == 0)
		{
			if ((p->fd_in = open(redirect->fd_out, O_RDONLY)) < 0)
			{
				ft_printf_err("42sh: no such file or directory: %s\n", redirect->fd_out);
				return (0);
			}
		}
		else if (ft_strcmp(p->redirect->token, ">&") == 0)
		{
			if (ft_strcmp(p->redirect->fd_out, "-") == 0)
				close(fd_in);
			else if (fd_in > 0 && fd_out > 0)
			{
				if (dup2(fd_out, fd_in) == -1)
					printf("%s\n", "cela ne marche pas");
			}
			else
				ft_printf_err("ceci ne marche pas");
		}
		else if (ft_strcmp(p->redirect->token, "<&") == 0)
		{
			if (ft_strcmp(p->redirect->fd_out, "-") == 0)
				close(fd_in);
			else if (fd_in > 0 && fd_out > 0)
			{
				if (dup2(fd_in, fd_out) == -1)
					printf("%s\n", "cela ne marche pas");
			}
			else
				ft_printf_err("ceci ne marche pas");
		}
		redirect = redirect->next;
	}
	return (1);
}*/

int			launch_redirection(t_process *p)
{
	t_redirect	*redirect;
	int			fd_in;
	int			fd_out;

	redirect = p->redirect;
	while (redirect)
	{
		fd_in = ft_atoi(p->redirect->fd_in);
		if (!p->redirect->fd_in)
			fd_in = 1;
		fd_out = ft_atoi(p->redirect->fd_out);
		if (ft_strcmp(redirect->token, ">") == 0)
		{
			p->fd_out = open(redirect->fd_out, O_CREAT | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
		else if (ft_strcmp(redirect->token, ">>") == 0)
		{
			p->fd_out = open(redirect->fd_out, O_CREAT | O_WRONLY | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
		else if (ft_strcmp(redirect->token, "<") == 0)
		{
			if ((p->fd_in = open(redirect->fd_out, O_RDONLY)) < 0)
			{
				ft_printf_err("42sh: no such file or directory: %s\n", redirect->fd_out);
				return (0);
			}
		}
		else if (ft_strcmp(p->redirect->token, ">&") == 0)
		{
			if (ft_strcmp(p->redirect->fd_out, "-") == 0)
				close(fd_in);
			else if (fd_in > 0 && fd_out > 0)
			{
				if (dup2(fd_out, fd_in) == -1)
					printf("%s\n", "cela ne marche pas");
			}
			else
				ft_printf_err("ceci ne marche pas");
		}
		else if (ft_strcmp(p->redirect->token, "<&") == 0)
		{
			if (ft_strcmp(p->redirect->fd_out, "-") == 0)
				close(fd_in);
			else if (fd_in > 0 && fd_out > 0)
			{
				if (dup2(fd_in, fd_out) == -1)
					printf("%s\n", "cela ne marche pas");
			}
			else
				ft_printf_err("ceci ne marche pas");
		}
		redirect = redirect->next;
	}
	return (1);
}
