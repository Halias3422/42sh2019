/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fc.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/08 11:18:28 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/08 17:12:01 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

#define TERM "42sh"

int		find_flags_order(t_fc *fc, char let_a, char let_b, int usage)
{
	int	i;

	i = 0;
	if (usage == 0)
	{
		(void)let_b;
		while (fc->flags[i] && fc->flags[i] != let_a)
			i++;
		return (i);
	}
	return (0);
}

void		check_flags_errors(t_fc *fc, t_process *p, int i, int j)
{
	if (j < ft_strlen(p->cmd[i]) && ft_strchr(fc->flags, 'e') == NULL)
	{
		ft_printf_err("%s: fc: -%c: invalid option\n", TERM, p->cmd[i][j]);
		write(2, "fc: usage: fc [-e ename] [-nlr] [first] [last]", 46);
		write(2, " or fc -s [pat=rep] [cmd]", 25);
		fc->error = 1;
	}
	if ((j < ft_strlen(p->cmd[i]) || !p->cmd[i + 1] ||
	(p->cmd[i + 1] && p->cmd[++i][0] == '-')) &&
			ft_strchr(fc->flags, 'e') != NULL)
	{
		if (!p->cmd[i + 1] &&
			find_flags_order(fc, 'e', '\0', 0) == ft_strlen(fc->flags) - 1)
		{
			ft_printf_err("%s: fc: -e: option requires an argument\n", TERM);
			write(2, "fc: usage: fc [-e ename] [-nlr] [first] [last]", 46);
			write(2, " or fc -s [pat=rep] [cmd]", 25);
		}
		else
		{
			while (j > 0 && p->cmd[i][j - 1] != 'e')
				j--;
			ft_printf_err("%s: fc: %s: command not found\n", TERM, p->cmd[i] + j);
		}
		fc->error = 1;
	}
}

int			determ_fc_flags(t_fc *fc, t_process *p, int k, int i)
{
	int		j;

	while (p->cmd[i] && ft_strlen(p->cmd[i]) > 1 && p->cmd[i][0] == '-' &&
			p->cmd[i][1] != '-' && fc->error == 0)
	{
		j = 1;
		while (p->cmd[i][j] && ft_strchr(fc->flags_model, p->cmd[i][j]) != NULL)
		{
			if (ft_strchr(fc->flags, p->cmd[i][j]) == NULL)
				fc->flags[k++] = p->cmd[i][j];
			j++;
		}
		check_flags_errors(fc, p, i, j);
		i++;
	}
	fc->flags[k] = '\0';
	return (i);
}

void		make_str_arg_into_int(t_fc *fc, t_hist *hist)
{
	if (fc->first_is_str == 1)
	{
		while (hist->prev)
		{
			hist = hist->prev;
			if (ft_strncmp(fc->str_first, hist->cmd,
						ft_strlen(fc->str_first)) == 0)
				fc->int_first = hist->cmd_no;
		}
	}
	while (hist->next->next)
		hist = hist->next;
	if (fc->last_is_str == 1)
	{
		while (hist->prev)
		{
			hist = hist->prev;
			if (ft_strncmp(fc->str_last, hist->cmd,
						ft_strlen(fc->str_last)) == 0)
				fc->int_last = hist->cmd_no;
		}
	}
	if ((fc->int_first == -1 || fc->int_last == -1) && fc->error++ == 0)
		ft_printf_err("%s: fc: history specification out of range\n", TERM);
}

void		get_int_arg(t_process *p, int *fill_int, int *is_str, int i)
{
	*fill_int = ft_atoi(p->cmd[i]);
	*is_str = 0;
}

void		get_str_arg(t_process *p, char **str, int *is_str, int i)
{
	*str = ft_strdup(p->cmd[i]);
	*is_str = 1;
}

void		get_str_args_of_fc(t_fc *fc, t_process *p, int i, int check)
{
	if ((ft_strchr(fc->flags, 'e') != NULL || ft_strchr(fc->flags, 's') != NULL)
	&& p->cmd[i] && (find_flags_order(fc, 'e', '\0', 0) == ft_strlen(fc->flags)
		- 1 || find_flags_order(fc, 's', '\0', 0) == ft_strlen(fc->flags) - 1))
		fc->ename = ft_strdup(p->cmd[i++]);
	while (p->cmd[i] && check < 2)
	{
		if (p->cmd[i][0] >= '0' && p->cmd[i][0] <= '9' && check == 0)
			get_int_arg(p, &fc->int_first, &fc->first_is_str, i);
		else if (p->cmd[i][0] >= '0' && p->cmd[i][0] <= '9' && check == 1)
			get_int_arg(p, &fc->int_last, &fc->last_is_str, i);
		else if (check == 0)
			get_str_arg(p, &fc->str_first, &fc->first_is_str, i);
		else if (check == 1)
			get_str_arg(p, &fc->str_last, &fc->last_is_str, i);
		i++;
		check++;
	}
	if (check == 0)
	{
		fc->first_not_precised = 1;
		fc->last_not_precised = 1;
	}
	if (check == 1)
		fc->last_not_precised = 1;
	if (fc->first_is_str == 1 || fc->last_is_str == 1)
		make_str_arg_into_int(fc, stock(NULL, 8));
}

void		init_fc_struct(t_fc *fc)
{
	fc->flags_model = ft_strdup("elnrs");
	fc->flags = ft_strnew(6);
	fc->ename = NULL;
	fc->str_first = ft_strnew(0);
	fc->str_last = ft_strnew(0);
	fc->int_first = -1;
	fc->int_last = -1;
	fc->first_is_str = -1;
	fc->last_is_str = -1;
	fc->first_not_precised = -1;
	fc->last_not_precised = -1;
	fc->error = 0;
}

void		print_l_flag(t_fc *fc, t_hist *hist)
{
	if (fc->int_first <= fc->int_last)
	{
		while (hist->prev && hist->cmd_no > fc->int_first - 1)
		hist = hist->prev;
		while (fc->int_first <= fc->int_last && hist->next->next)
		{
			if (ft_strchr(fc->flags, 'n') == NULL)
				ft_printf("%d", hist->cmd_no + 1);
			ft_printf("		%s\n", hist->cmd);
			fc->int_first += 1;
			hist = hist->next;
		}
	}
	else if (fc->int_first > fc->int_last)
	{
		ft_printf("je suis la johnny\n");
		while (hist->prev && hist->cmd_no > fc->int_last - 1)
			hist = hist->prev;
		while (fc->int_last <= fc->int_first && hist->next->next)
		{
			if (ft_strchr(fc->flags, 'n') == NULL)
			ft_printf("%d", hist->cmd_no + 1);
			ft_printf("		%s\n", hist->cmd);
			fc->int_last += 1;
			hist = hist->next;
		}
	}
}

void		prepare_l_flag(t_fc *fc, t_hist *hist)
{
	int		swap;

	if (fc->first_not_precised == 1 && fc->last_not_precised == 1)
	{
		fc->int_first = hist->cmd_no - 15;
		fc->int_last = hist->cmd_no;
	}
	if (fc->int_first < 0)
		fc->int_first = (hist->cmd_no + fc->int_first) - 1;
	else if (fc->int_last < 0)
		fc->int_last = (hist->cmd_no + fc->int_last) - 1;
	if (ft_strchr(fc->flags, 'r') != NULL)
	{
		swap = fc->int_first;
		fc->int_first = fc->int_last;
		fc->int_last = swap;
	}

	print_l_flag(fc, hist);
}

void		execute_fc_according_to_flags(t_fc *fc)
{
	t_hist	*hist;

	hist = stock(NULL, 8);
	if (fc->error == 1)
		return ;
	if (ft_strchr(fc->flags, 'l') != NULL)
		prepare_l_flag(fc, hist);
}

int			ft_fc(t_process *p, t_var **var)
{
	t_fc	fc;
	int		i;

	(void)var;
	init_fc_struct(&fc);
	i = determ_fc_flags(&fc, p, 0, 1);
	if  (fc.error == 0)
	{
		get_str_args_of_fc(&fc, p, i, 0);
		execute_fc_according_to_flags(&fc);
		ft_printf("fc.int_first = %d fc.int_last = %d\n", fc.int_first, fc.int_last);
		ft_printf("ename = {%s}\n", fc.ename);
	}
	return (0);
}
