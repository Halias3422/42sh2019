/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcmp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/09 09:34:41 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/11 16:35:52 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	while (((unsigned char*)s1)[i] == ((unsigned char*)s2)[i] && i < n - 1)
		i++;
	if (i == n)
		return (0);
	i = ((unsigned char*)s1)[i] - ((unsigned char*)s2)[i];
	return (i);
}
