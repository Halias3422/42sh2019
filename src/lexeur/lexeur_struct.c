/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexeur_struct.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/21 17:38:30 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/21 17:44:37 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void		fill_struct(t_lexeur *res, char *word, enum e_token token,
char *red)
{
	if (word)
		word = ft_del_simple_quote(word);
	res->word = ft_strdup(word);
	res->token = token;
	res->redirection = NULL;
	res->fd_in = NULL;
	res->fd_out = NULL;
	ft_strdel(&word);
	ft_strdel(&red);
}

t_lexeur	*fill_lex_while(char *buf, int *i, int token)
{
	t_lexeur	*res;

	if (buf[0] == '\\' && find_token(buf, 1) != -1)
		buf = change_buf(buf);
	res = malloc(sizeof(t_lexeur));
	if (token == -1)
		fill_struct(res, buf, token, NULL);
	else
		fill_struct(res, NULL, token, NULL);
	(*i)++;
	return (res);
}

t_lexeur	*fill_lex_redirection(char **buf,
int *i, enum e_token token)
{
	t_lexeur *res;

	res = malloc(sizeof(t_lexeur));
	if (token == 4 || token == 6 || token == 9)
	{
		fill_struct_fd_in(res, get_fd_in(buf[*i]), token,
		fill_redirection(buf, i));
		if (res->redirection)
			(*i)++;
		return (res);
	}
	if (token == 5 || token == 8)
	{
		fill_struct_fd_out(res, get_fd_in(buf[*i]), token,
		get_fd_out(buf[*i]));
		(*i)++;
		return (res);
	}
	return (NULL);
}
