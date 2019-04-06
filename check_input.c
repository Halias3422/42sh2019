/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_input.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 14:01:51 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/06 02:17:27 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

void		input_is_entry(t_pos *pos, t_hist *hist)
{
	char	*tmp;
//	char	**delete;
	
	tmp = ft_strjoin(getcwd(NULL, 255), "/.history");
//	delete = ft_strsplit("rm .history", ' ');	
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
//	execve("/bin/rm", delete, NULL);
//	ft_tabdel(delete);
	ft_printf("\nreponse -> |%s|\n", pos->ans);
	close(pos->history);
	pos->history = open(tmp, O_RDWR | O_CREAT, 0666);
	free(tmp);
	while (hist->prev)
		hist = hist->prev;
	while (hist)
	{
		write(pos->history, hist->cmd, ft_strlen(hist->cmd));
		write(pos->history, "\n", 1);
		if (hist->prev != NULL)
		{
			free(hist->prev->cmd);
			free(hist->prev);
		}
		if (hist->next == NULL)
		{
			free(hist->cmd);
			free(hist);
			hist = NULL;
		}
		else
			hist = hist->next;
	}
	close(pos->history);
	main();
}

void		input_is_printable_char(t_pos *pos, char *buf)
{
	fill_char_ans(buf, pos);
	pos->len_ans += 1;
	if (pos->act_li != pos->max_li && pos->act_co == pos->max_co - 1)
	{
		pos->act_co = 0;
		if (pos->act_li == pos->max_li)
			pos->start_li -= 1;
		else
			pos->act_li += 1;
	}
	else if ((pos->start_li + (pos->len_ans / pos->max_co)) == pos->max_li + 1 && pos->len_ans % (pos->max_co) == 0)
	{
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		tputs(tgoto(tgetstr("cm", NULL), pos->max_co + 1, pos->max_li + 1), 1, ft_putchar);
		write(1, " ", 1);
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
		pos->debug++;
		if (pos->act_co != pos->max_co - 1)
		{
			pos->act_co += 1;
			pos->act_li -= 1;
		}
		else
			pos->act_co = 0;
		pos->start_li -= 1;
	}
	else
		pos->act_co += 1;
	pos->let_nb += 1;
	check_poussin(buf[0]);
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
				input_is_entry(pos, hist);
			else
				input_is_printable_char(pos, buf);
		}
		free(hist->cmd);
		hist->cmd = ft_strdup(pos->ans);
		print_ans(pos);
	}
	return (hist);
}
