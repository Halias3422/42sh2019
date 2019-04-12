/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lst_totaldel.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/14 10:34:44 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/20 12:44:32 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_totaldel(t_list *alst)
{
	t_list	*data;
	t_list	*lst;

	if (!alst)
		return ;
	data = alst;
	while (data)
	{
		lst = data->next;
		free(data->content);
		data->content_size = 0;
		free(data);
		data = lst;
	}
	alst = NULL;
}
