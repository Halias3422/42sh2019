/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_lexeur.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/27 11:29:05 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/08 16:25:00 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void		jump_space(char *buf, int *i)
{
	while (buf[*i] && ((buf[*i] >= 9 && buf[*i] <= 13) || buf[*i] == ' '))
		(*i)++;
}

char		*get_fd_in(char	*str)
{
	char	*fd_in;
	int		i;

	i = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (i != 0)
		fd_in = ft_strsub(str, 0, i);
	else
		fd_in = NULL;
	return (fd_in);
}

void		fill_struct_fd_in(t_lexeur *res, char *fd_in, enum e_token token,
char *red)
{
	res->word = NULL;
	res->token = token;
	if (red)
		res->redirection = ft_strdup(red);
	else
		res->redirection = NULL;
	res->fd_in = ft_strdup(fd_in);
	res->fd_out = NULL;
	ft_strdel(&red);
	ft_strdel(&fd_in);
}

void		fill_struct_fd_out(t_lexeur *res, char *fd_in, enum e_token token,
char *fd_out)
{
	res->word = NULL;
	res->token = token;
	res->redirection = NULL;
	if (fd_in)
		res->fd_in = ft_strdup(fd_in);
	else
		res->fd_in = NULL;
	if (fd_out)
		res->fd_out = ft_strdup(fd_out);
	else
		res->fd_out = NULL;
	ft_strdel(&fd_in);
	ft_strdel(&fd_out);
}

void		fill_struct(t_lexeur *res, char *word, enum e_token token,
char *red)
{
	res->word = ft_strdup(word);
	res->token = token;
	res->redirection = NULL;
	res->fd_in = NULL;
	res->fd_out = NULL;
	ft_strdel(&word);
	ft_strdel(&red);
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
		return (res);
	}
	if (token == 5 || token == 8)
	{
		fill_struct_fd_out(res, get_fd_in(buf[*i]), token,
		fill_redirection(buf, i));
		return (res);
	}
	return (NULL);
}

t_lexeur	*fill_lex_while(char *buf, int *i, int token)
{
	t_lexeur	*res;

	res = malloc(sizeof(t_lexeur));
	if (token == -1)
		fill_struct(res, buf, token, NULL);
	else
		fill_struct(res, NULL, token, NULL);
	(*i)++;
	return (res);
}

int			check_token_for_redirection(char *str)
{
	int		i;
	int		token;

	token = 0;
	i = 0;
	while (str[i])
	{
		token = find_token(str, i);
		if (token == 4 || token == 5 || token == 6 || token == 8 || token == 9)
			return (token);
		i++;
	}
	return (-1);
}

t_lexeur	**fill_lex(char **buf, t_lexeur **array)
{
	int			i;
	int			j;
	int			k;
	int			t = 0;
	int			token;

	i = 0;
	j = 0;
	while (buf[i])
	{
		printf("buf[%d] : _%s_\n", i, buf[i]);
		i++;
	}
	array = malloc(sizeof(t_lexeur *) * (i + 1));
	i = 0;
	while (buf[i])
	{
		k = 0;
		if (ft_strcmp(buf[i], "") == 0)
			i++;
		if (buf[i])
		{
			token = check_token_for_redirection(buf[i]);
			printf("token: %d\n", token);
			if (token != -1)
				array[j] = fill_lex_redirection(buf, &i, token);
			else
				array[j] = fill_lex_while(buf[i], &i, find_token(buf[i], k));
			j++;
		}
	}
	array[j] = NULL;
	while (array[t])
	{
		printf("array[%d]:\tword -> _%s_\ttoken ->%d\tred -> _%s_\tfd_in _%s_ fd_out _%s_\n", t, array[t]->word, array[t]->token, array[t]->redirection, array[t]->fd_in, array[t]->fd_out);
		t++;
	}
//	check_redirection(&array);
	return (array);
}
