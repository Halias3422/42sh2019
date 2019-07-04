/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/09 10:52:26 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/04 16:23:54 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

int			cnt_size(char *str)
{
	int		nb;
	int		i;
	int		ret;

	i = 0;
	nb = 0;
	while (str[i])
	{
		while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
			i++;
		if (str[i] && str[i] == '"')
		{
			i++;
			nb++;
			while (str[i] && str[i] != '"')
				i++;
			i++;
		}
		if (str[i] && str[i] == '\'')
		{
			i++;
			nb++;
			while (str[i] && str[i] != '\'')
				i++;
			i++;
		}
		else if (str[i] && ((str[i] < 9 || str[i] > 13) && str[i] != ' '))
		{
			nb++;
			while (str[i] && ((str[i] < 9 || str[i] > 13) && str[i] != ' '
			&& str[i] != '"' && str[i] != '\'' && find_token(str, i) == -1))
				i++;
		}
		if (str[i] && (ret = find_token(str, i)) != -1)
		{
			i += g_fill_token[ret].size;
			nb++;
		}
	}
	return (nb);
}

//faire un sorte que les fd restes collé aux redirections comme 5> ect.
char		**split_space(char *str)
{
	int		i;
	int		k;
	int		ret;
	char	**res;
	int		start;

	i = 0;
	k = 0;
	res = malloc(sizeof(char *) * (cnt_size(str) + 1));
	while (str[i])
	{
		while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
			i++;
		if (str[i] && ((str[i] < 9 || str[i] > 13) && str[i] != ' '))
		{
			start = i;
			while (str[i] && ((str[i] < 9 || str[i] > 13) && str[i] != ' '
			&& find_token(str, i) == -1))
			{//faire en sorte que si c'est > >> < ou << alors on les laisse avec des int avant ou apres.
				if (str[i] == '\'')
				{
					i++;
					while (str[i] && str[i] != '\'')
						i++;
				}
				if (str[i] == '"')
				{
					i++;
					while (str[i] && str[i] != '"')
						i++;
				}
				i++;
			}
			res[k] = ft_strsub(str, start, i - start);
			k++;
		}
		if (str[i] && (ret = find_token(str, i)) != -1)
		{
			res[k] = ft_strsub(str, i, g_fill_token[ret].size);
			k++;
			i += g_fill_token[ret].size;
		}
	}
	res[k] = NULL;
	return (res);
}

void		list_add(t_replace **replace, char *array)
{
	t_replace	*next;
	t_replace	*start;

	start = (*replace);
	while ((*replace)->next)
		(*replace) = (*replace)->next;
	next = malloc(sizeof(t_replace));
	next->name = ft_strdup(array);
	next->next = NULL;
	(*replace)->next = next;
	(*replace) = start;
}

void		init_replace(t_replace **replace)
{
	(*replace) = malloc(sizeof(t_replace));
	(*replace)->name = ft_strdup("");
	(*replace)->next = NULL;
}

void		free_replace(t_replace *replace)
{
	t_replace	*tmp;

	while (replace)
	{
		ft_strdel(&replace->name);
		tmp = replace;
		replace = replace->next;
		free(&tmp);
	}
}
