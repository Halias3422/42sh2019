/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_num_length.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/21 10:29:54 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/01 09:17:42 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t			check_num_length(long long nb)
{
	size_t		length;

	length = 0;
	while (nb >= 1 || nb <= -1)
	{
		nb = nb / 10;
		length++;
	}
	if (length == 0)
		return (1);
	return (length);
}
