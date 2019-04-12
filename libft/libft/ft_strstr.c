/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 16:33:14 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/11 13:49:08 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	char	*str_haystack;

	i = 0;
	str_haystack = (char*)haystack;
	if (ft_strlen(str_haystack) < ft_strlen(needle))
		return (NULL);
	if (ft_strlen(needle) == 0 || (ft_strlen(needle) == 0 &&
				ft_strlen(str_haystack) == 0))
		return (str_haystack);
	while (str_haystack[i])
	{
		j = 0;
		while (str_haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return (str_haystack + (i));
			j++;
		}
		i++;
	}
	return (NULL);
}
