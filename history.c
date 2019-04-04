/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/29 09:57:44 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 09:09:47 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

void		update_position(t_pos *pos, char *cmd)
{
	pos->act_li = pos->act_li + ft_strlen(cmd) / pos->max_co;
	if ((int)ft_strlen(cmd) < pos->max_co)
		pos->act_co = ft_strlen(cmd);
	else
		pos->act_co = ft_strlen(cmd) % ((pos->act_li - pos->start_li) * pos->max_co);
	pos->let_nb = ft_strlen(cmd);
}

t_hist		*move_through_history(t_hist *hist, t_pos *pos, char *usage)
{
	if (ft_strcmp(usage, "up") == 0 && hist)
	{
		clean_screen(pos);
		write(1, hist->cmd, ft_strlen(hist->cmd));
		update_position(pos, hist->cmd);
//		pos->act_co = ft_strlen(hist->cmd);
//		pos->let_nb = pos->act_co;
		pos->ans = hist->cmd;
		if (hist->prev)
			hist = hist->prev;
	}
	else if (ft_strcmp(usage, "down") == 0 && hist && hist->next)
	{
		clean_screen(pos);
		if (hist && hist->next)
		{
			hist = hist->next;
			write(1, hist->cmd, ft_strlen(hist->cmd));
			update_position(pos, hist->cmd);
//			pos->act_co = ft_strlen(hist->cmd);
//			pos->let_nb = pos->act_co;
		}
	}
	else if (ft_strcmp(usage, "down") == 0)
	{
		clean_screen(pos);
		tputs(tgoto(tgetstr("cm", NULL), 0, pos->start_li), 1, ft_putchar);
		pos->act_li = pos->start_li;
		pos->act_co = 0;
		pos->let_nb = 0;
		pos->ans[0] = '\0';
	}
	return (hist);
}

t_hist		*ft_list_back(t_hist *head, t_hist *hist)
{
	t_hist	*tmp;

	tmp = NULL;
	if (head == NULL)
		head = hist;
	else
	{
		tmp = head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = hist;
		hist->prev = tmp;
	}
	return (head);
}

t_hist		*create_history(t_pos *pos, t_hist *hist)
{
	char	*pwd;
	int		ret;
	char	*line;
	t_hist	*head;

	ret = 1;
	head = NULL;
	pwd = getcwd(NULL, 255);
	pwd = ft_strjoin(pwd, "/.history");
	pos->history = open(pwd, O_RDWR | O_APPEND | O_CREAT, 0666);
	while (ret != 0)
	{
		ret = get_next_line(pos->history, &line);
		if (ret != 0 && ft_strlen(line) > 0)
		{
			hist = (t_hist*)malloc(sizeof(t_hist));
			hist->cmd = ft_strnew(0);
			hist->cmd = ft_strjoin(hist->cmd, line);
			hist->next = NULL;
			hist->prev = NULL;
			head = ft_list_back(head, hist);
		}
	}/*
	while (head && head->next)
	{
		ft_printf("head->cmd = {%s}\n", head->cmd);
		head = head->next;
	}
	if (head)
		ft_printf("head->cmd = {%s}\n", head->cmd);
	ft_printf("\n	------------\n\n");
	while (head)
	{
		ft_printf("Head->cmd->prev = {%s}\n", head->cmd);
		head = head->prev;
	}*/
	return (hist);
}
