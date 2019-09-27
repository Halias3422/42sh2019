/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token_free.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/22 14:33:05 by bjuarez      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/20 13:19:50 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void			free_heredoc(t_tok *in)
{
	if (in->herestr != NULL)
	{
		ft_strdel(&in->herestr);
		in->herestr = NULL;
	}
	if (in->fullheredoc != NULL)
	{
		ft_strdel(&in->fullheredoc);
		in->fullheredoc = NULL;
	}
}

static void		free_tok(t_tokench *tok)
{
	t_tokench	*tmp;

	while (tok && tok->prev != NULL)
		tok = tok->prev;
	tmp = tok;
	while (tmp && tmp->next != NULL)
	{
		tmp = tok->next;
		ft_strdel(&tok->token);
		tok->token = NULL;
		tok->prev = NULL;
		tok->next = NULL;
		free(tok);
		tok = tmp;
	}
	ft_strdel(&tok->token);
	tok->token = NULL;
	tok->prev = NULL;
	tok->next = NULL;
	free(tok);
}

void			free_all_check_token(t_tok *in, t_tokench *tok)
{
	ft_strdel(&in->dquote_d);
	free_heredoc(in);
	free_tok(tok);
}
