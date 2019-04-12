/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_factorial.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/12 08:55:27 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/12 09:35:20 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_factorial(int nb)
{
	int res;

	res = 1;
	if (nb > 12)
		return (0);
	if (nb < 0)
		return (0);
	while (nb > 0)
	{
		res = res * nb;
		nb--;
	}
	return (res);
}
