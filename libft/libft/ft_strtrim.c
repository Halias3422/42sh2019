/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 09:25:37 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 13:55:41 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strtrim(char const *s)
{
	int				start;
	int				end;
	char			*str;

	start = 0;
	end = 0;
	if (!s)
		return (NULL);
	while (s[start] &&
			(s[start] == ' ' || s[start] == '\n' || s[start] == '\t'))
		start++;
	if (start == (int)ft_strlen(s))
	{
		if (!(str = (char*)malloc(sizeof(char))))
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	end = ((int)ft_strlen(s) - 1);
	while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
		end--;
	str = ft_strsub(s, start, (end - start + 1));
	return (str);
}
