/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 10:51:14 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/19 18:09:41 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_word_split(char const *s, char c)
{
	int			i;
	int			cpt;
	int			verif;

	i = 0;
	cpt = 0;
	verif = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] && s[i] != c && verif == 0)
		{
			verif++;
			cpt++;
		}
		if (s[i] && s[i] == c)
			verif = 0;
		i++;
	}
	return (cpt);
}

static int		ft_let(int i, const char *s, char c)
{
	int			nb_let;

	nb_let = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		nb_let++;
	}
	return (nb_let);
}

static char		**ft_split2(char const *s, char c, char **tab)
{
	int			i;
	int			j;
	int			k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			j = 0;
			if (!(tab[k] = (char*)malloc(sizeof(char) * ft_let(i, s, c) + 1)))
				return (NULL);
			while (s[i] && s[i] != c)
				tab[k][j++] = s[i++];
			tab[k++][j] = '\0';
		}
	}
	tab[k] = NULL;
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**tab;
	int			nb_word;

	if (!s)
		return (NULL);
	nb_word = ft_count_word_split(s, c);
	if (!(tab = (char**)malloc(sizeof(char*) * (nb_word + 1))))
		return (NULL);
	return (ft_split2(s, c, tab));
}
