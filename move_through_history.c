/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_through_history.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 07:42:17 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/24 11:25:31 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"


void		update_position(t_pos *pos, char *cmd)
{
	int		diff;
	int		i;

	i = 0;
	if (pos->is_complete == 1)
	{
		diff = 0;
		if (cmd == NULL)
			return ;
		pos->len_ans = get_len_with_lines(pos);
		pos->act_li = pos->start_li + pos->len_ans / pos->max_co;
		if (pos->act_li > pos->max_li)
			pos->act_li = pos->max_li;
		if (pos->len_ans < pos->max_co)
			pos->act_co = pos->len_ans;
		else
			pos->act_co = pos->len_ans % pos->max_co;
		pos->let_nb = ft_strlen(cmd);
		diff = (pos->start_li + (pos->len_ans / pos->max_co)) - pos->max_li;
		if (diff > 0)
			pos->start_li -= diff;
	}
	else
	{
//		pos->act_li += count_nb_line(pos, &pos->act_co);
		pos->let_nb += 0;
		pos->act_li += len_of_previous_line(pos, 1) / pos->max_co;
		pos->act_co = len_of_previous_line(pos, 0);
		pos->let_nb -= 0;
		pos->debug = pos->act_co;
		pos->debug2 = pos->act_li;
		while (pos->act_li > pos->max_li)
		{
			pos->act_li -= 1;
			pos->start_li -= 1;
		}
		tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
	}
}

static t_hist		*stay_down_in_history(t_hist *hist, t_pos *pos)
{
	if (hist->cmd)
	{
		free(pos->ans);
		pos->ans = ft_strdup(hist->cmd);
		write(1, hist->cmd, ft_strlen(hist->cmd));
	}
	else
	{
		pos->act_li = pos->start_li;
		pos->act_co = pos->start_co;
		pos->let_nb = 0;
	}
	return (hist);
}

static t_hist		*go_back_down_in_history(t_hist *hist, t_pos *pos)
{
	hist = hist->next;
	write(1, hist->cmd, ft_strlen(hist->cmd));
	if (hist->cmd != NULL)
	{
		free(pos->ans);
		pos->ans = ft_strdup(hist->cmd);
	}
	else
	{
		free(pos->ans);
		pos->ans = ft_strnew(0);
	}
	return (hist);
}

static t_hist		*go_back_in_history(t_hist *hist, t_pos *pos)
{
	if (hist->prev == NULL && hist->cmd == NULL)
		return (hist);
	if (hist && hist->prev != NULL)
		hist = hist->prev;
//	write(1, hist->cmd, ft_strlen(hist->cmd));
	if (pos->is_complete == 0)
		pos->ans = ft_strjoinf(pos->ans, hist->cmd, 1);
	else if (pos->is_complete == 1)
	{
		free(pos->ans);
		pos->ans = ft_strdup(hist->cmd);
	}
	return (hist);
}

t_hist*			search_up_in_history(t_hist *hist, t_pos *pos)
{
	int			saved_cmd;

	saved_cmd = hist->cmd_no;
	while (1)
	{
		if (hist->prev)
			hist = hist->prev;
		if (ft_strncmp(hist->cmd, pos->saved_ans, ft_strlen(pos->saved_ans)) == 0)
			break ;
		if (hist->prev == NULL)
			break ;
	}
	if (hist->prev == NULL && ft_strncmp(hist->cmd, pos->saved_ans, ft_strlen(pos->saved_ans)) != 0)
	{
		while (hist->cmd_no != saved_cmd)
		{
			if (hist->next == NULL)
				break ;
			hist = hist->next;
		}
	}
	else
	{
		free(pos->ans);
		pos->ans = ft_strdup(hist->cmd);
	}
	return (hist);
}

t_hist		*search_down_in_history(t_hist *hist, t_pos *pos)
{
	int		saved_cmd;

	saved_cmd = hist->cmd_no;
	while (1)
	{
		if (hist->next)
			hist = hist->next;
		if (hist->cmd != NULL && ft_strncmp(hist->cmd, pos->saved_ans, ft_strlen(pos->saved_ans)) == 0)
			break ;
		if (hist->next == NULL)
			break ;
	}
	if (hist->next == NULL && ft_strncmp(hist->cmd, pos->saved_ans, ft_strlen(pos->saved_ans)) != 0)
	{
		while (hist->cmd_no != saved_cmd)
		{
			if (hist->prev == NULL)
				break ;
			hist = hist->prev;
		}
	}
	else
	{
		free(pos->ans);
		pos->ans = ft_strdup(hist->cmd);
	}
	return (hist);
}

t_hist		*move_through_history(t_hist *hist, t_pos *pos, char *usage, char *buf)
{
	//	clean_screen(pos);
	(void)buf;
	if (pos->history_mode == 1 && ft_strcmp(usage, "up") == 0)
		hist = search_up_in_history(hist, pos);
	else if (pos->history_mode == 1 && ft_strcmp(usage, "down") == 0)
		hist = search_down_in_history(hist, pos);
	else if (ft_strcmp(usage, "up") == 0 && hist && hist->prev)
		hist = go_back_in_history(hist, pos);
	else if (ft_strcmp(usage, "down") == 0 && hist && hist->next)
		hist = go_back_down_in_history(hist, pos);
	else if (ft_strcmp(usage, "down") == 0)
		hist = stay_down_in_history(hist, pos);
	update_position(pos, pos->ans);
	return (hist);
}
