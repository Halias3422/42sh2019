/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   quote.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/28 16:54:35 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/28 17:38:53 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

/*
** ar[0] = res.
** ar[1] = first.
** ar[2] = end.
** ar[3] = tmp.
*/

char	*replace(char *str, char c)
{
	char	*ar[4];
	int		s;
	int		i;

	i = 0;
	printf("str: %s\n", str);
	while (str[i] != c)
		i++;
	ar[1] = ft_strsub(str, 0, i);
	printf("f: _%s_\n", ar[1]);
	i++;
	s = i;
	while (str[i] != c)
		i++;
	printf("la le i: %d\ts: %d\n", i, s);
	ar[3] = ft_strsub(str, s, i - s);
	printf("tmp: _%s_\n", ar[3]);
	ar[0] = ft_strjoin(ar[1], ar[3]);
	i++;
	s = i;
	while (str[i])
		i++;
	ar[2] = ft_strsub(str, s, i - s);
	printf("end: _%s_\n", ar[2]);
	ft_strjoin_free(&ar[0], ar[2]);
	ft_strdel(&str);
	ft_strdel(&ar[1]);
	ft_strdel(&ar[2]);
	ft_strdel(&ar[3]);
	printf("res: _%s_\n", ar[0]);
	return (ar[0]);
}

void    remoove_quote(char ***array)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while ((*array)[i])
	{
		while ((*array)[i][j])
		{
			if ((*array)[i][j] == '\'' || (*array)[i][j] == '"')
				(*array)[i] = replace((*array)[i], (*array)[i][j]);
			j++;
		}
		j = 0;
		i++;
	}
}