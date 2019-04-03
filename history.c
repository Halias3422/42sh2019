/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/29 09:57:44 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/03 10:40:09 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

t_hist		*move_through_history(t_hist *hist, t_pos *pos, char *usage)
{
	int		ans_len;

	ans_len = 0;
	if (ft_strcmp(usage, "up") == 0 && hist)
	{
		clean_screen(pos);
		ans_len = ft_strlen(pos->ans);
		if (ans_len == 0)
			ans_len = ft_strlen(hist->cmd);
			while (ans_len-- >= 0)
			{
				tputs(tgetstr("le", NULL), 1, ft_putchar);
				tputs(tgetstr("dc", NULL), 1, ft_putchar);
			}
			ft_printf("%s", hist->cmd);
//			free(pos->ans);
			pos->ans = hist->cmd;
			if (hist->prev)
				hist = hist->prev;
	}
	else if (ft_strcmp(usage, "down") == 0 && hist->next)
	{
		clean_screen(pos);
		ans_len = ft_strlen(hist->cmd);
		if (hist->prev)
			ans_len = ft_strlen(hist->prev->cmd);
			while (ans_len-- >= 0)
			{
				tputs(tgetstr("le", NULL), 1, ft_putchar);
				tputs(tgetstr("dc", NULL), 1, ft_putchar);
			}
			if (hist->next)
				hist = hist->next;
			ft_printf("%s", hist->cmd);
	}
//	ft_printf("\nans_len = %d\n", ans_len);
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
	}
/*	while (head && head->next)
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
	}
*/	return (hist);
}


