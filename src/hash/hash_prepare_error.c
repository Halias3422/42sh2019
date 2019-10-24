/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_prepare_error.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 15:06:52 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 07:31:52 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/hash.h"

void		prepare_error_message_for_hash(int error, char *str)
{
	t_process	*p;

	p = to_stock(NULL, 3);
	if (p->hash_error)
		return ;
	p->hash_error = ft_strnew(0);
	p->hash_error = ft_strjoinf(p->hash_error, "42sh: ", 1);
	if (str)
		p->hash_error = ft_strjoinf(p->hash_error, str, 1);
	if (error == 1)
		p->hash_error = ft_strjoinf(p->hash_error, ": is a directory\n", 1);
	else if (error == 2)
		p->hash_error = ft_strjoinf(p->hash_error,
			   	": No such file or directory\n", 1);
	else if (error == 3)
		p->hash_error = ft_strjoinf(p->hash_error, ": permission denied\n", 1);
	else if (error == 4)
		p->hash_error = ft_strjoinf(p->hash_error, ": command not found\n", 1);
}
