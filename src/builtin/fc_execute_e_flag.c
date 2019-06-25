/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_execute_e_flag.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/25 08:56:49 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/25 14:15:15 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

static int					check_if_ename_is_text_editor(t_fc *fc)
{
	DIR				*dirp;
	struct dirent	*read;

	(void)fc;
	dirp = opendir("/usr/bin/");
	while ((read = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(fc->ename, read->d_name) == 0)
		{
			fc->ename = ft_secure_free(fc->ename);
			fc->ename = ft_strdup(read->d_name);
			return (1);
		}
	}
	closedir(dirp);
	return (0);
}

static void			correct_int_first_and_int_last(t_fc *fc, t_hist *hist)
{
	if (fc->first_not_precised == 1 && fc->last_not_precised == 1)
	{
		fc->int_first = hist->cmd_no;
		fc->int_last = hist->cmd_no;
	}
	else if (fc->first_not_precised == 1)
		fc->int_first = hist->cmd_no;
	else if (fc->last_not_precised == 1)
		fc->int_last = fc->int_first;
	if (fc->int_first < 0)
		fc->int_first = (hist->cmd_no + fc->int_first);
	if (fc->int_last < 0)
		fc->int_last = (hist->cmd_no + fc->int_last);
}

static void			*fill_command_to_send_to_text_editor(char *cmds, t_fc *fc, t_hist *hist)
{
	if (fc->int_first <= fc->int_last)
	{
		while (fc->int_first <= fc->int_last && hist->next->next)
		{
			
		}
	}
	else if (fc->int_first > fc->int_last)
	{
	
	}
}

void				prepare_e_flag(t_fc *fc, t_hist *hist)
{
	int				swap;
	
	(void)hist;
	if (fc->ename != NULL && check_if_ename_is_text_editor(fc) == 1)
	{
		correct_int_first_and_int_last(fc, hist);
		if (ft_strchr(fc->flags, 'r') != NULL)
		{
			swap = fc->int_first;
			fc->int_first = fc->int_last;
			fc->int_last = swap;
		}
		cmds = ft_strnew(0);
		while (hist->prev && hist->cmd_no + 1 > fc->int_first)
			hist = hist->prev;
		fill_command_to_send_to_text_editor(cmds, fc, hist);
		ft_printf("ename pas null et ide trouve\n");
	}

}
