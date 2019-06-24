/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fc.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/08 11:18:28 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/24 13:21:56 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

void		print_fc_usage(void)
{
	write(2, "fc: usage: fc [-e ename] [-nlr] [first] [last]", 46);
	write(2, " or fc -s [pat=rep] [cmd]\n", 26);
}

static void		init_fc_struct(t_fc *fc)
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

static void		execute_fc_according_to_flags(t_fc *fc)
{
	t_hist	*hist;

	hist = stock(NULL, 8);
	while (hist && hist->next)
		hist = hist->next;
	if (fc->int_first == 0)
		fc->int_first = hist->cmd_no - 1;
	if (fc->int_last == 0)
		fc->int_last = hist->cmd_no - 1;
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
	if (fc.error == 0)
	{
		get_str_args_of_fc(&fc, p, i, 0);
		execute_fc_according_to_flags(&fc);
	}
	return (0);
}
