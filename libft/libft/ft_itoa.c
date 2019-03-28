/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi2.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 15:29:35 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/04 13:28:39 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_count_length(long long n)
{
	int		a;

	a = 1;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		a++;
	}
	return (a);
}

char		*ft_itoa(long long n)
{
	char	*dest;
	int		a;
	int		neg;

	neg = 0;
	a = ft_count_length(n);
	if (n == -9223372036854775807 - 1)
		return (ft_strdup("-9223372036854775808"));
	if (n < 0)
	{
		neg++;
		n = -n;
	}
	if (!(dest = (char*)malloc(sizeof(char) * (a + 1 + neg))))
		return (NULL);
	dest[a-- + neg] = '\0';
	while (a >= 0)
	{
		dest[a + neg] = n % 10 + 48;
		n = n / 10;
		a--;
	}
	if (neg == 1)
		dest[0] = '-';
	return (dest);
}
