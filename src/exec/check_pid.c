/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_pid.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/08 14:23:39 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/10 11:23:12 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

void	check_pid(int pid)
{
	if (pid == 11)
		ft_printf("Process killed by a segfault : 11\n");
	else if (pid == 10)
		ft_printf("Bus error: 10\n");
	else if (pid == 6)
		ft_printf("Abort : 6\n");
}