/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token_free.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bjuarez <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/22 14:33:05 by bjuarez      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/13 09:27:59 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

int				check_in_2(t_pos *pos)
{
	int			i;
	int			nb;

	i = 0;
	nb = 0;
	while (pos->ans && pos->ans[i] != '\0')
	{
		if (pos->ans[i] > 32 && pos->ans[i] < 127)
		{
			if (verif_token(&pos->ans[i]) > 0 && nb == 0)
				return (1);
			nb++;
		}
		i++;
	}
	return (1);
}

void			free_heredoc(t_tok *in)
{
	if (in->herestr != NULL)
	{
		free(in->herestr);
		in->herestr = NULL;
	}
	if (in->fullheredoc != NULL)
	{
		free(in->fullheredoc);
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
		free(tok->token);
		tok->token = NULL;
		tok->prev = NULL;
		tok->next = NULL;
		free(tok);
		tok = tmp;
	}
	free(tok->token);
	tok->token = NULL;
	tok->prev = NULL;
	tok->next = NULL;
	free(tok);
}

void			free_all_check_token(t_tok *in, t_tokench *tok)
{
	free(in->dquote_d);
	free_heredoc(in);
	free_tok(tok);
}
