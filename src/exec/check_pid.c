/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_pid.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/08 14:23:39 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/14 10:41:36 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

static void	sigerror(char *err, int status)
{
	ft_putstr_fd(err, 2);
	dprintf(2, "%d", status);
	ft_putchar_fd('\n', 2);
}

int	check_pid(int status)
{
	int	ret;

	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 6)
			sigerror("Abort trap: ", 6);
		else if (WTERMSIG(status) == 8)
			sigerror("Floating point exception: ", 8);
		else if (WTERMSIG(status) == 9)
			sigerror("Killed: ", 9);
		else if (WTERMSIG(status) == 10)
			sigerror("Bus error: ", 10);
		else if (WTERMSIG(status) == 11)
			sigerror("Segmentation fault: ", 11);
		else if (WTERMSIG(status) == 13)
			sigerror("Broken pipe: ", 13);
		ret = status + 128;
	}
	else
		ret = WEXITSTATUS(status);
	return (ret);
}