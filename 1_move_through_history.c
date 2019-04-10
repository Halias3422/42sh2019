/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_through_history.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 09:41:10 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 09:41:42 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

static t_hist	*stay_down_in_history(t_hist *hist, t_pos *pos)
{
	if (hist->cmd)
	{
		free(pos->ans);
		pos->ans = ft_strdup(hist->cmd);
		write(1, hist->cmd, ft_strlen(hist->cmd));
//		update_position(pos, hist->cmd);
	}
	else
	{
		pos->act_li = pos->start_li;
		pos->act_co = pos->start_co;
		pos->let_nb = 0;
	}
	return (hist);
}

static t_hist	*go_back_down_in_history(t_hist *hist, t_pos *pos)
{
	hist = hist->next;
	write(1, hist->cmd, ft_strlen(hist->cmd));
//	update_position(pos, hist->cmd);
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

static t_hist	*go_back_in_history(t_hist *hist, t_pos *pos)
{
	if (hist->prev == NULL && hist->cmd == NULL)
		return (hist);
	if (hist && hist->prev != NULL)
		hist = hist->prev;
	write(1, hist->cmd, ft_strlen(hist->cmd));
//	update_position(pos, hist->cmd);
	free(pos->ans);
	pos->ans = ft_strdup(hist->cmd);
	return (hist);
}

t_hist			*move_through_history(t_hist *hist, t_pos *pos, char *usage)
{
	clean_screen(pos);
	if (ft_strcmp(usage, "up") == 0 && hist)
		hist = go_back_in_history(hist, pos);
	else if (ft_strcmp(usage, "down") == 0 && hist && hist->next)
		hist = go_back_down_in_history(hist, pos);
	else if (ft_strcmp(usage, "down") == 0)
		hist = stay_down_in_history(hist, pos);
	update_position(pos, hist->cmd);
	return (hist);
}
