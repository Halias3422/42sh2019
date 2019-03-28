/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 10:56:36 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/12 09:36:20 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	rep;

	rep = (size_t)ft_strlen(dst) + (size_t)ft_strlen(src);
	i = 0;
	j = 0;
	if ((size_t)ft_strlen(dst) >= size)
		return (ft_strlen(src) + size);
	while (dst[i])
		i++;
	while (src[j] && ((i + 1) < size))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (rep);
}
