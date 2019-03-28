/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/09 09:18:59 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/11 14:28:32 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	*str_s;
	unsigned char	char_c;

	i = -1;
	str_s = (unsigned char*)s;
	char_c = (unsigned char)c;
	while (++i < (int)n)
	{
		if (str_s[i] == char_c)
			return (str_s + i);
	}
	return (NULL);
}
