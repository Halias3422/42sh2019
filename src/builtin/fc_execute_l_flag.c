/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute_fc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/08 18:30:58 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/08 19:13:36 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static void		print_l_flag(t_fc *fc, t_hist *hist)
{
	if (fc->int_first <= fc->int_last)
	{
		while (fc->int_first <= fc->int_last && hist->next->next)
		{
			if (ft_strchr(fc->flags, 'n') == NULL)
				ft_printf("%d", hist->cmd_no + 1);
			ft_printf("		%s\n", hist->cmd);
			fc->int_first += 1;
			hist = hist->next;
			if (fc->int_first == fc->int_last && (fc->first_not_precised == 2 ||
						fc->last_not_precised == 2 < 0))
				break ;
		}
	}
	else if (fc->int_first > fc->int_last)
	{
		while (fc->int_first >= fc->int_last && hist)
		{
			if (ft_strchr(fc->flags, 'n') == NULL)
				ft_printf("%d", hist->cmd_no + 1);
			ft_printf("		%s\n", hist->cmd);
			fc->int_first -= 1;
			hist = hist->prev;
			if (fc->int_first == fc->int_last - 1 && (fc->int_first < 0 ||
						fc->int_last < 0))
				break ;
		}
	}
}

static void		correct_int_first_and_int_last(t_fc *fc, t_hist *hist)
{
	if (fc->first_not_precised == 1 && fc->last_not_precised == 1)
	{
		fc->int_first = hist->cmd_no - 15;
		fc->int_last = hist->cmd_no;
	}
	else if (fc->first_not_precised == 1)
		fc->int_first = hist->cmd_no;
	else if (fc->last_not_precised == 1)
		fc->int_last = hist->cmd_no;
	if (fc->int_first < 0)
	{
		fc->int_first = (hist->cmd_no + fc->int_first);
		fc->first_not_precised = 2;
	}
	else if (fc->int_last < 0)
	{
		fc->int_last = (hist->cmd_no + fc->int_last) - 1;
		fc->last_not_precised = 2;
	}
}

void		prepare_l_flag(t_fc *fc, t_hist *hist)
{
	int		swap;

	correct_int_first_and_int_last(fc, hist);
	if (ft_strchr(fc->flags, 'r') != NULL)
	{
		swap = fc->int_first;
		fc->int_first = fc->int_last;
		fc->int_last = swap;
	}
	while (hist->prev && hist->cmd_no > fc->int_first - 1)
		hist = hist->prev;
	print_l_flag(fc, hist);
}
