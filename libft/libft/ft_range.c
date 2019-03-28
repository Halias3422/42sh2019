/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_range.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/12 08:56:55 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/12 08:58:43 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		*ft_range(int min, int max)
{
	int *tab;
	int i;
	int	diff;

	diff = max - min;
	if (min >= max)
		return (NULL);
	if (!(tab = malloc(sizeof(int) * diff)))
		return (NULL);
	i = 0;
	while (i < diff)
	{
		tab[i] = min++;
		i++;
	}
	return (tab);
}
