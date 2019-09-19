/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memset.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/23 13:37:06 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 16:55:14 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

void	*ft_memset(void *b, int c, size_t l)
{
	size_t			i;
	unsigned char	*r;

	i = 0;
	r = (unsigned char*)b;
	while (i < l)
	{
		r[i] = c;
		i++;
	}
	return (b);
}
