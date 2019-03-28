/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memccpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 15:24:10 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/11 14:20:47 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	int				i;
	unsigned char	*str_d;
	unsigned char	*str_s;

	str_d = (unsigned char*)dst;
	str_s = (unsigned char*)src;
	i = -1;
	while (++i < (int)n)
	{
		str_d[i] = str_s[i];
		if (str_s[i] == ((unsigned char)c))
			return (&dst[i + 1]);
	}
	return (NULL);
}
