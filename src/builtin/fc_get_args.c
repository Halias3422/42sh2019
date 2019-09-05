/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_fc_args.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/08 18:16:45 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/05 14:30:18 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static void		get_int_arg(t_process *p, int *fill_int, int *is_str, int i)
{
	*fill_int = ft_atoi(p->cmd[i]);
	*is_str = 0;
}

static void		get_str_arg(t_process *p, char **str, int *is_str, int i)
{
	*str = ft_strdup(p->cmd[i]);
	*is_str = 1;
}

void		make_str_last_into_int(t_fc *fc, t_hist *hist)
{
	while (hist && hist->next && hist->next->next)
		hist = hist->next;
	if (fc->last_is_str == 1)
	{
		while (hist->prev)
		{
			hist = hist->prev;
			if (ft_strncmp(fc->str_last, hist->cmd,
						ft_strlen(fc->str_last)) == 0)
			{
				fc->int_last = hist->cmd_no + 1;
				break ;
			}
		}
	}
}

void		make_str_arg_into_int(t_fc *fc, t_hist *hist)
{
	int			check;

	check = 0;
	if (fc->first_is_str == 1)
	{
		while (hist->prev)
		{
			hist = hist->prev;
			if (ft_strncmp(fc->str_first, hist->cmd,
						ft_strlen(fc->str_first)) == 0)
			{
				fc->int_first = hist->cmd_no + 1;
				break ;
			}
		}
	}
	make_str_last_into_int(fc, hist);
	if ((fc->int_first == -1 || fc->int_last == -1) && fc->error++ == 0)
	{
		remove_cmd_from_hist(hist);
		overwrite_history_file(hist);
		ft_printf_err("%s: fc: history specification out of range\n", TERM);
	}
}

static void		check_if_str_args_need_correction(t_fc *fc, int check)
{
	if (check == 0)
	{
		fc->first_not_precised = 1;
		fc->int_first = 0;
		fc->last_not_precised = 1;
		fc->int_last = 0;
	}
	if (check == 1)
	{
		fc->last_not_precised = 1;
		fc->int_last = 0;
	}
	if (fc->first_is_str == 1 || fc->last_is_str == 1)
		make_str_arg_into_int(fc, stock(NULL, 8));
}

void		get_str_args_of_fc(t_fc *fc, t_process *p, int i, int check)
{
	if ((ft_strchr(fc->flags, 'e') != NULL || ft_strchr(fc->flags, 's') != NULL)
	&& p->cmd[i] && (find_flags_order(fc, 'e', '\0', 0) == ft_strlen(fc->flags)
		- 1 || find_flags_order(fc, 's', '\0', 0) == ft_strlen(fc->flags) - 1))
		fc->ename = ft_strdup(p->cmd[i++]);

	while (p->cmd[i] && check < 2)
	{
		if (((p->cmd[i][0] >= '0' && p->cmd[i][0] <= '9') || (p->cmd[i][1]
		&& p->cmd[i][0] == '-' && p->cmd[i][1] >= '0' && p->cmd[i][1] <= '9'))
				&& check == 0)
			get_int_arg(p, &fc->int_first, &fc->first_is_str, i);
		else if (((p->cmd[i][0] >= '0' && p->cmd[i][0] <= '9') || (p->cmd[i][1]
		&& p->cmd[i][0] == '-' && p->cmd[i][1] >= '0' && p->cmd[i][1] <= '9'))
				&& check == 1)
			get_int_arg(p, &fc->int_last, &fc->last_is_str, i);
		else if (check == 0)
			get_str_arg(p, &fc->str_first, &fc->first_is_str, i);
		else if (check == 1)
			get_str_arg(p, &fc->str_last, &fc->last_is_str, i);
		i++;
		check++;
	}
	check_if_str_args_need_correction(fc, check);
}
