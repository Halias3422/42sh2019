/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_isprime.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/12 09:37:05 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/12 09:39:11 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprime(int nb)
{
	int i;
	int j;

	j = (nb / 2) + 1;
	i = 3;
	if (nb == 0)
		return (0);
	if (nb == 1)
		return (0);
	if (nb % 2 == 0)
		return (0);
	while (i < nb)
	{
		if (i > j)
			return (1);
		if (i % nb == 0)
			return (0);
		i += 2;
	}
	return (1);
}
