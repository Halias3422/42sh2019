/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 21:32:49 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 10:54:54 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"



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
		pos->len_ans = pos->len_prompt + ft_strlen(cmd);
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
//		ft_printf("-1-");
/*		while (pos->ans[i])
		{
		//	ft_printf("-2-");
			if ((i != 0 && i % pos->max_co == 0))
			{
				if (pos->act_li < pos->max_li)
				{
				//	ft_printf("-3-act_li %d, pos->ans[%d] |%c|", pos->act_li, i, pos->ans[i]);
					pos->act_li += 1;
					write(1, "\n", 1);
				}
				else
				{
				//	ft_printf("-4-");
					pos->start_li -= 1;
				}
			}
			i++;
		}*/
//		while (pos->ans[i] != '\n')
//			i--;
//		i++;
		i = ft_strlen(pos->ans) - 1;
		if (pos->act_li != pos->max_li)
			pos->act_li += 1;
		else
		{
			pos->start_li -= 1;
			if_prompt_is_on_last_char(pos);
		}
		pos->act_co = ft_strlen(pos->ans + i) % pos->max_co;
		tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
	//	write(1, "> ", 3);
	}
}

void		init_t_hist(t_hist *hist)
{
	if (hist == NULL)
		return ;
	hist->cmd = NULL;
	hist->next = NULL;
	hist->prev = NULL;
	hist->cmd_no = 0;
}

t_hist		*add_list_back_hist(t_hist *hist)
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
	new->cmd_no = hist->cmd_no + 1;
	return (new);
}

t_hist		*create_history(t_pos *pos, t_hist *hist)
{
	char	*pwd;
	int		ret;
	char	*line;

	ret = 1;
	line = NULL;
	pwd = getcwd(NULL, 255);
	pwd = ft_strjoinf(pwd, "/.history", 1);
	pos->history = open(pwd, O_RDWR | O_APPEND | O_CREAT, 0666);
	free(pwd);
	while ((ret = get_next_line(pos->history, &line)))
	{
		hist->cmd = ft_strnew(0);
		hist->cmd = ft_strjoinf(hist->cmd, line, 3);
		hist = add_list_back_hist(hist);
		line = NULL;
	}
	return (hist);
}
