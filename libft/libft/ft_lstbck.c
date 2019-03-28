/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstbck.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/14 10:33:54 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/20 11:15:23 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstbck(t_list **cr, char *content, size_t content_size)
{
	t_list	*newend;
	t_list	*temp;

	newend = ft_lstnew(content, content_size);
	if (*cr == NULL)
		*cr = newend;
	else
	{
		temp = *cr;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newend;
	}
}
