/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   quote.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/28 16:54:35 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/07 10:32:02 by mdelarbr    ###    #+. /#+    ###.fr     */
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

char	*fill_first_replace(int *i, char *str, char c, int *s)
{
	char	*res;

	if (str[*i] != c)
	{
		while (str[*i] != c || (*i == 0 || str[*i - 1] == '\\'))
			(*i)++;
		res = ft_strsub(str, 0, *i);
	}
	else
		res = ft_strdup("");
	(*i)++;
	(*s) = (*i);
	while (str[*i])
	{
		if (str[*i] == c && (*i == 0 || str[*i - 1] != '\\'))
			break ;
		(*i)++;
	}
	return (res);
}

char	*replace(char *str, char c)
{
	char	*ar[4];
	int		s;
	int		i;

	i = 0;
	ar[1] = fill_first_replace(&i, str, c, &s);
	ar[3] = ft_strsub(str, s, i - s);
	ar[0] = ft_strjoin(ar[1], ar[3]);
	i++;
	s = i;
	i = ft_strlen(str);
	if (i >= s)
		ar[2] = ft_strsub(str, s, i - s);
	else
		ar[2] = ft_strdup("");
	ft_strjoin_free(&ar[0], ar[2]);
	ft_strdel(&str);
	ft_strdel(&ar[1]);
	ft_strdel(&ar[2]);
	ft_strdel(&ar[3]);
	return (ar[0]);
}

void	need_replace_quote(char ***array, int i, int *j)
{
	char	c;
	int		tmp;

	tmp = *j;
	c = (*array)[i][*j];
	(*array)[i] = replace((*array)[i], c);
	if (!(*array) && !ft_strcmp((*array)[i], ""))
		return ;
	if (*j > ft_strlen((*array)[i]))
		(*j) = tmp;
}


int		check_red(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (find_token(str, i) != -1)
			return (0);
		i++;
	}
	return (1);
}

void	browse_ar(char ***array, int i, int j)
{
	while ((*array)[i][j])
	{
		if (((*array)[i][j] == '\'' && (j == 0 ||
		(*array)[i][j - 1] != '\\')) || ((*array)[i][j] == '"'
		&& (j == 0 || (*array)[i][j - 1] != '\\')))
		{
			need_replace_quote(array, i, &j);
		}
		else
		{
			if (j < ft_strlen((*array)[i]))
				j++;
			else
				j = ft_strlen((*array)[i]);
		}
		if (!ft_strcmp((*array)[i], "") && j > ft_strlen((*array)[i]))
			break ;
	}
}

void	remoove_quote(char ***array)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while ((*array)[i])
	{
		browse_ar(array, i, j);
		j = 0;
		i++;
	}
}
