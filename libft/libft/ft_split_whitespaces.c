/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_split_whitespaces.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/19 20:46:43 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/28 13:01:23 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cpt_mot(char *str)
{
	int		i;
	int		i_bool;
	int		nb_mot;

	i = 0;
	i_bool = 0;
	nb_mot = 0;
	while (str[i])
	{
		if (str[i] != '\n' && str[i] != '\t' && str[i] != ' ' && str[i])
		{
			i++;
			i_bool = 0;
		}
		if ((str[i] == '\n' || str[i] == '\t' || str[i] == ' ')
				&& str[i] && i_bool == 0)
		{
			i_bool++;
			nb_mot++;
		}
		i++;
	}
	return (nb_mot);
}

static int	ft_cpt_lettre(char *str, int i)
{
	int		nb_lettre;

	nb_lettre = 0;
	while (str[i] != '\n' && str[i] != '\t' && str[i] != ' ' && str[i])
	{
		nb_lettre++;
		i++;
	}
	return (nb_lettre);
}

static char	**remplissage(char **tab, char *str, int i, int j)
{
	int		k;

	k = 0;
	while (str[i])
	{
		while ((str[i] == '\n' || str[i] == '\t' || str[i] == ' ') && str[i])
			i++;
		if (str[i])
		{
			k = 0;
			tab[j] = malloc(sizeof(char) * ft_cpt_lettre(str, i) + 1);
			while (str[i] != '\n' && str[i] != '\t' && str[i] != ' ' && str[i])
				tab[j][k++] = str[i++];
			tab[j][k] = '\0';
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

char		**ft_split_whitespaces(char *str)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	if (!(tab = malloc(sizeof(char) * ft_cpt_mot(str) + 1)))
		return (NULL);
	return (tab = remplissage(tab, str, i, j));
}
