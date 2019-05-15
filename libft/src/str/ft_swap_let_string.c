/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_swap_let_string.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 16:49:32 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/13 09:22:34 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

char		*ft_swap_let_string(char *str, int let1, int let2)
{
	char	tmp;

	tmp = str[let1];
	str[let1] = str[let2];
	str[let2] = tmp;
	return (str);
}
