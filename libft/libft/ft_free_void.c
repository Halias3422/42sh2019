/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_voids.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/22 12:45:00 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/25 10:35:30 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_void(void *str, void *str2, void *str3, void *str4)
{
	if (str)
		free(str);
	if (str2)
		free(str2);
	if (str3)
		free(str3);
	if (str4)
		free(str4);
}
