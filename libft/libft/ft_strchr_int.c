/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strchr_int.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/12 08:24:04 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 08:40:13 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_strchr_int(char *s, int c)
{
	int		i;
	char	*str_s;

	i = -1;
	str_s = (char*)s;
	while (str_s[++i] != '\0')
	{
		if (str_s[i] == (char)c)
			return (i);
	}
	if (c == 0 && s)
		return (i);
	return (-1);
}
