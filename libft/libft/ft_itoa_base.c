/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 13:11:15 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/27 16:04:45 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa_base2(long num, int base, char *str)
{
	int		i;
	int		neg;
	int		rest;

	i = 0;
	neg = 0;
	rest = 0;
	if (num < 0)
	{
		base == 10 ? neg = 1 : neg;
		num = -num;
	}
	while (num != 0)
	{
		rest = num % base;
		str[i++] = (rest > 9) ? (rest - 10) + 'a' : rest + '0';
		num = num / base;
	}
	if (neg)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_strrev(str));
}

char		*ft_itoa_base(int value, int base)
{
	char *str;
	long num;

	num = value;
	if (num == 0)
		return ("0");
	if ((str = (char *)malloc(sizeof(char) * 33)) == NULL)
		return (NULL);
	return (ft_itoa_base2(num, base, str));
}
