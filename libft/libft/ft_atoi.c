/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 14:34:54 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/28 16:24:52 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int							ft_atoi(const char *str)
{
	size_t					i;
	unsigned long long int	nb;
	int						neg;

	i = 0;
	nb = 0;
	neg = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			neg++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		nb = (nb * 10 + (str[i++] - 48));
	if (nb > 9223372036854775807 && neg == 1)
		return (0);
	if (nb > 9223372036854775807 && neg == 0)
		return (-1);
	if (neg == 1)
		nb = nb * -1;
	return (nb);
}
