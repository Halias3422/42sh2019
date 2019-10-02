/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirection.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 17:01:39 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/21 14:51:27 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

char			*fill_redirection(char **buf, int *i)
{
	char	*res;

	if (buf[*i + 1])
	{
		(*i)++;
		res = ft_strdup(buf[*i]);
		return (res);
	}
	return (NULL);
}
