/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstdel.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/10 13:13:09 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/11 14:34:56 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*data;
	t_list	*lst;

	if (!alst)
		return ;
	data = *alst;
	while (data)
	{
		lst = data->next;
		del(data->content, data->content_size);
		free(data);
		data = lst;
	}
	*alst = NULL;
}
