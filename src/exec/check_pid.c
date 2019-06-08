/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_pid.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/08 14:23:39 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/08 14:24:57 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "exec.h"

void    check_pid(int pid)
{
    if (pid == 11)
		ft_printf("Process killed by a segfault : 11\n");
    else if (pid == 10)
        ft_printf("Bus error: 10\n");
}