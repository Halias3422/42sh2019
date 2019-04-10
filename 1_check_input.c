/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_input.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 14:01:51 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 09:59:14 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

void		free_t_hist(t_hist *hist)
{
	t_hist *tmp;

	while (hist->next)
		hist = hist->next;
	while (hist)
	{
		tmp = hist;
		if (hist->cmd)
			free(hist->cmd);
		hist = hist->prev;
		free(tmp);
	}
}

void		input_is_entry(t_pos *pos, t_hist *hist)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoinf(getcwd(NULL, 255), "/.history", 1);
	remove(tmp);
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
	close(pos->history);
	pos->history = open(tmp, O_RDWR | O_CREAT, 0666);
	free(tmp);
	while (hist->prev != NULL)
		hist = hist->prev;
	while (hist)
	{
		if (hist->next == NULL)
		{
			if (pos->ans && pos->ans[0] != '\0')
			{
				write(pos->history, pos->ans, ft_strlen(pos->ans));
				write(pos->history, "\n", 1);
			}
			break ;
		}
		if (hist->cmd && hist->cmd[0])
		{
			write(pos->history, hist->cmd, ft_strlen(hist->cmd));
			write(pos->history, "\n", 1);
		}
		hist = hist->next;
	}
	free_t_hist(hist);
	close(pos->history);
}

void		input_is_backspace(t_pos *pos)
{
	if (pos->let_nb > 0 || pos->act_li > pos->start_li)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
		remove_char_ans(pos);
		pos->act_co -= pos->act_co == 0 ? 0 : 1;
		pos->len_ans -= 1;
	}
}

t_hist		*check_input(char *buf, t_pos *pos, t_hist *hist)
{

	if (buf[0] == 27)
		hist = find_arrow(buf, pos, hist);
	else
	{
		clean_screen(pos);
		if (buf[0] == 127)
			input_is_backspace(pos);
		else
		{
			if (buf[0] == 10)
			{
				input_is_entry(pos, hist);
				hist = NULL;
			}
			else
				input_is_printable_char(pos, buf);
		}
		if (hist && hist->next == NULL)
		{
			if (hist->cmd != NULL)
				free(hist->cmd);
			hist->cmd = ft_strdup(pos->ans);
		}

		print_ans(pos);
	}
	return (hist);
}
