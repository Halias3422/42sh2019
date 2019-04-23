/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi_base.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 08:02:01 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/06 09:23:41 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

long long		ft_atoi_base(char *nb, int base)
{
	int			i;
	int			end;
	long long	res;
	int			neg;

	res = 0;
	end = 0;
	neg = 0;
	while (nb[end] == '+' || nb[end] == '-')
		neg = nb[end++] == '-' ? 1 : 0;
	while ((nb[end] <= '9' ? nb[end] - 48 : nb[end] - 87) < base && nb[end])
		end++;
	i = --end + 1;
	while (--i >= 0 + neg)
		res += nb[i] <= '9' ? (nb[i] - 48) * ft_power(base, end - i) :
			(nb[i] - 87) * ft_power(base, end - i);
	return (neg == 1 ? -res : res);
}
