/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token_heredoc_creation_margarine.c               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/30 23:09:00 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/30 23:17:49 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

void			init_t_heredoc(t_heredoc *hdoc)
{
	hdoc->to_find = NULL;
	hdoc->current_index = 0;
	hdoc->content = ft_strnew(0);
	hdoc->next = NULL;
	hdoc->prev = NULL;
}

t_heredoc		*add_list_back_heredoc(t_heredoc *heredoc)
{
	t_heredoc	*new;

	new = NULL;
	if (!(new = (t_heredoc*)malloc(sizeof(t_heredoc))))
		return (NULL);
	if (heredoc == NULL)
	{
		init_t_heredoc(new);
		return (new);
	}
	while (heredoc->next != NULL)
		heredoc = heredoc->next;
	init_t_heredoc(new);
	heredoc->next = new;
	new->prev = heredoc;
	return (new);
}

