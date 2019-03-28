/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_swap.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 16:49:32 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/31 10:17:05 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char		*ft_swap_let_string(char *str, int let1, int let2)
{
	char	tmp;

	tmp = str[let1];
	str[let1] = str[let2];
	str[let2] = tmp;
	return (str);
}
