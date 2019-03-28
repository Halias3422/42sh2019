/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 10:20:03 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/11 14:32:47 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		j;
	char	*str_haystack;

	i = 0;
	str_haystack = (char*)haystack;
	if ((ft_strlen(str_haystack) < ft_strlen(needle)))
		return (NULL);
	if (ft_strlen(needle) == 0 || (ft_strlen(needle) == 0 &&
				ft_strlen(str_haystack) == 0))
		return (str_haystack);
	while (str_haystack[i])
	{
		j = 0;
		while (str_haystack[i + j] == needle[j] && (i + j) < (int)len)
		{
			if (needle[j + 1] == '\0')
				return (str_haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
