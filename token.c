/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bjuarez <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 08:40:32 by bjuarez      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 10:55:28 by bjuarez     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

int		verif_inter(char *str)
{
	if (ft_strncmp(str, "&&", 2) == 0)
		return (1);
	if (ft_strncmp(str, "||", 2) == 0)
		return (2);
	if (ft_strncmp(str + 1, "|", 1) == 0)
		return (3);
	if (ft_strncmp(str + 1, ">", 1) == 0)
		return (4);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (5);
	if (ft_strncmp(str + 1, "<", 1) == 0)
		return (6);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (7);
	if (ft_strncmp(str + 1, ";", 1) == 0)
		return (8);
	return (0);
}

int		find_last_inter(char *input)
{
	int i;
	int check;

	i = 0;
	check = 0;
	while (input[i])
		i++;
	while (ft_isprint(input[i]) != 1)
		i--;
	i--;
	if ((check = verif_inter(&input[i])) != 0)
		return (check);
	return (0);
}

int		find_err_quote(char *input, char c, char d)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (input[i])
	{
		if (input[i] == c && check == 0)
			check = 1;
		else if (input[i] == d && check == 1)
			check = 0;
		i++;
	}
	return (check);
}

char	*print_inter(char *inter, char *str, char *str2, int mode)
{
	char *ch;
	int i;

	i = 0;
	ch = ft_strnew(1);
	if (mode == 1)
	{
		while (inter[i] && inter[i] != '>')
			i++;
		if (inter[0] != '\0')
			ch = ft_strnjoinnf(ft_itoa(i), "|0|1", "0|0|0");
		else
			ch = ft_strnjoinnf(ch, "0|0|1", "0|0|1");
		if (inter[0] != '\0')
			inter = ft_strnjoinnf(inter, str, ch);
		else
			inter = ft_strnjoinnf(inter, str2, ch);
	}
	else
	{
		while (inter[i])
		{
			if (inter[i] == 'd' && inter[i + 1] == 'q')
				break ;
			if (inter[i] == 'p')
				break ;
			ft_printf("%c",inter[i]);
			i++;
		}
		if (inter[0] != '\0')
			ch = ft_strnjoinnf(ft_itoa(i - 1), "|0|1", "0|0|0");
		else
			ch = ft_strnjoinnf(ch, "0|0|1", "0|0|1");
		if (inter[0] == '\0')
			inter = ft_strnjoinnf(inter, str2, ch);
		else
			inter = ft_strnjoinnf(inter, str, ch);
	}
	return (inter);
}

void	check_enter(t_pos *pos)
{
	int check_inter;
	char *inter;

	inter = ft_strnew(1);
	check_inter = 0;
	if (find_err_quote(pos->ans, '"', '"') == 1)
	{
		inter = print_inter(inter, " dquote> ", "dquote> ", 1);
		ft_printf("\n%s", inter);
		input_is_printable_char(pos, "\n");
		pos->act_co++;
	}
	else if (find_err_quote(pos->ans, '{', '}') == 1)
	{
		inter = print_inter(inter, " cursh> ", "cursh> ", 1);
		ft_printf("\n%s", inter);
//					fill_str("\n", &pos);
//					pos.total++;
//					pos.actual++;
	}
	else if ((check_inter = find_last_inter(pos->ans)) != 0)
	{
		if (check_inter == 1)
		{
			inter = print_inter(inter, " cmdand> ", "cmdand> ", 2);
			ft_printf("\n%s", inter);
		}
		else if (check_inter == 2)
		{
			inter = print_inter(inter, " cmdor> ", "cmdor> ", 2);
			ft_printf("\n%s", inter);
		}
		else if (check_inter == 3)
		{
			inter = print_inter(inter, " pipe> ", "pipe> ", 1);
			ft_printf("\n%s", inter);
		}
		else if (check_inter > 3)
		{
			ft_printf("minishell: paerse error near '\n'\n");
			exit(0);
		}
	}
	else
	{
		tputs(tgetstr("ei", NULL), 1, ft_putchar);
		ft_printf("\nreponse -> |%s|\n", pos->ans);
		//	free(buf);
		exit (0);
	}
}
