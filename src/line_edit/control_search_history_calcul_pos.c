/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   control_search_history_calcul_pos.c              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 07:22:34 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/27 12:59:33 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void		get_pos_coordinates_right_again(t_pos *pos)
{
	int		i;

	i = 0;
	pos->act_li = pos->start_li;
	pos->act_co = pos->len_prompt;
	while (pos->ans[i])
	{
		if (pos->ans[i] == '\n' || pos->act_co == pos->max_co - 1)
		{
			pos->act_li += 1;
			pos->act_co = 0;
		}
		else
			pos->act_co += 1;
		i++;
	}
}

void		count_ctrl_col_and_line(t_pos *pos, char *ans, t_ctrl_hist *ctrl,
			int needle)
{
	int		i;

	i = 0;
	while (ans[i] && i < needle)
	{
		if (ans[i] == '\n' || ctrl->act_co == pos->max_co - 2)
		{
			ctrl->act_li++;
			ctrl->act_co = 0;
		}
		else
			ctrl->act_co++;
		i++;
	}
}

int			count_cmd_line_len(t_pos *pos, char *ans, int act_co)
{
	int		nb_line;
	int		i;

	i = 0;
	nb_line = 0;
	while (ans[i])
	{
		if (ans[i] == '\n' || act_co == pos->max_co - 1)
		{
			nb_line++;
			act_co = 0;
		}
		else
			act_co++;
		i++;
	}
	return (nb_line);
}

void		get_right_coordinates_not_found(t_pos *pos, t_ctrl_hist *ctrl)
{
	int		i;

	i = 0;
	ctrl->act_co = 0;
	ctrl->act_li = pos->start_li;
	pos->debug = pos->len_prompt + 22 + ft_strlen(pos->ans);
	while (i < pos->len_prompt + 22 + ft_strlen(pos->ans))
	{
		if (ctrl->act_co < pos->max_co)
			ctrl->act_co += 1;
		if (ctrl->act_co == pos->max_co)
		{
			ctrl->act_co = 0;
			ctrl->act_li += 1;
			if (ctrl->act_li-- > pos->max_li)
			{
				pos->debug5 += 1;
				++;
				prompt_is_on_last_char(pos);
			}
		}
		i += 1;
	}
	if (ctrl->act_li > pos->max_li)
		ctrl->act_li = pos->max_li;
/*	while (ctrl->act_li > pos->max_li)
	{
		ctrl->act_li -= 1;
		pos->start_li -= 1;
	}*/
	pos->act_li = ctrl->act_li;
	pos->act_co = ctrl->act_co;
	print_info(pos);
}

void		get_right_coordinates_found(t_pos *pos, t_hist *hist,
			t_ctrl_hist *ctrl)
{
	int		prev_act_li;
//	int		prev_act_co;

	(void)hist;
	prev_act_li = ctrl->act_li;
	get_right_coordinates_not_found(pos, ctrl);

/*
	prev_act_li = ctrl->act_li;
	prev_act_co = ctrl->act_co;
	count_ctrl_col_and_line(pos, hist->cmd, ctrl, ft_strlen(hist->cmd));
	pos->debug4 = ctrl->act_li;
	while (ctrl->act_li > pos->max_li)
	{
		ctrl->act_li -= 1;
		pos->start_li -= 1;
		prev_act_li -= 1;
	}
	ctrl->act_li = prev_act_li;
	ctrl->act_co = prev_act_co;*/
/*	char *tmp;

	tmp = hist->cmd;
	pos->debug3 = ctrl->act_co;
	while (tmp < hist->cmd + ctrl->needle)
	{
		if (ctrl->act_co == pos->max_co || *tmp == '\n')
		{
			ctrl->act_co = 0;
			ctrl->act_li += 1;
			tmp -= 1;
		}
		else
			ctrl->act_co++;
		tmp += 1;
		pos->debug4 += 1;
	}*/
//	pos->act_co = ctrl->act_co;
//	pos->act_li = ctrl->act_li;
//	pos->debug4 = 0;
}
