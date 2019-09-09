 /* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/02 16:15:56 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/04 10:41:43 by mjalenqu    ###    #+. /#+    ###.fr     */
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

	printf("-------------------------------first check-------------------------------\n");
	j = 0;
	jump_space(str, &j);
	printf("i = %d et j = %d\n", i, j);
	if (j == i)
		return (print_error(token));
	return (0);
}

int		second_check(char *str, int i, int token)
{
	printf("-------------------------------second check-------------------------------\n");
	i += g_fill_token[token].size;
	jump_space(str, &i);
	printf("str[%d]=%c\n", i, str[i]);
	if (!str[i])
		return (print_error(token));
	return (0);
}

int		check_double_token(char *str, int i, int token)
{
	int		token2;

	printf("-------------------------------check double token-------------------------------\n");
	i += g_fill_token[token].size;
	jump_space(str, &i);
	token2 = find_token(str, i);
	printf("token2 = %d\n", token2);
	if (token2 != -1)
		return (print_error(token2));
	return (0);
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
		token = find_token(str, i);
		if (token == 2 || token == 0)
			if (first_check(str, i, token))
				return (-1);
		if (token == 9 || token == 8 || token == 4 || token == 5)
			if (second_check(str, i, token))
				return (-1);
		printf("i = %d|\tlen = %d|\tstr[i] = %c|\ttoken = %d\n", i, ft_strlen(str), str[i], token);
		// // if (token == 10 || token == 2 || token == 3 || token == 1 || token == 8 || token == 9)
		// if (token != -1 && token != 9 && token != 3)
		// 	if (first_check(str, i, token))
		// 		return (-1);
		// // if (token == 4 || token == 5 || token == 6 || token == 7)
		// if (token != -1)
		// 	if (second_check(str, i, token))
		// 		return (-1);
		if (token != -1)
			if (check_double_token(str, i, token))
				return (-1);
		if (token != -1)
				i += g_fill_token[token].size;
		else
			i++;
	}
	return (0);
}
