/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/09 10:52:26 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/10 05:17:38 by mdelarbr    ###    #+. /#+    ###.fr     */
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
		printf("str[%d]: _%c_\n", i, str[i]);
		if (str[i] && (str[i] == '"' && (i == 0 || str[i - 1] != '\\')))
		{
			i++;
			nb++;
			while (str[i] && (str[i] != '"' && (i == 0 || str[i - 1] != '\\')))
				i++;
			if (str[i])
				i++;
		}
		if (str[i] && (str[i] == '\'' && (i == 0 || str[i - 1] != '\\')))
		{
			i++;
			nb++;
			while (str[i] && (str[i] != '\'' && (i == 0 || str[i - 1] != '\\')))
				i++;
			i++;
		}
		else if (str[i] && ((str[i] < 9 || str[i] > 13) && str[i] != ' '))
		{
			nb++;
			while (str[i] && ((str[i] < 9 || str[i] > 13) && str[i] != ' '
			&& find_token(str, i) == -1))
			{
				if (str[i] == '"' && (i == 0 || str[i - 1] != '\\'))
					break ;
				if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
					break ;
				i++;
			}
		}
		if (str[i] && (ret = find_token(str, i)) != -1)
		{
			nb++;
			i += g_fill_token[ret].size;
		}
	}
	printf("nb: %d\n", nb);
	return (nb);
}

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
			if (str[i] && ((str[i] >= '0' && str[i] <= '9') || (find_token(str, i) >= 4 && find_token(str, i) <= 7)))
			{
				if ((ret = find_token(str, i)) != -1)
				{
					i += g_fill_token[ret].size;
					while (str[i] && (str[i] >= '0' && str[i] <= '9'))
						i++;
				}
				else
				{
					while (str[i] && (str[i] >= '0' && str[i] <= '9'))
						i++;
					if (str[i])
						ret = find_token(str, i);
					if (str[i] && (ret >= 4 && ret <= 7))
						i += g_fill_token[ret].size;
				}
			}
			else
			{
				while (str[i] && ((str[i] < 9 || str[i] > 13) && str[i] != ' '
				&& (find_token(str, i) == -1) && (str[i] < '0' || str[i] > '9')))
				{
					if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
					{
						i++;
						while (str[i] && (str[i] != '\'' && (i == 0 || str[i - 1] != '\\')))
							i++;
					}
					if (str[i] == '"' && (i == 0 || str[i - 1] != '\\'))
					{
						i++;
						while (str[i] && str[i] != '"' && (i == 0 || str[i - 1] != '\\'))
							i++;
					}
					if (str[i])
						i++;
				}
			}
			res[k] = ft_strsub(str, start, i - start);
		}
		if (str[i] && (ret = find_token(str, i)) != -1)
		{
			res[k] = ft_strsub(str, i, g_fill_token[ret].size);
			i += g_fill_token[ret].size;
		}
		k++;
		if (str[i])
			i++;
	}
	printf("k %d\n", k);
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
