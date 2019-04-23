/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 14:54:35 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 16:22:37 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*str;
	int		i;

	i = -1;
	if (!(str = (char*)malloc(sizeof(char) * size + 1)))
		return (NULL);
	while (++i <= (int)size)
		str[i] = '\0';
	return (str);
}
