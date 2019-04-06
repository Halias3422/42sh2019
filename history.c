/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 21:32:49 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/06 10:43:43 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

void		update_position(t_pos *pos, char *cmd)
{
	int		diff;

	diff = 0;
	pos->debug2 = pos->act_li;
	pos->debug3 = ft_strlen(cmd);
	pos->debug4 = pos->len_prompt;
	pos->debug5 = pos->max_co;
	pos->act_li = pos->act_li + (ft_strlen(cmd) + pos->len_prompt) / pos->max_co;
	if ((int)ft_strlen(cmd) + pos->len_prompt < pos->max_co)
		pos->act_co = ft_strlen(cmd) + pos->len_prompt;
	else
		pos->act_co = (ft_strlen(cmd) + pos->len_prompt) % ((pos->act_li - pos->start_li) * pos->max_co);
	pos->let_nb = ft_strlen(cmd);
	diff = (pos->start_li + ((ft_strlen(cmd) + pos->len_prompt) / pos->max_co)) - pos->max_li;
	pos->debug = pos->act_li;
	if (diff > 0)
	{
		pos->start_li -= diff;
	//	pos->act_li -= diff;
	}
}

t_hist		*move_through_history(t_hist *hist, t_pos *pos, char *usage)
{
	clean_screen(pos);
	if (ft_strcmp(usage, "up") == 0 && hist)
	{
		if (hist->prev == NULL && hist->cmd == NULL)
			return (hist);
		if (hist && hist->prev != NULL)
			hist = hist->prev;
		write(1, hist->cmd, ft_strlen(hist->cmd));
		pos->len_ans = pos->len_prompt + ft_strlen(hist->cmd);
		update_position(pos, hist->cmd);
		pos->ans = ft_strdup(hist->cmd);
	}
	else if (ft_strcmp(usage, "down") == 0 && hist && hist->next)
	{
		if (hist && hist->next)
		{
			hist = hist->next;
			write(1, hist->cmd, ft_strlen(hist->cmd));
			pos->len_ans = pos->len_prompt + ft_strlen(hist->cmd);
			update_position(pos, hist->cmd);
			if (hist->cmd != NULL)
				pos->ans = ft_strdup(hist->cmd);
			else
			{
				free(pos->ans);
				pos->ans = ft_strnew(0);
			}
		}
	}
	else if (ft_strcmp(usage, "down") == 0)
	{
		tputs(tgoto(tgetstr("cm", NULL), pos->start_co, pos->start_li), 1, ft_putchar);
		pos->act_li = pos->start_li;
		pos->act_co = pos->start_co;
		pos->let_nb = 0;
		free(pos->ans);
		pos->ans = ft_strnew(0);
	}
	return (hist);
}

void	init_t_hist(t_hist *hist)
{
	if (hist == NULL)
		return ;
	hist->cmd = NULL;
	hist->next = NULL;
	hist->prev = NULL;
}

t_hist	*add_list_back_hist(t_hist *hist)
{
	t_hist	*new;

	new = NULL;
	if (!(new = (t_hist*)malloc(sizeof(t_hist))))
		return (NULL);
	if (hist == NULL)
	{
		init_t_hist(new);
		return (new);
	}
	while (hist->next != NULL)
		hist = hist->next;
	init_t_hist(new);
	hist->next = new;
	new->prev = hist;
	return (new);
}

t_hist		*create_history(t_pos *pos, t_hist *hist)
{
	char	*pwd;
	int		ret;
	char	*line;

	ret = 1;
	pwd = getcwd(NULL, 255);
	pwd = ft_strjoin(pwd, "/.history");
	pos->history = open(pwd, O_RDWR | O_APPEND | O_CREAT, 0666);
	free(pwd);
	while (ret != 0)
	{
		line = NULL;
		ret = get_next_line(pos->history, &line);
		if (ret != 0 && ft_strlen(line) > 0)
		{
			hist->cmd = ft_strnew(0);
			hist->cmd = ft_strjoin(hist->cmd, line);
			hist = add_list_back_hist(hist);
			free(line);
		}
	}
	return (hist);
}
