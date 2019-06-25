/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_execute_s_flag.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/24 13:41:03 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/25 08:56:03 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

void		prepare_s_flag(t_fc *fc, t_hist *hist)
{
	int		check;

	check = 0;
	ft_printf("ename = %s first = %d last = %d\n", fc->ename, fc->int_first, fc->int_last);
	if (fc->ename == NULL)
	{
		//executer derniere commande historique
	}
	else
	{
		if ((fc->ename[0] >= '0' && fc->ename[0] <= '9') || (fc->ename[0] == '-'
		&& fc->ename[1] && fc->ename[1] >= '0' && fc->ename[1] <= '9'))
		{
			fc->int_first = ft_atoi(fc->ename);
			if (fc->int_first <= 0)
			{
				fc->int_first = hist->cmd_no + fc->int_first;
				if (fc->int_first < 0 && fc->error++ == 0)
					ft_printf_err("42sh: fc: no command found\n");
			}
			if (fc->error > 0)
				return ;
			while (hist && hist->prev && fc->int_first < (hist->cmd_no + 1))
				hist = hist->prev;
			if (fc->int_first == hist->cmd_no + 1)
			{
				fc->ename = ft_secure_free(fc->ename);
				fc->ename = ft_strdup(hist->cmd);
			}
			else if (fc->error++ == 0)
				ft_printf_err("42sh: fc: no command found\n");
		}
		else
		{
			while (hist->prev)
			{
				hist = hist->prev;
				if (ft_strncmp(fc->ename, hist->cmd, ft_strlen(fc->ename)) == 0)
				{
					fc->ename = ft_secure_free(fc->ename);
					fc->ename = ft_strdup(hist->cmd);
					check += 1;
					break ;
				}
			}
			if (check == 0 && fc->error++ == 0)
				ft_printf_err("42sh: fc: no command found\n");
		}
		ft_printf("ename = %s\n", fc->ename);
	}
}
