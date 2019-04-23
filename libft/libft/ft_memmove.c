/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 15:30:37 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/11 14:27:21 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	int				i;
	unsigned char	*str_s;
	unsigned char	*str_d;

	str_d = (unsigned char*)dst;
	str_s = (unsigned char*)src;
	if (str_s < str_d)
	{
		i = (int)len;
		while (--i >= 0)
			*(str_d + i) = *(str_s + i);
	}
	else
	{
		i = -1;
		while (++i < (int)len)
			*(str_d + i) = *(str_s + i);
	}
	return (dst);
}
