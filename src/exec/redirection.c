/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirection.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: husahuc <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/19 13:34:01 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/02 09:47:03 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

static int	fd_right(char *path)
{
	if (access(path, F_OK) != -1)
	{
		if (opendir(path) != NULL)
			ft_printf_err("42sh: %s: Is a directory", path);
		else if (access(path, R_OK) == -1)
			ft_printf_err("42sh: %s: Permission denied", path);
		else
			return (1);
	}
	else
		return (1);
	return (0);
}

static int	duplication(t_redirect *redirect, int fd_in, int fd_out)
{
	if (ft_strcmp(redirect->token, ">&") == 0)
	{
		if (ft_strcmp(redirect->fd_out, "-") == 0)
			close(fd_in);
		else if (fd_in > 0 && fd_out > 0)
		{
			if (dup2(fd_out, fd_in) == -1)
				ft_printf_err("42sh: duplication not working\n");
			else
				return (1);
		}
		else
			ft_printf_err("42sh: file number expected");
		return (0);
	}
	if (ft_strcmp(redirect->token, "<&") == 0)
	{
		if (ft_strcmp(redirect->fd_out, "-") == 0)
			close(fd_in);
		else if (fd_in > 0 && fd_out > 0)
		{
			if (fd_out > STDERR_FILENO)
				ft_printf_err("42sh: %d: bad file descriptor", fd_out);
			else if (dup2(fd_in, fd_out) == -1)
				ft_printf_err("42sh: duplication not working\n");
			else
				return (1);
		}
		else
			ft_printf_err("42sh: file number expected");
		return (0);
	}
	return (2);
}

static int	redirection_file(t_process *p, t_redirect *redirect)
{
	if (ft_strcmp(redirect->token, ">") == 0)
	{
		if (!fd_right(redirect->fd_out))
			return (0);
		dup2(redirect->open_out, redirect->fd);
		close(p->file_out);
	}
	if (ft_strcmp(redirect->token, ">>") == 0)
	{
		if (!fd_right(redirect->fd_out))
			return (0);
		dup2(p->file_out, redirect->fd);
		close(p->file_out);
	}
	if (ft_strcmp(redirect->token, "<") == 0)
	{
		if (!fd_right(redirect->fd_out) || !ft_file_exists(redirect->fd_out))
			return (0);
		dup2(p->file_in, STDIN_FILENO);
		close(p->file_in);
	}
	return (1);
}

int			launch_redirection(t_process *p)
{
	t_redirect	*redirect;
	int			fd_in;
	int			fd_out;

	redirect = p->redirect;
	while (redirect)
	{
		fd_in = ft_atoi(redirect->fd_in);
		if (!redirect->fd_in)
			fd_in = 1;
		fd_out = ft_atoi(redirect->fd_out);
		if (redirection_file(p, redirect) == 0)
			return (0);
		if (duplication(redirect, fd_in, fd_out) == 0)
			return (0);
		redirect = redirect->next;
	}
	return (1);
}

void		before_redirection_file(t_redirect *redirect, t_process *p)
{
	if (ft_strcmp(redirect->token, ">") == 0)
	{
		if (fd_right(redirect->fd_out))
		{
			redirect->open_out = open(redirect->fd_out, O_CREAT | O_RDWR | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
	}
	if (ft_strcmp(redirect->token, ">>") == 0)
	{
		if (fd_right(redirect->fd_out))
			p->file_out = open(redirect->fd_out, O_CREAT | O_RDWR | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	if (ft_strcmp(redirect->token, "<") == 0)
	{
		if ((p->file_in = open(redirect->fd_out, O_RDONLY)) < 0)
		{
			ft_printf_err("42sh: no such file or directory: %s\n",
				redirect->fd_out);
		}
	}
	redirect = redirect->next;
}

void		before_redirection(t_process *p)
{
	t_redirect	*redirect;

	while (p)
	{
		p->fd_error = STDERR_FILENO;
		p->fd_in = 0;
		p->fd_out = 1;
		redirect = p->redirect;
		while (redirect)
		{
			before_redirection_file(redirect, p);
			redirect = redirect->next;
		}
		p = get_and_or(p);
	}
}
