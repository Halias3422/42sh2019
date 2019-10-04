 /* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/02 16:15:56 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/10 17:36:54 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/check_error.h"
#include "../../includes/lexeur.h"

int		print_error(int token)
{
	ft_printf_err("42sh: syntax {B.T.red.} error{eoc}");
	ft_printf_err(" near unexpected token `%s`\n", g_fill_token[token].name);
	return (-1);
}

int		first_check(char *str, int i, int token)
{
	int		j;

	j = 0;
	jump_space(str, &j);
	if (j == i)
		return (print_error(token));
	return (0);
}

int		second_check(char *str, int i, int token)
{
	i += g_fill_token[token].size;
	jump_space(str, &i);
	if (!str[i])
		return (print_error(token));
	return (0);
}

int		check_double_token(char *str, int i, int token)
{
	int		token2;

	i += g_fill_token[token].size;
	jump_space(str, &i);
	token2 = find_token(str, i);
	if (token2 != -1)
		return (print_error(token2));
	return (0);
}

void	error_heredoc_go_next(char *str, int *i)
{
	char	*tag;
	char	*tmp;
	int		s;

	tag = get_tag(str, i);
	(*i) += g_fill_token[7].size;
	while (str[*i])
	{
		jump_space(str, i);
		s = *i;
		while (str[*i] && ((str[*i] < 9 || str[*i] > 13) && str[*i] != ' '))
			(*i)++;
		tmp = ft_strsub(str, s, *i - s);
		if (!ft_strcmp(tmp, tag))
		{
			ft_strdel(&tmp);
			return ;
		}
		(*i)++;
	}
	if (tmp)
		ft_strdel(&tmp);
}

int		check_is_end(char *str, int i)
{
	i += g_fill_token[7].size;
	jump_space(str, &i);
	if (!str[i])
		return (0);
	return (1);
}

int		check_error(char *str)
{
	int		i;
	int		token;

	i = 0;
	if (ft_strcmp(str, "") == 0)
		return (-1);
	while (str[i])
	{
		jump_space(str, &i);
		if (i == 0 || str[i - 1] != '\\')
		{
			token = find_token(str, i);
			if (token == 7 && check_is_end(str, i))
			{
				error_heredoc_go_next(str, &i);
				token = find_token(str, i);
			}
			if (token == 4 || token == 0 || token == 1 || token == 10 || token == 2 || token == 3)
				if (first_check(str, i, token))
					return (-1);
			if (token == 9 || token == 6 || token == 8 || token == 5 || token == 4 || token == 7)
				if (second_check(str, i, token))
					return (-1);
			if (token != -1)
				if (check_double_token(str, i, token))
					return (-1);
			if (token != -1)
				i += g_fill_token[token].size;
			else if (str[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (0);
}
