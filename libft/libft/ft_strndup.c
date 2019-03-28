/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strndup.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 12:30:24 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/25 12:35:34 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(char *s1, int n)
{
	int		i;
	char	*tab;

	i = ft_strlen(s1);
	if (n < i)
	{
		if (!(tab = (char *)malloc(sizeof(char) * n + 1)))
			return (NULL);
	}
	else
	{
		if (!(tab = (char *)malloc(sizeof(char) * i + 1)))
			return (NULL);
	}
	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
