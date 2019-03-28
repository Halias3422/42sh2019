/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 16:16:49 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/15 14:40:37 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str_s;

	i = -1;
	str_s = (char*)s;
	while (str_s[++i] != '\0')
	{
		if (str_s[i] == (char)c)
			return (&str_s[i]);
	}
	if (c == 0 && s)
		return (&str_s[ft_strlen(s)]);
	return (NULL);
}
