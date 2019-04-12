/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrev.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/12 08:19:46 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/27 16:55:57 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrev(char *str)
{
	int		i;
	int		len;
	int		len_less;
	char	tmp;

	len = 0;
	while (str[len])
		len++;
	i = 0;
	len_less = len - 1;
	while (i < len / 2)
	{
		tmp = str[i];
		str[i] = str[len_less];
		str[len_less] = tmp;
		i++;
		len_less--;
	}
	return (str);
}
