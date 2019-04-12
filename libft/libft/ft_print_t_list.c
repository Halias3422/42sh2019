/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_print_t_list.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/20 11:09:13 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/20 12:44:29 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_t_list(t_list *list)
{
	while (list)
	{
		ft_putnbr(list->content_size);
		ft_putstr(" |/| ");
		ft_putstr(list->content);
		ft_putchar('\n');
		list = list->next;
	}
}
