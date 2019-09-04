/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/02 16:15:56 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/04 17:24:17 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/check_error.h"
#include "../../includes/lexeur.h"

int		print_error(int token)
{
	ft_putstr("42sh: syntax ");
	ft_putstr(ERROR);
	ft_putstr("error");
	ft_putstr(WHITE);
	ft_putstr(" near unexpected token `");
	ft_putstr(g_fill_token[token].name);
	ft_putstr("'\n");
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

int		ft_check_is_null(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (!str[i])
		return (0);
	return (1);
}

int		check_error(char *str)
{
	int		i;
//	int		token;

	i = 0;
	if (ft_strcmp(str, "") == 0)
		return (-1);
	if (ft_check_is_null(str) == 0)
		return (-1);
	while (str[i])
	{
//		jump_space(str, &i);
//		token = find_token(str, i);
//		if (token == 0 || token == 2 || token == 3 || token == 1 || token == 8)
//			if (first_check(str, i, token))
//				return (-1);
//		if (token == 4 || token == 5 || token == 6 || token == 7)
//			if (second_check(str, i, token))
//				return (-1);
//		if (token != -1)
//			if (check_double_token(str, i, token))
//				return (-1);
//		if (str[i])
			i++;
	}
	return (0);
}
