/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_fd.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/05 13:21:55 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/05 13:49:47 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

t_lexeur	*fill_fd(int fd, int token)
{
	t_lexeur	*res;

	res = malloc(sizeof(t_lexeur));
	res->word = NULL;
	res->token = token;
	res->fd = fd;
	res->redirection = NULL;
	return (res);
}

int			check_fd(char *buf, int i)
{
	int		token;

	while (buf[i] && (buf[i] >= '0' && buf[i] <= '9'))
		i++;
	if (!buf[i])
		return (1);
	token = find_token(buf, i);
	if (token != 4 && token != 5 && token != 6 && token != 7)
		return (1);
	return (0);
}

t_lexeur	*find_fd(char *buf, int i)
{
	int			fd;
	char		*tmp;
	int			start;
	int			token;

	if (check_fd(buf, i))
		return (NULL);
	while (buf[i])
	{
		if (buf[i] && (buf[i] >= '0' && buf[i] <= '9'))
		{
			start = i;
			while (buf[i] && (buf[i] >= '0' && buf[i] <= '9'))
				i++;
			token = find_token(buf, i);
			tmp = ft_strsub(buf, start, i - start);
			printf("tmp: _%s_\n", tmp);
			fd = ft_atoi(tmp);
			return (fill_fd(fd, token));
		}
		i++;
	}
	return (NULL);
}
