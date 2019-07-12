/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   quote.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/28 16:54:35 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/12 09:22:18 by mjalenqu    ###    #+. /#+    ###.fr     */
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
	if (str[i] != c)
	{
		while (str[i] != c || (i == 0 || str[i - 1] == '\\'))
			i++;
		ar[1] = ft_strsub(str, 0, i);
	}
	else
		ar[1] = ft_strdup("");
	i++;
	s = i;
	while (str[i])
	{
		if (str[i] == c && (i == 0 || str[i - 1] != '\\'))
			break ;
		i++;
	}
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

// TODO faire les \ devant les alias. ils ne se font pas
// gerer le bug des simples quotes qui passe 2 fois dans la boucle.  echo '\""\$USER\""'

void	remoove_quote(char ***array)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while ((*array)[i])
	{
		printf("array[%d]=%s\n", i, (*array)[i]);
		while ((*array)[i][j])
		{
			if (((*array)[i][j] == '\'' && (j == 0 || (*array)[i][j - 1] != '\\'))
			|| ((*array)[i][j] == '"' && (j == 0 || (*array)[i][j - 1] != '\\')))
				(*array)[i] = replace((*array)[i], (*array)[i][j]);
			if (j < ft_strlen((*array)[i]))
				j++;
			else
				j = ft_strlen((*array)[i]);
		}
		j = 0;
		i++;
	}
}
