/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 12:03:23 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/11 14:25:53 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*str_dst;
	char	*str_src;

	i = -1;
	str_dst = (char*)dst;
	str_src = (char*)src;
	if (n == 0 || dst == src)
		return (dst);
	while (++i < n)
		str_dst[i] = str_src[i];
	return (dst);
}
