/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ispsace.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 12:53:23 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 12:57:13 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

int		is_space(char c)
{
	if (c != '\0' && (c == ' ' || c == '\t'))
		return (1);
	return (0);
}
