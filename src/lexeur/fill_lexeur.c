/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_lexeur.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/27 11:29:05 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 13:28:37 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void		jump_space(char *buf, int *i)
{
	while (buf[*i] && ((buf[*i] >= 9 && buf[*i] <= 13) || buf[*i] == ' '))
		(*i)++;
}

void		fill_struct_filein(t_lexeur *res, char *word, enum e_token token,
char *red)
{
	if (word)
		res->word = ft_strdup(word);
	else
		res->word = NULL;
	res->token = token;
	if (red)
		res->file_in = ft_strdup(red);
	else
		res->file_in = NULL;
	res->fd = -1;
	ft_strdel(&word);
	ft_strdel(&red);
}

void		fill_struct_fileout(t_lexeur *res, char *word, enum e_token token,
char *red)
{
	if (word)
		res->word = ft_strdup(word);
	else
		res->word = NULL;
	res->token = token;
	if (red)
		res->file_out = ft_strdup(red);
	else
		res->file_out = NULL;
	res->fd = -1;
	ft_strdel(&word);
	ft_strdel(&red);
}

t_lexeur	*fill_lex_redirection(char **buf, t_lexeur *res, int *i, int token)
{
	if (token == 4 || token == 5)
	{
		fill_struct_fileout(res, NULL, token, ft_strdup(buf[*i + 1]));
		(*i)++;
	}
	if (token == 7)
	{
		fill_struct_filein(res, NULL, token, ft_strdup(buf[*i + 1]));
		(*i)++;
	}
	if (token != 7 && token != 4 && token != 5)
		fill_struct_fileout(res, buf[*i], token, NULL);
	return (res);
}

t_lexeur	*fill_lex_while(char **buf, int *i, int token)
{
	t_lexeur	*res;

	res = malloc(sizeof(t_lexeur));
	res->file_out = NULL;
	res->file_in = NULL;
	return (fill_lex_redirection(buf, res, i, token));
//	if (buf[*i] && token != -1)
//	else
//	{
//		fill_struct_fileout(res, buf[*i], -1, NULL);
//		return (res);
//	}
	return (NULL);
}

t_lexeur	**fill_lex(char **buf, t_lexeur **array)
{
	int			i;
	int			j;
//	t_lexeur	*tmp;

	i = 0;
	j = 0;
	while (buf[i])
		i++;
	array = malloc(sizeof(t_lexeur *) * (i + 1));
	i = 0;
	while (buf[i])
	{
//		if ((tmp = find_fd(buf[i], 0)) != NULL)
//			array[j] = tmp;
		array[j] = fill_lex_while(buf, &i, find_token(buf[i], 0));
		i++;
		j++;
	}
	array[j] = NULL;
//	check_redirection(&array);
	return (array);
}
