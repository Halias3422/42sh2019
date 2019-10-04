/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexeur_struct.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/21 17:38:30 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/03 19:07:50 by mdelarbr    ###    #+. /#+    ###.fr     */
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

void		fill_lex_heredoc(t_lexeur ***array, int *j, char **buf, int *i)
{
	t_lexeur	*res;
	char		*tag;

	puts("FILL_LEX_HEREDOC");
	res = malloc(sizeof(t_lexeur));
	fill_struct_fd_in(res, get_fd_in(buf[*i]), 7,
	fill_redirection(buf, i));
	tag = ft_strdup(res->redirection);
	printf("TAG: _%s_\n", tag);
	(*array)[*j] = res;
	(*i)++;
	while (buf[*i])
	{
		(*j)++;
		fill_struct(res, buf[*i], -1, NULL);
		(*array)[*j] = res;
		printf("red -> word _%s_\ttoken : _%d_\n", res->word, res->token);
		printf("FIN ar[%d] -> word _%s_\ttoken : _%d_\n", *j, (*array)[*j]->word, (*array)[*j]->token);
		if (!ft_strcmp(buf[*i], tag))
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
	printf("DURING j %d\n", *j);
	ft_strdel(&tag);
}

t_lexeur	*fill_lex_redirection(char **buf,
int *i, enum e_token token)
{
	t_lexeur *res;

	res = malloc(sizeof(t_lexeur));
	if (token == 4 || token == 6 || token == 9 || token == 7)
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
